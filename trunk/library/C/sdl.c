/***************************************************************
 * Simple Directmedia Layer (SDL) Abstraction Layer
 *
 * This is part of a hybrid library module for Toka. It helps
 * abstract the underlying SDL implementation making basic SDL
 * programming easier.
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


SDL_Surface *screen;
long width, height;

void sdl_setup(long req_width, long req_height)
{
   height = req_height;
   width  = req_width;
   SDL_Init(SDL_INIT_VIDEO);
   screen = SDL_SetVideoMode((int)width, (int)height, 32, SDL_SWSURFACE);
}

void sdl_render()
{
  SDL_UpdateRect(screen, 0, 0, width, height);
}

long sdl_event_type(SDL_Event *event)
{
  return (long)event->type;
}

long sdl_surface_size()
{
  return (long)sizeof(SDL_Surface);
}

long sdl_event_size()
{
  return (long)sizeof(SDL_Event);
}


void sdl_putpixel(long x, long y, long color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = (int)y * (screen->pitch / 4);
  ptr[lineoffset + x] = (int)color;
}


void sdl_circle(long x, long y, long radius, long color)
{
    long x_position, y_position, d, delta_e, delta_se;

    x_position = -1;
    y_position = radius;
    d = 1 - radius;
    delta_e = -1;
    delta_se = (-radius << 1) + 3;

    while (y_position > x_position) {
        delta_e += 2;
        x_position++;

        if (d < 0) {
            d += delta_e;
            delta_se += 2;
        }
        else {
            d += delta_se;
            delta_se += 4;
            y_position--;
        }

        sdl_putpixel(x + x_position, y + y_position, color);
        sdl_putpixel(x + y_position, y + x_position, color);
        sdl_putpixel(x + y_position, y - x_position, color);
        sdl_putpixel(x + x_position, y - y_position, color);

        sdl_putpixel(x - x_position, y - y_position, color);
        sdl_putpixel(x - y_position, y - x_position, color);
        sdl_putpixel(x - y_position, y + x_position, color);
        sdl_putpixel(x - x_position, y + y_position, color);
    }
    sdl_render();
}
