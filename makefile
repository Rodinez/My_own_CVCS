ALL:
	gcc main.c lib/ds.c lib/dir.c -lcrypto -Wno-deprecated-declarations -o main
	gcc test.c lib/ds.c lib/dir.c -lcrypto -Wno-deprecated-declarations -o test