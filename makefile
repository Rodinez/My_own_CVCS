ALL:
	gcc main.c lib/ds.c lib/dir.c -o main
	gcc test.c lib/ds.c lib/dir.c -o test