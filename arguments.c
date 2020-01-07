//Функции для работы и обработки аргументов программы
#include "arguments.h"

const char *starg="hvs:m:";

void print_help()
{
	printf(
	"\t   [ \e[1;32mHelp Menu\e[0m ]\n\n\t\e[1;35mPowered by D21nkMaster\e[0m\n\n -s <XxY>\t----\t\tSet size X and Y (32x32;16x16)\n"
	" -m <name>\t----\t\tOpen save matrix\n"
	" -h\t\t----\t\tPrint this menu\n -v\t\t----\t\tPrint version\n");
	exit(0);
}

//проверка правильного ввода чисел,без символов и букв
char check_numbers(char *str)
{
	char numbers[]="0123456789";
	char check=0;
	for(short i=0;str[i]!=0;++i)
	{
		for(short j=0;numbers[j];++j)
		{
			if(str[i]==numbers[j]){check=1;break;}
			else check=0;
		}
		if(!check)break;
	}
	return check;
}

//забирает числа из аргумента -s XxY
void getnumbers(short *x,short *y,char *arg)
{
	char tmpstr[16];
	char check=0;
	for(unsigned char i=0;arg[i];++i)
	{
		if(arg[i]=='x')
		{
			check=1;
			break;
		}
	}
	if(!check)
	{
		printf("Wrong input size!\n");
		print_help();
		exit(1);
	}
	unsigned char i=0;
	for(;arg[i]!='x';++i)
		tmpstr[i]=arg[i];
	if(!check_numbers(tmpstr))
	{
		printf("You must been input letters in X size\n");
		print_help();
		exit(1);
	}
	if(!check_numbers(arg+i+1))
	{
		printf("You must been input letters in Y size\n");
		print_help();
		exit(1);
	}
	*x=atoi(tmpstr);
	*x=atoi(tmpstr);
	*y=atoi(arg+i+1);
}

//обработчик аргументов
short start_args(short *x,short *y,int argc,char **argv,char *open_name)
{
	short choose=0;
	int ch=0;
	while((ch=getopt(argc,argv,starg))!=-1)
	{
		switch(ch)
		{
			case 's':getnumbers(x,y,optarg);break;
			case 'm':choose=1;sprintf(open_name,"%s",optarg);break;
			case 'h':print_help();break;
			case 'v':printf("Terminal Painter version 0.21 OpenBeta\n");exit(0);break;
			default:
				printf("Wrong option!\n");
				print_help();
		}
	}
	argv+=optind;
	argc-=optind;
	return choose;
}
