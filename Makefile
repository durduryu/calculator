TAR = main
OBJ := *.c
$(TAR):$(OBJ)
	gcc $(OBJ) -o $(TAR) -lreadline