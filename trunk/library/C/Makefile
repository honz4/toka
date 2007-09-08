# ==============================================
# Toka Library
# ==============================================

CFLAGS  =  -O2 -shared -fPIC -g -Wall
CC      =  gcc

default:
	$(CC) $(CFLAGS) sockets.c -o sockets.so
	$(CC) $(CFLAGS) floats.c -o floats.so
	$(CC) $(CFLAGS) console.c -o console.so
	@cd texteditor && $(CC) $(CFLAGS) textedit.c -o ../textedit.so
	$(CC) $(CFLAGS) sdl.c -o sdl.so -lSDL -lm
