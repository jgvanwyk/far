PREFIX ?= /usr/local

MAN1_DIR = $(PREFIX)/share/man/man1
BIN_DIR = $(PREFIX)/bin

far: far.m
	clang -framework Foundation -o far far.m

.PHONY: install
install: far far.1
	cp far $(BIN_DIR)
	cp far.1 $(MAN1_DIR)

.PHONY: uninstall
uninstall:
	rm $(BIN_DIR)/far
	rm $(MAN1_DIR)/far.1

clean:
	rm -f far
