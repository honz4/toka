# ==============================================
# You may want to override CFLAGS to optimize
# further or include debugging information.
# ==============================================

CC = gcc
CFLAGS = -O2 -s -Wall
LDFLAGS = `$(CC) other/needdl.c -ldl 2>/dev/null && echo "-ldl" && rm a.out`
#HEADERS = -I/boot/develop/headers


# ==============================================
# Do the following to disable FFI:
#
# Remove source/ffi.c from DEPS and source/ffi.o
# from OBJS
#
# Add -DNOFFI to CFLAGS
# ==============================================

DEPS =  source/bits.c \
        source/class.c \
        source/cmdline.c \
        source/conditionals.c \
        source/console.c \
        source/data.c \
        source/debug.c \
        source/decompile.c \
        source/dictionary.c \
        source/errors.c \
        source/files.c \
        source/gc.c \
        source/initial.c \
        source/interpret.c \
        source/math.c \
        source/parser.c \
        source/quotes.c \
        source/stack.c \
        source/toka.c \
        source/vm.c \
        source/ffi.c

OBJS =  source/bits.o \
        source/class.o \
        source/cmdline.o \
        source/conditionals.o \
        source/console.o \
        source/data.o \
        source/debug.o \
        source/decompile.o \
        source/dictionary.o \
        source/errors.o \
        source/files.o \
        source/gc.o \
        source/initial.o \
        source/interpret.o \
        source/math.o \
        source/parser.o \
        source/quotes.o \
        source/stack.o \
        source/toka.o \
        source/vm.o \
        source/ffi.o
# ==============================================
default: toka

toka: $(OBJS)
	$(CC) -o toka $^ $(CFLAGS) $(LDFLAGS)

%.o: %.c #$(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(HEADERS)
# ==============================================
clean:
	rm -f `find . | grep \~ `
	rm -f source/*.o source/a.out
	rm -f toka test.log
# ==============================================
install: toka
	cp toka /usr/bin
	mkdir -p /usr/share/toka
	cp bootstrap.toka /usr/share/toka
	chmod +x examples/*
# ==============================================
tests:
	cd examples && toka tests.toka >../test.log
# ==============================================
docs:
	chmod +x scripts/*
	cd source && ../scripts/tokadoc
	cd source && mv FUNCTIONS GLOSSARY ../doc
# ==============================================
