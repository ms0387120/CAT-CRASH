#include "font.h"
#ifndef FRAMEWORK_
#define FRAMEWORK_
typedef struct
{
    int x;
    int y;
    int fgcolor;
    int bgcolor;
    int cursor;
    int num_options;
    int state[10];
    char text[15][30]; /* �̦h�s�Q�Ӧr��  �C�Ӧr����׳̦h 79 �Ӧr�� */
    char alt_text[15][30]; /* �̦h�s�Q�Ӧr��  �C�Ӧr����׳̦h 79 �Ӧr�� */
    Font *large_font;
} Menu;
extern void setMainmenu(Menu *m);
extern void scrollMenu(Menu *m, int diff);
extern void showMenu(Menu *m);
extern int IsOnItem(Menu *m, int index);
extern int IsItemSelected(Menu *m, int index);
#endif
