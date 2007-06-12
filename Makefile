# ==============================================
# You may want to override CFLAGS to optimize
# further or include debugging information.
# ==============================================

CC = gcc
CFLAGS = -g -O2 -Wall
LDFLAGS = `$(CC) other/needdl.c -o a.out -ldl 2>/dev/null && echo "-ldl" && rm a.out*`


# ==============================================
# Choose One:
#  - UNIX = Linux, BSD, Solaris, BeOS, Cygwin, etc
#  - WIN32 = Windows (native)
# ==============================================
PLATFORM = -DUNIX
#PLATFORM = -DWIN32


# ==============================================
# Do the following to disable FFI:
#
# Remove source/ffi.c
# Add -DNOFFI to CFLAGS
# ==============================================
default: clean toka

toka:
	$(CC) -o toka source/*.c $(CFLAGS) $(LDFLAGS) $(PLATFORM)
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
remove:
	rm -rf /usr/bin/toka
	rm -rf /usr/share/toka
# ==============================================
tests:
	cd examples && toka tests.toka >../test.log
# ==============================================
docs:
	chmod +x scripts/*
	cd source && ../scripts/tokadoc
	cd source && mv FUNCTIONS GLOSSARY ../doc
# ==============================================
