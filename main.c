//основной файл

#include "interface.c"
#include "arguments.c"

int main(int argc,char *argv[])
{
	if(argc<2)
	{
		print_help();
		exit(0);
	}
	short x,y;
	start_args(&x,&y,argc,argv);//arguments.c
	if(interface())//interface.c
	{
		printf("Sorry your terminal can't support colors\n");
		exit(1);
	}
	check_size(x,y);//interface.c
	show_interface();//interface.c
	int **matrix=(int**)calloc(col*sizeof(int*),1);
	for(short i=0;i<col;++i)
		matrix[i]=calloc(row*sizeof(int),1);
	motion(matrix);//interface.c
	quit_interface(matrix);//interface.c
	return 0;
}
