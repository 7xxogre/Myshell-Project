myshell_exe : builtin.o exterior.o main.o
		gcc -o myshell_exe builtin.o exterior.o main.o

builtin.o : builtin.c
	gcc -c -o builtin.o builtin.c

exterior.o : exterior.c
	gcc -c -o exterior.o exterior.c

main.o : main.c
	gcc -c -o main.o main.c

clean :
	rm *.o myshell_exe


