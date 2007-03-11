# ==============================================
# You may want to override CFLAGS to optimize
# further or include debugging information.
# ==============================================
CFLAGS = -O2 -s
CC = gcc
UNAME = `uname`


# ==============================================
# Additional flags required by specific OSes
# ==============================================
BEOSFLAGS = -I/boot/develop/headers



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
	@case "x$(UNAME)" in        \
          xLinux)     make linux ;; \
          xOpenBSD)   make bsd   ;; \
          xNetBSD)    make bsd   ;; \
          xFreeBSD)   make bsd   ;; \
          xDragonFly) make bsd   ;; \
          xBeOS)      make beos  ;; \
          xCYGWIN_NT-6.0) make windows   ;; \
	esac
# ==============================================
toka:
	@make
linux:
	@echo Host appears to be Linux...
	cd source && $(CC) $(CFLAGS) $(FILES) -ldl -o ../toka
bsd:
	@echo Host appears to be a BSD system...
	cd source && $(CC) $(CFLAGS) $(FILES) -o ../toka
windows:
	@echo WARNING: Only tested under Cygwin
	cd source && $(CC) $(CFLAGS) $(FILES) -ldl -o ../toka
beos:
	@echo Host appears to be BeOS...
	cd source && $(CC) $(CFLAGS) $(BEOSFLAGS) $(FILES) -ldl -o ../toka
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
	rm -f source/*.o
# ==============================================
install: toka
	cp toka /usr/bin
	mkdir -p /usr/share/toka
	cp bootstrap.toka /usr/share/toka
	chmod +x examples/*
# ==============================================
