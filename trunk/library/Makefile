# ==============================================
# Toka Library
# ==============================================

CFLAGS  =  -O2 -shared -fPIC
CC      =  gcc

default:
	@echo ==============================================
	@echo Valid targets are:
	@echo
	@echo - install
	@echo Build and Install the libraries.
	@echo
	@echo - clean
	@echo Remove all temporary files.
	@echo
	@echo - remove
	@echo Uninstall Toka Library
	@echo
	@echo - test
	@echo Run a series of automated tests agains the
	@echo newly installed libraries.
	@echo ==============================================

install:
	mkdir -p /usr/share/toka/library
	mkdir -p /usr/share/toka/library/C
	cp Libraries/* /usr/share/toka/library
	cd C && make -kis
	cp C/*.so /usr/share/toka/library/C

clean:
	rm -f `find . | grep \~ `
	rm -f C/*.so C/*.o test.log

remove:
	rm -rf /usr/share/toka/library

test:
	cd tests && toka tests.toka >../test.log
