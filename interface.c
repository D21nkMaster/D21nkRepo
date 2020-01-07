//интерфейс программы и всё,что связанно с ncurses
#include "interface.h"
#include "opensave.h"

WINDOW *win;

char isnumber(int num)
{
	if(((num>=48)&&(num<=57))||((num>=97)&&(num<=102)))
		return 1;
	return 0;
}

void fullrefresh()
{
	refresh();
	wrefresh(win);
}

//старт интерфейса ncurses
char interface()
{
	initscr();
	if(!has_colors())
	{
		endwin();
		return 1;
	}
	start_color();
	noecho();
	for(int i=0;i<16;++i)
		init_pair(i,0,i);
	return 0;
}

//обработчик цветов ncurses
void refresh_color(int **matrix,short col,short row)
{
	for(short i=0;i<col;++i)
	{
		for(short j=0;j<row;++j)
		{
			wmove(win,j,i);
			switch(matrix[i][j])
			{
				case 48:wattron(win,COLOR_PAIR(0));wprintw(win," ");wattroff(win,COLOR_PAIR(0));break;
				case 49:wattron(win,COLOR_PAIR(1));wprintw(win," ");wattroff(win,COLOR_PAIR(1));break;
				case 50:wattron(win,COLOR_PAIR(2));wprintw(win," ");wattroff(win,COLOR_PAIR(2));break;
				case 51:wattron(win,COLOR_PAIR(3));wprintw(win," ");wattroff(win,COLOR_PAIR(3));break;
				case 52:wattron(win,COLOR_PAIR(4));wprintw(win," ");wattroff(win,COLOR_PAIR(4));break;
				case 53:wattron(win,COLOR_PAIR(5));wprintw(win," ");wattroff(win,COLOR_PAIR(5));break;
				case 54:wattron(win,COLOR_PAIR(6));wprintw(win," ");wattroff(win,COLOR_PAIR(6));break;
				case 55:wattron(win,COLOR_PAIR(7));wprintw(win," ");wattroff(win,COLOR_PAIR(7));break;
				case 56:wattron(win,COLOR_PAIR(8));wprintw(win," ");wattroff(win,COLOR_PAIR(8));break;
				case 57:wattron(win,COLOR_PAIR(9));wprintw(win," ");wattroff(win,COLOR_PAIR(9));break;
				case 97:wattron(win,COLOR_PAIR(10));wprintw(win," ");wattroff(win,COLOR_PAIR(10));break;
				case 98:wattron(win,COLOR_PAIR(11));wprintw(win," ");wattroff(win,COLOR_PAIR(11));break;
				case 99:wattron(win,COLOR_PAIR(12));wprintw(win," ");wattroff(win,COLOR_PAIR(12));break;
				case 100:wattron(win,COLOR_PAIR(13));wprintw(win," ");wattroff(win,COLOR_PAIR(13));break;
				case 101:wattron(win,COLOR_PAIR(14));wprintw(win," ");wattroff(win,COLOR_PAIR(14));break;
				case 102:wattron(win,COLOR_PAIR(15));wprintw(win," ");wattroff(win,COLOR_PAIR(15));break;
			}
		}
	}
	fullrefresh();
}

//очистка матрицы для клавиши space
void clean_matrix(int **matrix,short col,short row)
{
	for(short i=1;i<col-1;++i)
	{
		for(short j=1;j<row-1;++j)
			matrix[i][j]=48;
	}
	refresh_color(matrix,col,row);
	fullrefresh();
}

//управление
char motion(int **matrix,short col,short row)
{
	fullrefresh();
	int x=1;
	int y=1;
	keypad(win,1);
	while(1)
	{
		wmove(win,y,x);
		int ch=wgetch(win);
		switch(ch)
		{
			case KEY_UP:if((y-1)>0)--y;wmove(win,y,x);fullrefresh();break;
			case KEY_DOWN:if((y+1)<row-1)++y;wmove(win,y,x);fullrefresh();break;
			case KEY_LEFT:if((x-1)>0)--x;wmove(win,y,x);fullrefresh();break;
			case KEY_RIGHT:if((x+1)<col-1)++x;wmove(win,y,x);fullrefresh();break;
			case 32:clean_matrix(matrix,col,row);break;
			case 'm':output_matrix(matrix,col,row);fullrefresh();break;
			case 's':output_shell(matrix,col,row);fullrefresh();break;
			case 'q':return 0;
			default:
				if(isnumber(ch))
				{
					matrix[x][y]=ch;
					refresh_color(matrix,col,row);
				}
		}
	}
}

//вывод управления и кодов цветов
void show_interface(short col)
{
	for(int i=0;i<16;++i)
	{
		if(i<8)
			move(i+2,col+3);
		else
			move(i-6,col+7);
		if(i<10)
			printw("%d-",i);
		else
			printw("%c-",i+87);
		attron(COLOR_PAIR(i));
		printw(" ");
		attroff(COLOR_PAIR(i));
	}
	mvprintw(2,col+11,"SPACE -clear all colors");
	mvprintw(3,col+11,"ARROWS-move the cursor");
	mvprintw(5,col+11,"q-quit programm");
	mvprintw(7,col+11,"m-inport in matrix");
	mvprintw(9,col+11,"s-inport in shell");
	refresh();
}

void quit_interface(int **matrix,short col)
{
	for(char i=0;i<col;++i)
		free(matrix[i]);
	free(matrix);
	endwin();
}

//проверка размера выбранного юзера
//если размер превышает окно терминала-подстраивает максимальный
void check_size(short x,short y,short *col,short *row)
{
	short xMax,yMax;
	getmaxyx(stdscr,yMax,xMax);
	if(x>(xMax-35))
		*col=xMax-35;
	else
		*col=x;
	if(y>yMax-2)
		*row=yMax-2;
	else
		*row=y;

	win=newwin(*row,*col,1,1);
	box(win,0,0);
	fullrefresh();
}
