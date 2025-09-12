CC = gcc

build:	tema1.o queue.o car.o
	$(CC) $^ -o tema1

queue.o:	queue.c 
	$(CC) -c $^ -o $@

car.o:	car.c 
	$(CC) -c $^ -o $@

tema1.o:	tema1.c 
	$(CC) -c $^ -o $@

run:	tema1
	./tema1
	
clean:	
	rm -rf *.o tema1