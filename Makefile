MAN1_DIR=/usr/local/share/man/man1
BIN_DIR=/usr/local/bin

far: far.c
	clang -framework CoreFoundation -o far far.c

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
