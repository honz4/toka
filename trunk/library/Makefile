# ==============================================
# Toka Library
# Released under the MIT License (doc/LICENSE)
# ==============================================

CFLAGS  =  -O2 -shared -fPIC
CC      =  gcc

default:
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
	@echo ==============================================

install:
	mkdir -p /usr/share/toka/library
	mkdir -p /usr/share/toka/library/C
	cp Libraries/* /usr/share/toka/library
	cd C && make
	cp C/*.so /usr/share/toka/library/C

clean:
	rm -f `find . | grep \~ `
	rm -f C/*.so C/*.o

remove:
	rm -rf /usr/share/toka/library
