TAR1 = main
OBJ1 := main.c stack.c work.c print.c file_make.c solve.c transit.c
$(TAR1):$(OBJ1)
	gcc $(OBJ1) -o $(TAR1) -lreadline
