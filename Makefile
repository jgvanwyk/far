DESTDIR=/usr/local/bin

far: far.c
	clang -framework CoreFoundation -o far far.c

install: far
	cp far $(DESTDIR)

clean:
	rm -f far
