flags=-Wall --std=c90
encontraLog=encontraLog
listagem=listagem
dirent=dirent

all: encontraLog listagem dirent
clear:
	clear
encontraLog: encontraLog.c encontraLog.o 
	gcc $(flags) encontraLog.o -o $(encontraLog)
listagem: listagem.o
	gcc $(flags) listagem.o -o $(listagem)
dirent: dirent.o
	gcc $(flags) dirent.o -o $(dirent)
# ru: ru_na_pandemia.o libpilha.o
# 	gcc -o $(flags) ru_na_pandemia.o libpilha.o libfila.o liblista.o -o $(ru)

clean:
	rm -f *.o *.gch $(encontraLog) $(listagem) $(dirent)
