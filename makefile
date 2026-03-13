all:
	gcc main.c lib/ds.c lib/dir.c -lcrypto -Wno-deprecated-declarations -o main

check:
	./main

distcheck:
	make
	make check
