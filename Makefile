CC = gcc
HEADER = ./header/traffic.c

populate:
	${CC} ./populate.c ${HEADER} -o ./pop.out

act1:
	${CC} ./activities/act1.c ${HEADER} -o ./act1.out

act2:
	${CC} ./activities/act2.c ${HEADER} -o ./act2.out

delete:
	rm ./files/traffic.dat
