CC = gcc

populate:
	${CC} ./populate.c ./header/traffic.c -o ./pop.out

act1:
	${CC} ./activities/act1.c ./header/traffic.c -o ./act1.out

