# ==============================================
# You may want to override CFLAGS to optimize
# further or include debugging information.
# ==============================================
CFLAGS = -O2 -s
CC = gcc
UNAME = `uname`
DL  = `$(CC) ../other/needdl.c -ldl 2>/dev/null &&  echo "-ldl"`
LDFLAGS = $(DL)

# ==============================================
# Additional flags required by specific OSes
# ==============================================
BEOSFLAGS = -I/boot/develop/headers

# ==============================================
NOFFI = bits.c \
        class.c \
        cmdline.c \
        conditionals.c \
        console.c \
        data.c \
        debug.c \
        decompile.c \
        dictionary.c \
        files.c \
        gc.c \
        initial.c \
        interpret.c \
        math.c \
        parser.c \
        quotes.c \
        stack.c \
        toka.c \
        vm.c

FILES = $(NOFFI) \
        ffi.c
# ==============================================
default:
	cd source && $(CC) $(CFLAGS) $(FILES) $(LDFLAGS) -o ../toka
	make -s tclean

cygwin:
	cd source && $(CC) $(CFLAGS) $(NOFFI) -DNOFFI -o ../toka
	make -s tclean

beos:
	cd source && $(CC) $(CFLAGS) $(BEOSFLAGS) $(FILES) $(LDFLAGS) -o ../toka
	make -s tclean

vanilla:
	cd source && $(CC) $(CFLAGS) $(NOFFI) -DNOFFI -o../toka
	make -s tclean
# ==============================================
tests:
	cd examples && toka tests.toka >../test.log
# ==============================================
docs:
	chmod +x scripts/*
	cd source && ../scripts/tokadoc
	cd source && mv FUNCTIONS GLOSSARY ../doc
# ==============================================
clean:
	make -s tclean
	rm -f toka test.log
# ==============================================
tclean:
	rm -f `find . | grep \~ `
	rm -f source/*.o source/a.out
# ==============================================
install: toka
	cp toka /usr/bin
	mkdir -p /usr/share/toka
	cp bootstrap.toka /usr/share/toka
	chmod +x examples/*
# ==============================================
