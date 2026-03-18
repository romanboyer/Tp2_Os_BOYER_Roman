default : servudp cliudp servbeuip clibeuip creme.o biceps

cliudp : cliudp.c
	cc -Wall -Werror -o cliudp cliudp.c

servudp : servudp.c
	cc -Wall -Werror -o servudp servudp.c

clibeuip : clibeuip.c
	cc -Wall -Werror -DTRACE -o clibeuip clibeuip.c

servbeuip : servbeuip.c
	cc -Wall -Werror -DTRACE -o servbeuip servbeuip.c

creme.o: creme.c creme.h
	cc -Wall -Werror -DTRACE -c creme.c

biceps : triceps.c creme.o
	cc -Wall -Werror -DTRACE -o biceps triceps.c creme.o

clean :
	rm -f cliudp servudp clibeuip servbeuip biceps triceps *.o