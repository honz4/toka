# ==============================================
# Toka Library
# Released under the MIT License (doc/LICENSE)
# ==============================================

CFLAGS  =  -O2 -shared -fPIC -g -Wall
CC      =  gcc

default:
	$(CC) $(CFLAGS) sockets.c -o sockets.so
	$(CC) $(CFLAGS) floats.c -o floats.so
	$(CC) $(CFLAGS) hexdump.c -o hexdump.so
	$(CC) $(CFLAGS) console.c -o console.so
	@cd texteditor && $(CC) $(CFLAGS) textedit.c -o ../textedit.so
	$(CC) $(CFLAGS) sdl.c -o sdl.so -lSDL -lm
