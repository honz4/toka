# ==============================================
# You may want to override CFLAGS to optimize
# further or include debugging information.
# ==============================================

CC = gcc
CFLAGS = -g -O2 -Wall
#CFLAGS = -s -O3 -Wall -ffast-math -funsafe-loop-optimizations
LDFLAGS = `$(CC) other/needdl.c -o a.out -ldl 2>/dev/null && echo "-ldl" && rm a.out*`
#HEADERS = -I/boot/develop/headers


# ==============================================
# Do the following to disable FFI:
#
# Remove source/ffi.c
# Add -DNOFFI to CFLAGS
# ==============================================
default: toka

toka:
	$(CC) -o toka source/*.c $(CFLAGS) $(LDFLAGS) $(HEADERS)
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
