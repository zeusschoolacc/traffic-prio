CC = gcc
HEADER = ./header/traffic.c

populate:
	${CC} ./populate.c ${HEADER} -o ./pop.out

act1:
	${CC} ./activities/act1.c ${HEADER} -o ./act1.out

