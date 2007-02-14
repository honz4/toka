# ==============================================
# You may want to override CFLAGS to optimize
# further or include debugging information.
# ==============================================
CFLAGS = -O3 -s
CC = gcc
# ==============================================
FILES = bits.c \
        class.c \
        cmdline.c \
        conditionals.c \
        console.c \
        data.c \
        debug.c \
        decompile.c \
        dictionary.c \
        ffi.c \
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
# ==============================================
default:
	@echo ================================================
	@echo Valid targets are:
	@echo - linux
	@echo - bsd
	@echo - windows
	@echo ================================================
	@echo Additional targets:
	@echo - clean
	@echo - install
	@echo ================================================
	@echo Tips:
	@echo - Use GCC 3.x or 4.x if possible
	@echo - Use Cygwin to compile under Windows
	@echo ================================================
# ==============================================
linux:
	cd source && $(CC) $(CFLAGS) $(FILES) -ldl -o ../toka
bsd:
	cd source && $(CC) $(CFLAGS) $(FILES) -o ../toka
windows:
	cd source && $(CC) $(CFLAGS) $(FILES) -ldl -o ../toka
# ==============================================
tests:
	cd examples && toka tests.toka >../test.log
# ==============================================
docs:
	cd source && ../scripts/tokadoc
	cd source && mv FUNCTIONS GLOSSARY ../doc
	cd doc && ./generate html toka.rdml toka.html
	cd doc && ./generate text toka.rdml toka.txt
# ==============================================
clean:
	rm -f `find . | grep \~ `
	rm -f `find . | grep tmp `
	rm -f toka test.log
# ==============================================
tclean:
	rm -f `find . | grep \~ `
# ==============================================
install:
	cp toka /usr/bin
	mkdir -p /usr/share/toka
	mkdir -p /usr/share/toka/library
	cp bootstrap.toka /usr/share/toka
	cp -r library/* /usr/share/toka/library
# ==============================================
