exe: bin/seewhat.o bin/main.o
	gcc -std=c99 -o exe bin/main.o bin/seewhat.o

bin/seewhat.o: source/seewhat.c
	gcc -std=c99 -c source/seewhat.c -o bin/seewhat.o

bin/main.o: main.c
	gcc -std=c99 -c main.c -o bin/main.o

clear:
	rm bin/* exe