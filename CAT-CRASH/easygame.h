#ifndef EASYGAME_H_INCLUDED
#define EASYGAME_H_INCLUDED

#define WIDTH     300
#define HIHG      110
#define SIZE      (WIDTH*HIHG)  /* 地圖的大小 */
#define OFFSET_X  10
#define OFFSET_Y  10

#define REFRESH_DURATION 5
#define ATTACK_GAP1 100

struct t_CatNode {
    int x;
    int y;
    int direction;
    int duration;
    int tick;
    int high;
    int wide;
};
typedef struct t_CatNode CatNode;

struct t_AttackNode {
    int x;
    int y;
    int duration;
    int direction;
    int tick;
    int high;
    int wide;
};
typedef struct t_AttackNode AttackNode;

void easygame1(void);

void genCatstar_DATA(CatNode* cat, Image * STAR);
void showCatstar(CatNode* cat , Image* STAR);


void showAttack(AttackNode* At ,int A[14],int num, Image* enemy);

void resetAttack_DATA(AttackNode* At);
void genAttack_DATA_fromtop(AttackNode* At);//01234
void genAttack_DATA_bottom(AttackNode* At);//56789
void genAttack_DATA_left(AttackNode* At);//10 11
void genAttack_DATA_right(AttackNode* At);//12 13
void genCatstar_DATA22(CatNode* cat, Image * STAR);

void moveAttack(AttackNode* At, int A[14],int num);
void moveAttack_terrible(AttackNode* At,int A[14],int num);
void boundaryCheck_Cat(CatNode *cat);
void CarshCheck(AttackNode* At, CatNode *cat,int A[14],int num);




#endif // GAME_CAT_H_INCLUDED
