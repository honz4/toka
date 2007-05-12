# ==============================================
# You may want to override CFLAGS to optimize
# further or include debugging information.
# ==============================================

CC = gcc
CFLAGS = -O2 -s -Wall
LDFLAGS = `$(CC) needdl.c -ldl 2>/dev/null && echo "-ldl" && rm a.out`
#HEADERS = -I/boot/develop/headers


# ==============================================
# Do the following to disable FFI:
#
# Remove source/ffi.c
# Add -DNOFFI to CFLAGS
# ==============================================
default: clean symlinks toka

toka:
	$(CC) -o toka debug/*.c $(CFLAGS) $(LDFLAGS) $(HEADERS)
	rm -f debug/*.o source/a.out
# ==============================================
clean:
	@cd debug && rm -f bits.c conditionals.c debug.c errors.c gc.c interpret.c  
	@cd debug && rm -f quotes.c stack.c vm.c class.c console.c decompile.c ffi.c math.c
	@cd debug && rm -f cmdline.c data.c dictionary.c files.c initial.c parser.c
	@cd debug/headers && rm -f bits.h conditionals.h data.h dictionary.h files.h interpret.h quotes.h toka.h
	@cd debug/headers && rm -f class.h config.h debug.h errors.h gc.h math.h vm.h
	@cd debug/headers && rm -f cmdline.h console.h decompile.h ffi.h initial.h parser.h stack.h
	@rm -f toka

symlinks:
	cd debug && ln -s ../../source/bits.c 
	cd debug && ln -s ../../source/class.c 
	cd debug && ln -s ../../source/cmdline.c 
	cd debug && ln -s ../../source/conditionals.c 
	cd debug && ln -s ../../source/console.c
	cd debug && ln -s ../../source/data.c
	cd debug && ln -s ../../source/debug.c
	cd debug && ln -s ../../source/decompile.c
	cd debug && ln -s ../../source/dictionary.c
	cd debug && ln -s ../../source/errors.c
	cd debug && ln -s ../../source/ffi.c
	cd debug && ln -s ../../source/files.c
	cd debug && ln -s ../../source/gc.c
	cd debug && ln -s ../../source/initial.c
	cd debug && ln -s ../../source/interpret.c
	cd debug && ln -s ../../source/math.c
	cd debug && ln -s ../../source/parser.c
	cd debug && ln -s ../../source/quotes.c
	cd debug && ln -s ../../source/stack.c
	cd debug && ln -s ../../source/vm.c
	cd debug/headers && ln -s ../../../source/headers/bits.h
	cd debug/headers && ln -s ../../../source/headers/class.h
	cd debug/headers && ln -s ../../../source/headers/cmdline.h
	cd debug/headers && ln -s ../../../source/headers/conditionals.h
	cd debug/headers && ln -s ../../../source/headers/config.h
	cd debug/headers && ln -s ../../../source/headers/console.h
	cd debug/headers && ln -s ../../../source/headers/data.h
	cd debug/headers && ln -s ../../../source/headers/debug.h
	cd debug/headers && ln -s ../../../source/headers/decompile.h
	cd debug/headers && ln -s ../../../source/headers/dictionary.h
	cd debug/headers && ln -s ../../../source/headers/errors.h
	cd debug/headers && ln -s ../../../source/headers/ffi.h
	cd debug/headers && ln -s ../../../source/headers/files.h
	cd debug/headers && ln -s ../../../source/headers/gc.h
	cd debug/headers && ln -s ../../../source/headers/initial.h
	cd debug/headers && ln -s ../../../source/headers/interpret.h
	cd debug/headers && ln -s ../../../source/headers/math.h
	cd debug/headers && ln -s ../../../source/headers/parser.h
	cd debug/headers && ln -s ../../../source/headers/quotes.h
	cd debug/headers && ln -s ../../../source/headers/stack.h
	cd debug/headers && ln -s ../../../source/headers/toka.h
	cd debug/headers && ln -s ../../../source/headers/vm.h
