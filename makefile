all: control.o write.o
	gcc -o control control.o
	gcc -o write write.o

control.o:
	gcc -c control.c

write.o:
	gcc -c write.c

clean:
	rm *.o
	rm *.out
	rm *~
