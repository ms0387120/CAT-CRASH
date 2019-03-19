#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "font.h"
#include "framework.h"
void setMainmenu(Menu *m)
{
    int i;

    m->large_font = read_font("font.txt");
    m->x = 250;
    m->y = 11;
    m->fgcolor = 10;
    m->bgcolor = 15;
    m->num_options = 3;
    m->cursor = 0;
    for (i=0; i<m->num_options; i++) {
        m->state[i] = 0;
    }
    m->state[m->cursor] = m->state[m->cursor] | 1;  /* 目前選擇的項目 */
    strcpy(m->text[0], "START");
    strcpy(m->text[1], "ABOUT");
    strcpy(m->text[2], "EXIT");

    strcpy(m->alt_text[0], "START *");
    strcpy(m->alt_text[1], "ABOUT *");
    strcpy(m->alt_text[2], "EXIT *");
}

void showMenu(Menu *m)
{
    int i;
    int fg;
    char *str;

    for (i=0; i< m->num_options; i++) {

        if ( !IsOnItem(m, i) ) {
            fg = m->fgcolor;
        } else {
            fg = m->bgcolor;
        }

        if ( !IsItemSelected(m, i) ) {
            str = m->text[i];
        } else {
            str = m->alt_text[i];
        }

        putStringLarge(m->large_font, m->x,(m->y)+40*i, str, fg);
    }
}

void scrollMenu(Menu *m, int diff)
{
    m->state[m->cursor] = m->state[m->cursor] & (~1);  /* 把目前游標所在的選項狀態清除 */
    m->cursor = (m->cursor + diff + m->num_options) % m->num_options; /* 把遊標移到下一個選項 */
    m->state[m->cursor] = m->state[m->cursor] | 1; /* 選擇目前游標所在的選項 */
}
int IsOnItem(Menu *m, int index)
{
    return (m->state[index] & 1); /* 用位元運算來判斷目前選擇的項目 */
}
int IsItemSelected(Menu *m, int index)
{
    return (m->state[index] & 2); /* 用位元運算來判斷目前選擇的項目 */
}

