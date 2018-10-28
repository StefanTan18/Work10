all: rand.o
	gcc -o randfile rand.o

rand.o:
	gcc -c rand.c

run:
	./randfile

clean:
	rm *.o
	rm randfile
