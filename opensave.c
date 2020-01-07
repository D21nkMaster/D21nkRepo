#include "opensave.h"

char *ask_name(short col,short row)
{
	static char name[256]={0};
	WINDOW *name_win=newwin(4,30,11,col+3);
	echo();
	box(name_win,0,0);
	mvwprintw(name_win,1,1,"Enter output filename:");
	wmove(name_win,2,1);
	wscanw(name_win,"%255s",name);
	wclear(name_win);
	wrefresh(name_win);
	refresh();
	delwin(name_win);
	noecho();
	return (char*)&name;
}

void output_matrix(int **matrix,short col,short row)
{
	FILE *name=fopen(ask_name(col,row),"w+");
	fprintf(name,"%d %d \n",col,row);
	for(short i=0;i<col;++i)
	{
		for(short j=0;j<row;++j)
			fprintf(name,"%d ",matrix[i][j]);
		fputc('\n',name);
	}
	fclose(name);
}


void output_shell(int **matrix,short col,short row)
{
	FILE *name=fopen(ask_name(col,row),"w+");
	for(short i=0;i<row;++i)
	{
		for(short j=0;j<col;++j)
		{
			switch(matrix[j][i])
			{
				case 48:fprintf(name,"\e[40m ");break;
				case 49:fprintf(name,"\e[41m ");break;
				case 50:fprintf(name,"\e[42m ");break;
				case 51:fprintf(name,"\e[43m ");break;
				case 52:fprintf(name,"\e[44m ");break;
				case 53:fprintf(name,"\e[45m ");break;
				case 54:fprintf(name,"\e[46m ");break;
				case 55:fprintf(name,"\e[47m ");break;
				case 56:fprintf(name,"\e[1;40m ");break;
				case 57:fprintf(name,"\e[1;41m ");break;
				case 97:fprintf(name,"\e[1;42m ");break;
				case 98:fprintf(name,"\e[1;43m ");break;
				case 99:fprintf(name,"\e[1;44m ");break;
				case 100:fprintf(name,"\e[1;45m ");break;
				case 101:fprintf(name,"\e[1;46m ");break;
				case 102:fprintf(name,"\e[1;47m ");break;
			}
		}
		fprintf(name,"\e[0m\n");
	}
	fclose(name);
}
