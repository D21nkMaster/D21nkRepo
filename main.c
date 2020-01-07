//основной файл
#include "interface.h"
#include "arguments.h"

int getnum(FILE *file)
{
	short ch=0;
	char num[8]={0};
	for(char i=0;(ch=getc(file))!=' ';++i)
		num[i]=ch;

	return atoi(num);
}

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		print_help();
		exit(0);
	}
	
	short choose=0;
	unsigned short x=0,y=0;
	char open_name[256]={0};
	unsigned short col=0;
	unsigned short row=0;
	int **matrix;
	choose=start_args(&x,&y,argc,argv,open_name);//arguments.c

	if(interface())//interface.c
	{
		printf("Sorry your terminal can't support colors\n");
		exit(1);
	}

	if(choose==1)
	{
		FILE *file=fopen(open_name,"r");
		x=getnum(file);
		y=getnum(file);
		check_size(x,y,&col,&row);//interface.c
		matrix=(int**)calloc(col*sizeof(int*),1);
		for(short i=0;i<col;++i)
			matrix[i]=calloc(row*sizeof(int),1);
		for(short i=0;i<col;++i)
		{
			for(short j=0;j<row;++j)
				matrix[i][j]=getnum(file);
		}
		fclose(file);
		refresh_color(matrix,col,row);
	}
	else
	{
		check_size(x,y,&col,&row);//interface.c
		matrix=(int**)calloc(col*sizeof(int*),1);
		for(short i=0;i<col;++i)
			matrix[i]=calloc(row*sizeof(int),1);
		clean_matrix(matrix,col,row);//interface.c
	}
	
	show_interface(col);//interface.c
	motion(matrix,col,row);//interface.c
	quit_interface(matrix,col);//interface.c
	return 0;
}
