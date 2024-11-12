build:
	rm -f app.exe
	gcc main.c -o app.exe

run:
	./app.exe

rand3:
	./app.exe < random3.txt

rand4:
	./app.exe < random4.txt

rand5:
	./app.exe < random5.txt

rand6:
	./app.exe < random6.txt

rand7:
	./app.exe < random7.txt

valgrind:
	rm -f app.exe
	gcc -g main.c -o app.exe
	valgrind ./app.exe

