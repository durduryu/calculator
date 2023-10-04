TAR = main
OBJ := main.c stack.c work.c print.c file_make.c
$(TAR):$(OBJ)
	gcc $(OBJ) -o $(TAR) -lreadline
