
all: monolith list_static list_dynamic

lab1.o:
	gcc -Wall -c lab1.c -o lab1.o -I.

list.o:
	gcc -Wall -c list.c -o list.o -I.

monolith: lab1.o list.o
	gcc lab1.o list.o -o list_test

liblist.a: list.o
	ar r liblist.a list.o
	ar tv liblist.a

list_static: lab1.o liblist.a
	gcc lab1.o liblist.a -o list_test_static 

liblist.so: list.o
	gcc -Wall -fPIC -c list.c -I.
	gcc list.o -shared -o liblist.so

list_dynamic: lab1.o liblist.so
	gcc lab1.o -L. -llist -o list_test_dynamic

clean: 
	rm *.a *.so *.o list_test_static list_test list_test_dynamic