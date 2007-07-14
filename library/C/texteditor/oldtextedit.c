/* te.c - Text Editor

  REV   DATE	REVISION NOTES
  ----------------------------------------------------------
   -   7/27/02	Split off from htn.c.. just a viewer so far.
   A  10/16/02	Finished the viewer code.
   B   7/17/03	Editor functions.
   C   7/22/03  Support for saving files
   D   7/23/03  Better ENTER handling
                Screen updates (cursor pos, after a delete)
                More information in update bar
   E   7/26/03  Easier modification of command keys (CTRL+??)
                Titlebar now shows if file is saved or modified
   F   7/13/07  Now a library for Toka.

  >>  As of Revision D, te can be considered usable <<

  Tom Novelli wrote the original code (revisions -, A, B)
  Charles Childers wrote revisions C, D, E, F

  TODO (and comments/thoughts)
  ----------------------------------------------------------
   [x] Update the cursor statistics on each move
   [x] Better ENTER key handling
       [x] Insert a newline AFTER the current line, not before
       [x] Increment 'line' counter
           * I _should_ reduce the 'line' counter when a line
             is deleted, but it isn't a neccessity.
   [x] Update screen after a delete
   [ ] General source cleanup
       [ ] Reformat to Toka-style formatting
       [ ] Comments in TokaDoc format
       [ ] This section could be dropped or moved to a
           changelog file
   [ ] External documentation
   [x] File saving
   [ ] Separate shared code (from htn.c) from editor code
       * Rationale: As an external, self contained module,
                    code reuse will be easier. Both te and
                    htn will benifit from any improvements
                    to the shared code.
   [x] Easier selection of key bindings
   [x] More information in update bar
       [x] Filename
       [x] Modified or Saved

  ----------------------------------------------------------
  Tom Novelli has a new version which is more suitable to
  text editing. His new version (called 'edit') will be the
  default editor. I will take this version in a totally
  different direction and design it for editing Forth code
  as a part of the Seahorse Experiment.
  ----------------------------------------------------------

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "term.h"
#include "scancodes.h"

// Titlebar display value
//                             file       cy     cx    isClean()
#define titlebar "\e[0;7mFile: %s    Row %4d Col %3d   %s\e[0m\n"

char *file;
FILE *f;
char buf[4096 * 16];		// Edit buffer
int w = 80, h = 25,		// Screen size (my screen is really 100x37)
 cx = 0, cy = 0,		// Cursor position (in rows/columns within file)
 sx = 0, sy = 0,		// Scrolling location (first row/column visible on screen)
 lines;				// # of lines in file
int clean = 0;                  // Has code been modified?

// Temp variables for rendering.. draw(), etc.
int x, y;			// Current Position
char *p;			// Buffer ptr

void *get_buffer()
{
  return &buf;
}

void load(char *file)
{
    int c;
    char *p = buf;
    if (!(f = fopen(file, "r"))) {
	printf("Couldn't open file '%s'\n", file);
	exit(1);
    }
    lines = 0;
    c = fgetc(f);
    while (!feof(f)) {
	*p++ = c;
	if (c == 10)
	    lines++;
	c = fgetc(f);
    }
    fclose(f);
    clean = 0;
}

void save(char *file)
{
    if (!(f = fopen(file, "w"))) {
	printf("Couldn't open file '%s'\n", file);
	exit(1);
    }
    fprintf(f, "%s", buf);
    fclose(f);
    clean = 0;
    update();
}

char *isClean()
{
   if(clean == 0)
     return "          ";
   else
     return "(Modified)";
}

spaces(int n)
{
    int i;
    for (i = 0; i < n; i++)
	putchar(32);
    x += n;
}


/* Returns a pointer to the beginning of line n */
char *line(int n)
{
    char *p = buf;
    int y = 0;
    for (; *p && y < n; p++)
	if (*p == 10)
	    y++;
    return p;
}

void drawline(char *p)
{
    while (*p && *p != 10) {
	putchar(*p);
	p++;
    }
}

void update()
{
    home();
    printf(titlebar, file, cy, cx, isClean());
    cursor(); }

/* Redraw the entire screen */
void draw()
{
    cls();
    home();
    printf(titlebar, file, cy, cx, isClean());
    for (p = buf, x = 0, y = 0; *p && y < sy; p++) {
	if (*p == 10) {
	    y++;
	    x = 0;
	}

	else
	    x++;
    }
    for (; *p && y < sy + h; p++) {
	putchar(*p);
	if (*p == 10) {
	    y++;
	    x = 0;
	}
    }
    cursor();
}


/* Move cursor to cx,cy */
void cursor()
{
    xy(cx + 1, cy - sy + 2);
}


/* Process keystrokes */
void edit()
{
    int c;
    term_init(); draw();

    for (;;) {
	switch (c = getchar()) {
	case 27:		// ...
	    escape();
	    break;
	case CTRL_X:		// ^X Quit
	    term_cleanup(); return;
	case CTRL_L:		// ^L Redraw
	    draw();
	    break;
	case CTRL_A:		// ^A Home
	    k_home();
	    break;
	case CTRL_E:		// ^E End
	    k_end();
	    break;
	case CTRL_S:		// ^S save
	    save(file);
	    break;
	case CTRL_Y:		// ^Y Page up
	    k_pgup();
	    break;
	case CTRL_V:		// ^V Page down
	    k_pgdn();
	    break;
	case CTRL_H:		// ^H backspace
	case 127:
	    cx--;
	    printf("\e[D");
	case CTRL_D:		// ^D delete
	    k_del();
            draw();
	    break;
	default:		// Insert a character (or overwrite)
	    if (c > 31 && c < 127 || c == 10 || c == 13) {
		char *p = cx + line(cy);
		memmove(p + 1, p, strlen(p));
		*p = c;
           if(c == 10 || c == 13) {
             printf("\e[L");
             draw();
             lines++;
             break;
           }
		cx++;
		printf("\e[@%c", c);
                clean = -1;
		update();
	    }
	}			/* switch */
    }
}


/* Process incoming VT100 escape codes */
void escape()
{
    if (getchar() != '[')
	return;
    switch (getchar()) {
    case 'A':			// Up
	if (!cy)
	    break;
	cy--;
	if (cy < sy)
	    lnup();
	cursor();
	break;
    case 'B':			// Down
	if (cy + 1 >= lines)
	    break;
	cy++;
	if (cy >= sy + h)
	    lndn();
	cursor();
	break;
    case 'C':			// Right
	if (cx < w) {
	    cx++;
	    printf("\e[C");
	}
	break;
    case 'D':			// Left
	if (cx) {
	    cx--;
	    printf("\e[D");
	}
	break;
    case '1':			// Home
	if (getchar() != '~')
	    break;
	k_home();
	break;
    case '3':			// Del
	if (getchar() != '~')
	    break;
	k_del();
	break;
    case '4':			// End
	if (getchar() != '~')
	    break;
	k_end();
	break;
    case '5':			// PgUp
	if (getchar() != '~')
	    break;
	k_pgup();
	break;
    case '6':			// PgDn
	if (getchar() != '~')
	    break;
	k_pgdn();
	break;
    }
    update();
}

void k_home()
{
    if (cx == 0) {
	char *p;
	for (p = line(cy); isspace(*p); p++, cx++);	// Scan to first non-space char.
    }

    else
	cx = 0;
    cursor();
}

void k_end()
{
    char *p;
    for (cx = 0, p = line(cy); !(*p == 10 || *p == 13); p++, cx++);	// Scan to end of line
    cursor();
}

void k_pgup()
{
    if (!sy)
	return;
    sy -= h;
    cy -= h;
    if (sy < 0)
	sy = cy = 0;
    draw();
}

void k_pgdn()
{
    if (sy + h > lines)
	return;
    sy += h;
    cy += h;
    draw();
}


/* Scroll up 1 line */
void lnup()
{
    if (!sy)
	return;
    sy--;
    xy(1, h + 1);
    printf("\e[M");		// delete line
    xy(1, 2);
    printf("\e[L");		// insert line
    drawline(line(sy));
}


/* Scroll down 1 line */
void lndn()
{
    if (sy + 1 >= lines)
	return;
    sy++;
    xy(1, 2);
    printf("\e[M");		// delete line
    xy(1, h + 1);
    drawline(line(sy + h - 1));
}

void k_del()
{
    char *p = cx + line(cy);
    if (*p == 10 || *p == 13)
	draw();			// Redraw if a line was deleted
    else
	printf("\e[P");
    memmove(p, p + 1, strlen(p));
}
