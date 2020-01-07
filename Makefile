build:main interface arguments opensave
	gcc main.o interface.o arguments.o opensave.o -lncurses -o tpaint

debag:main_debag interface_debag arguments_debag opensave_debag
	gcc main.o interface.o arguments.o opensave.o -g -lncurses -o tpaint_debag

main:main.c
	gcc -c main.c

interface:interface.c
	gcc -c interface.c

arguments:arguments.c
	gcc -c arguments.c

opensave:opensave.c
	gcc -c opensave.c

main_debag:main.c
	gcc -c main.c -g

interface_debag:interface.c
	gcc -c interface.c -g

arguments_debag:arguments.c
	gcc -c arguments.c -g

opensave_debag:opensave.c
	gcc -c opensave.c -g

clean:
	rm -rf ./*.o

help:
	echo -e '\t[ \e[1;32mHelp menu\e[0m ]\nbuild\t\t----\t\tbuild the project\ndebag\t\t----\t\tbuild the project for debug\nclean\t\t----\t\tremove all build files\nhelp\t\t----\t\tshow this menu\n'
