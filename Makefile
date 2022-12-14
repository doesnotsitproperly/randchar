default:
	$(CC) main.c -O2 -Wall -o randchar

windows:
	$(CC) main.c -O2 -Wall -o randchar.exe

run: default
	./randchar

run-windows: windows
	.\randchar.exe
