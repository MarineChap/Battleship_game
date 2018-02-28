battleship : battleship.o main.o
	gcc battleship.o main.o -o battleship

battleship.o : battleship.c 
	gcc -o battleship.o -g -c -Wall -pedantic battleship.c

main.o : main.c battleship.h
	gcc -o main.o -g -c -Wall -pedantic main.c 

clean:
	rm -rf *.o

mrproper: clean
	rm -rf battleship
