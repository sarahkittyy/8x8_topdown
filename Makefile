all: prog.out
	./prog.out
	
prog.out: prog.c
	gcc prog.c -o prog.out