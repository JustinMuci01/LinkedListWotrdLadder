build_test:
	rm -f test.exe
	gcc test.c -o test.exe

run_test:
	./test.exe

valgrind:
	rm -f test.exe
	gcc -g test.c -o test.exe
	valgrind ./test.exe