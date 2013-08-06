To compile this code, you need to use g++

On the linux command line you can compile your code using the following command:
	g++ -o main main.cpp postfix.c -Wno-write-strings
	
You can then run your program by running:
	./main

In DevC++ you need to create a Project that includes both the main.cpp and postfix.c files.


There is a makefile which means you can also just run make to compile your code:
	make

