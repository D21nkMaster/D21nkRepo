#include <ncurses.h>
#include <stdlib.h>

char interface();
char motion(int **matrix,short col,short row);
void show_interface(short col);
void quit_interface(int **matrix,short col);
void check_size(short x,short y,short *col,short *row);
void clean_matrix(int **matrix,short col,short row);
void refresh_color(int **matrix,short col,short row);
