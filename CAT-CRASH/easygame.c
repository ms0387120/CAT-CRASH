#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <mmsystem.h>
#include "console_draw3.h"
#include "kb_input2.h"
#include "image.h"
#include "font.h"
#include "audio.h"
#include "easygame.h"
int IsEnding = 0;

void easygame1(void)
{
    int i;
    CatNode Catstar[2];
    AttackNode Attack[20];
/*        01234  56789   10 11   1213*/
    /*from top   bottom  left    right*/

    /*計時*/
    clock_t startc;
    int game_tick = 0;
    int game_at[20];



    for(i=0; i<20; i++) game_at[i]=0;

    /*鍵盤控制*/
    int vk;

    /*音效*/
    //Audio Background_music;
    //openAudioFile("chimes.wav", &au1);

    /* 啟動鍵盤控制 */
    initializeKeyInput();

    /*記住當時的時間*/
    startc = clock();

    /*get picture*/
    Image *star1 = read_image("star1.pixel" , "star1.color");
    Image *star2 = read_image("star2.pixel" , "star2.color");
    Image *STAR = star2;

    Image *water = read_image("water.pixel" , "water.color");
    Image *drums = read_image("drums.pixel" , "drums.color");
    Image *fungi = read_image("fungi.pixel" , "fungi.color");
    Image *lize  = read_image("lize.pixel"  , "lize.color");
    Image *old   = read_image("old.pixel"   , "old.color");
    Image *morisan=read_image("morisan.pixel", "morisan.color");
    Image *bg0   = read_image("bg0.pixel"   , "bg0.color");
    Image *bg2   = read_image("bg2.pixel"   , "bg2.color");
    Image *next   = read_image("next.pixel"   , "next.color");
    Image *most   = read_image("most.pixel"   , "most.color");


    genCatstar_DATA(Catstar,STAR);

    genAttack_DATA_fromtop(Attack);//01234
    genAttack_DATA_bottom(Attack);//56789
    genAttack_DATA_left(Attack);//10 11
    genAttack_DATA_right(Attack);//12 13


    /*Game star*/
    while (!IsEnding) {



        if ((double)(clock()-startc) > 0.01*CLOCKS_PER_SEC) { //每秒1000 clock 1/100sce
            game_tick++;
            for(i=0;i<14;i++)game_at[i]++;
            startc = clock();
        }

        if (game_tick > REFRESH_DURATION) { //game_tick 要更新的時候 才更新
            game_tick = 0;
            clearScreen(); //清畫面

            show_image(bg0, OFFSET_X, OFFSET_Y);
            showCatstar(Catstar,STAR);

            // Attack Start

            if (game_at[0]>ATTACK_GAP1   && game_at[0]<=ATTACK_GAP1*3){

                int A[14]={1,4,5,6};
                int Nn=4;
                showAttack(Attack,A,Nn,drums);
                moveAttack(Attack,A,Nn);
                if (game_at[0]>=ATTACK_GAP1*3){
                    resetAttack_DATA(Attack);
                    game_at[0]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[1]>ATTACK_GAP1*3 && game_at[1]<=ATTACK_GAP1*5){

                int A[14]={6,8,9};
                int Nn=3;
                showAttack(Attack,A,Nn,fungi);
                moveAttack(Attack,A,Nn);
                if (game_at[1]>=ATTACK_GAP1*5){
                    resetAttack_DATA(Attack);
                    game_at[1]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[2]>ATTACK_GAP1*5 && game_at[2]<=ATTACK_GAP1*9){

                int A[14]={6,7,8,10,13};
                int Nn=5;
                showAttack(Attack,A,Nn,old);
                moveAttack(Attack,A,Nn);
                if (game_at[2]>=ATTACK_GAP1*9){
                    //resetAttack_DATA(Attack);
                    genAttack_DATA_left(Attack);//10 11
                    game_at[2]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[3]>ATTACK_GAP1*7 && game_at[3]<=ATTACK_GAP1*9){

                int A[14]={0,8,12};
                int Nn=3;
                showAttack(Attack,A,Nn,old);
                moveAttack(Attack,A,Nn);
                if (game_at[3]>=ATTACK_GAP1*11){
                    resetAttack_DATA(Attack);
                    game_at[3]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[4]>ATTACK_GAP1*11 && game_at[3]<=ATTACK_GAP1*13){

                int A[14]={1,5,10};
                int Nn=3;
                showAttack(Attack,A,Nn,morisan);
                moveAttack(Attack,A,Nn);
                if (game_at[4]>=ATTACK_GAP1*13){
                    resetAttack_DATA(Attack);
                    game_at[4]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[5]>ATTACK_GAP1*13 && game_at[5]<=ATTACK_GAP1*16){

                int A[14]={2,4,7};
                int Nn=3;
                showAttack(Attack,A,Nn,morisan);
                moveAttack(Attack,A,Nn);
                if (game_at[5]>=ATTACK_GAP1*16){
                    resetAttack_DATA(Attack);
                    game_at[5]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[6]>ATTACK_GAP1*9 && game_at[6]<=ATTACK_GAP1*11){

                int A[14]={2,10,13};
                int Nn=3;
                showAttack(Attack,A,Nn,lize);
                moveAttack(Attack,A,Nn);
                if (game_at[6]>=ATTACK_GAP1*11){
                    resetAttack_DATA(Attack);
                    game_at[6]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            drawCmdWindow();
        }

        if(waitForKeyDown(0.01)) {
            vk=getKeyEventVirtual();	/* read a virtual key */

            //遇到break 才出來
            switch(vk) {
                case VK_ESCAPE:  /* 按下 ESC 鍵 就結束 */
                    IsEnding = 1; //無窮迴圈結束
                    break;
                case VK_UP:
                case VK_W:
                    Catstar[0].y=Catstar[0].y-10;
                    break;
                case VK_DOWN: //等同於RIGHT L做的事情 都一樣
                case VK_S:
                    Catstar[0].y=Catstar[0].y+10;
                    break;
                case VK_LEFT:
                case VK_A:
                    Catstar[0].x=Catstar[0].x-10;
                    break;
                case VK_RIGHT:
                case VK_D:
                    Catstar[0].x=Catstar[0].x+10;
                    break;

            }
            boundaryCheck_Cat(Catstar);
        }


    }
/**********************************************************************/
    IsEnding = 0;
    STAR = star1;
    clearScreen();
    show_image(next, OFFSET_X, OFFSET_Y);
    drawCmdWindow();
    Sleep(2000);

    genCatstar_DATA22(Catstar,STAR);

    genAttack_DATA_fromtop(Attack);//01234
    genAttack_DATA_bottom(Attack);//56789
    genAttack_DATA_left(Attack);//10 11
    genAttack_DATA_right(Attack);//12 13

    /*Game star2222222222222222222222*/
    while (!IsEnding) {



        if ((double)(clock()-startc) > 0.01*CLOCKS_PER_SEC) { //每秒1000 clock 1/100sce
            game_tick++;
            for(i=0;i<14;i++)game_at[i]++;
            startc = clock();
        }

        if (game_tick > REFRESH_DURATION) { //game_tick 要更新的時候 才更新
            game_tick = 0;
            clearScreen(); //清畫面

            //show_image(bg2, OFFSET_X, OFFSET_Y);
            show_image(bg2, OFFSET_X, OFFSET_Y);
            showCatstar(Catstar,STAR);

            // Attack Start

            if (game_at[0]>ATTACK_GAP1   && game_at[0]<=ATTACK_GAP1*3){

                int A[14]={1,8,11,13};
                int Nn=4;
                showAttack(Attack,A,Nn,water);
                moveAttack(Attack,A,Nn);
                if (game_at[0]>=ATTACK_GAP1*3){
                    resetAttack_DATA(Attack);
                    game_at[0]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[1]>ATTACK_GAP1*3 && game_at[1]<=ATTACK_GAP1*5){

                int A[14]={0,1,4,5,6};
                int Nn=4;
                showAttack(Attack,A,Nn,old);
                moveAttack(Attack,A,Nn);
                if (game_at[1]>=ATTACK_GAP1*5){
                    resetAttack_DATA(Attack);
                    game_at[1]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[2]>ATTACK_GAP1*5 && game_at[2]<=ATTACK_GAP1*9){

                int A[14]={2,3,10,13};
                int Nn=4;
                showAttack(Attack,A,Nn,lize);
                moveAttack(Attack,A,Nn);
                if (game_at[2]>=ATTACK_GAP1*9){
                    //resetAttack_DATA(Attack);
                    genAttack_DATA_left(Attack);//10 11
                    game_at[2]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[3]>ATTACK_GAP1*9 && game_at[3]<=ATTACK_GAP1*11){

                int A[14]={5,6,8};
                int Nn=3;
                showAttack(Attack,A,Nn,fungi);
                moveAttack(Attack,A,Nn);
                if (game_at[3]>=ATTACK_GAP1*11){
                    resetAttack_DATA(Attack);
                    game_at[3]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[4]>ATTACK_GAP1*11 && game_at[3]<=ATTACK_GAP1*13){

                int A[14]={6,9};
                int Nn=2;
                showAttack(Attack,A,Nn,morisan);
                moveAttack(Attack,A,Nn);
                if (game_at[4]>=ATTACK_GAP1*13){
                    resetAttack_DATA(Attack);
                    game_at[4]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[5]>ATTACK_GAP1*13 && game_at[5]<=ATTACK_GAP1*16){

                int A[14]={0,1,8,9};
                int Nn=10;
                showAttack(Attack,A,Nn,drums);
                moveAttack(Attack,A,Nn);
                if (game_at[5]>=ATTACK_GAP1*16){
                    resetAttack_DATA(Attack);
                    game_at[5]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[6]>ATTACK_GAP1*9 && game_at[6]<=ATTACK_GAP1*11){

                int A[14]={2,10,13};
                int Nn=3;
                showAttack(Attack,A,Nn,lize);
                moveAttack(Attack,A,Nn);
                if (game_at[6]>=ATTACK_GAP1*11){
                    resetAttack_DATA(Attack);
                    game_at[6]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            drawCmdWindow();
        }

        if(waitForKeyDown(0.01)) {
            vk=getKeyEventVirtual();	/* read a virtual key */

            //遇到break 才出來
            switch(vk) {
                case VK_ESCAPE:  /* 按下 ESC 鍵 就結束 */
                    IsEnding = 1; //無窮迴圈結束
                    break;
                case VK_UP:
                case VK_W:
                    Catstar[0].y=Catstar[0].y-10;
                    break;
                case VK_DOWN: //等同於RIGHT L做的事情 都一樣
                case VK_S:
                    Catstar[0].y=Catstar[0].y+10;
                    break;
                case VK_LEFT:
                case VK_A:
                    Catstar[0].x=Catstar[0].x-10;
                    break;
                case VK_RIGHT:
                case VK_D:
                    Catstar[0].x=Catstar[0].x+10;
                    break;

            }
            boundaryCheck_Cat(Catstar);
        }
    }
/**********************************************************************/
    /*Terrible*/
    IsEnding = 0;
    STAR = star1;
    clearScreen();
    show_image(most, OFFSET_X, OFFSET_Y);
    drawCmdWindow();
    Sleep(2000);

    genCatstar_DATA22(Catstar,STAR);

    genAttack_DATA_fromtop(Attack);//01234
    genAttack_DATA_bottom(Attack);//56789
    genAttack_DATA_left(Attack);//10 11
    genAttack_DATA_right(Attack);//12 13

    /*Game star2222222222222222222222*/
    while (!IsEnding) {



        if ((double)(clock()-startc) > 0.01*CLOCKS_PER_SEC) { //每秒1000 clock 1/100sce
            game_tick++;
            for(i=0;i<14;i++)game_at[i]++;
            startc = clock();
        }

        if (game_tick > REFRESH_DURATION) { //game_tick 要更新的時候 才更新
            game_tick = 0;
            clearScreen(); //清畫面

            //show_image(bg2, OFFSET_X, OFFSET_Y);
            show_image(bg2, OFFSET_X, OFFSET_Y);
            showCatstar(Catstar,STAR);

            // Attack Start

            if (game_at[0]>ATTACK_GAP1   && game_at[0]<=ATTACK_GAP1*1.5){

                int A[14]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};
                int Nn=14;
                showAttack(Attack,A,Nn,water);
                moveAttack(Attack,A,Nn);
                if (game_at[0]>=ATTACK_GAP1*2){
                    resetAttack_DATA(Attack);
                    game_at[0]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }

            if (game_at[0]>ATTACK_GAP1*1.5   && game_at[0]<=ATTACK_GAP1*3){

                int A[14]={0,1,2,3,4,5,6,7,8,9,10,11,12,13};
                int Nn=14;
                showAttack(Attack,A,Nn,star1);
                moveAttack(Attack,A,Nn);
                if (game_at[0]>=ATTACK_GAP1*5){
                    resetAttack_DATA(Attack);
                    game_at[0]=0;
                }
                CarshCheck(Attack,Catstar,A,Nn);
            }


            drawCmdWindow();
        }

        if(waitForKeyDown(0.01)) {
            vk=getKeyEventVirtual();	/* read a virtual key */

            //遇到break 才出來
            switch(vk) {
                case VK_ESCAPE:  /* 按下 ESC 鍵 就結束 */
                    IsEnding = 1; //無窮迴圈結束
                    break;
                case VK_UP:
                case VK_W:
                    Catstar[0].y=Catstar[0].y-10;
                    break;
                case VK_DOWN: //等同於RIGHT L做的事情 都一樣
                case VK_S:
                    Catstar[0].y=Catstar[0].y+10;
                    break;
                case VK_LEFT:
                case VK_A:
                    Catstar[0].x=Catstar[0].x-10;
                    break;
                case VK_RIGHT:
                case VK_D:
                    Catstar[0].x=Catstar[0].x+10;
                    break;

            }
            boundaryCheck_Cat(Catstar);
        }
    }



}


/*CAT*/
void genCatstar_DATA(CatNode* cat, Image * STAR)
{
    cat[0].x =OFFSET_X+20;
    cat[0].y =OFFSET_Y+10;
    cat[0].high=27;
    cat[0].wide=27;
}

void genCatstar_DATA22(CatNode* cat, Image * STAR)
{
    cat[0].x =OFFSET_X+120;
    cat[0].y =OFFSET_Y+35;
    cat[0].high=20;
    cat[0].wide=20;
}


void showCatstar(CatNode* cat , Image* STAR)
{
    show_image(STAR, OFFSET_X+cat[0].x, OFFSET_Y+cat[0].y);
}

/*ATTACT*/

/*        01234   56789   10 11   1213
   from   top     bottom  left    right*/

void resetAttack_DATA(AttackNode* At)
{
    genAttack_DATA_fromtop(At);//01234
    genAttack_DATA_bottom(At);//56789
    genAttack_DATA_left(At);//10 11
    genAttack_DATA_right(At);//12 13
}

void genAttack_DATA_fromtop(AttackNode* At)
{
    int i;
    for(i=0; i<5; i++){
        At[i].x=/*OFFSET_X*/+(WIDTH/6)*i+clock()%100;
        At[i].y=/*OFFSET_Y*/+0;
        At[i].direction=1;
        At[i].duration=50;
        At[i].tick=0;
        At[i].high=27;
        At[i].wide=27;
    }
}

void genAttack_DATA_bottom(AttackNode* At)
{
    int i;
    for(i=5; i<10; i++){
        At[i].x=/*OFFSET_X*/+(WIDTH/6)*(i%5)+20/*+clock()%100*/;
        At[i].y=/*OFFSET_Y*/+100;
        At[i].direction=0;
        At[i].duration=50;
        At[i].tick=0;
        At[i].high=27;
        At[i].wide=27;
    }
}

void genAttack_DATA_left(AttackNode* At)
{
        At[10].x=/*OFFSET_X*/+0;
        At[10].y=/*OFFSET_Y*/+25+clock()%50;
        At[10].direction=3;
        At[10].duration=50;
        At[10].tick=0;
        At[10].high=27;
        At[10].wide=27;

        At[11].x=OFFSET_X+0;
        At[11].y=OFFSET_Y+60+clock()%100;
        At[11].direction=3;
        At[11].duration=50;
        At[11].tick=0;
        At[11].high=27;
        At[11].wide=27;
}

void genAttack_DATA_right(AttackNode* At)
{
        At[12].x=/*OFFSET_X*/+(WIDTH/6)*5;
        At[12].y=/*OFFSET_Y*/+clock()%100;
        At[12].direction=2;
        At[12].duration=50;
        At[12].tick=0;
        At[12].high=25;
        At[12].wide=25;

        At[13].x=/*OFFSET_X*/+(WIDTH/6)*5;
        At[13].y=/*OFFSET_Y*/+clock()%100+clock()%50;
        At[13].direction=2;
        At[13].duration=50;
        At[13].tick=0;
        At[13].high=25;
        At[13].wide=25;

}

void showAttack(AttackNode* At ,int A[14],int num, Image* enemy)
{
    int i,j;
    for (i=0; i<14; i=i+1){
        for(j=0;j<num;j++){
            if(i==A[j]){
                show_image(enemy, At[i].x, At[i].y);
            }
        }
    }
}

void moveAttack(AttackNode* At,int A[14],int num)
{
    int i,j;
    for(i=0; i<14; i++){
        for(j=0;j<num;j++){
            if(i==A[j]){
                if(At[i].direction==0 /*&& At[i].y>OFFSET_Y*/){
                    At[i].y=At[i].y-10;
                }else if (At[i].direction==1){
                    At[i].y=At[i].y+10;
                }else if (At[i].direction==2 /*&& At[i].x>OFFSET_X*/){
                    At[i].x=At[i].x-20;
                }else if (At[i].direction==3){
                    At[i].x=At[i].x+20;
                }
            }
        }
    }
}

void moveAttack_terrible(AttackNode* At,int A[14],int num)
{
    int i,j;
    for(i=0; i<14; i++){
        for(j=0;j<num;j++){
            if(i==A[j]){
                if(At[i].direction==0 /*&& At[i].y>OFFSET_Y*/){
                    At[i].y=At[i].y-5;
                }else if (At[i].direction==1){
                    At[i].y=At[i].y+5;
                }else if (At[i].direction==2 /*&& At[i].x>OFFSET_X*/){
                    At[i].x=At[i].x-5;
                }else if (At[i].direction==3){
                    At[i].x=At[i].x+5;
                }
            }
        }
    }
}


/*MAP*/
void CarshCheck(AttackNode* At, CatNode *cat,int A[14],int num)
{
    int i,j;
    int cat_x1,cat_y1;
    int cat_x2,cat_y2;
    int at_x1,at_y1;
    int at_x2,at_y2;

    cat_x1=cat[0].x;
    cat_y1=cat[0].y;
    cat_x2=cat[0].x+cat[0].wide;
    cat_y2=cat[0].y+cat[0].high;


    for(i=0; i<14; i++){
        for(j=0;j<num;j++){
            if(i==A[j]){
                    at_x1=At[i].x;
                    at_y1=At[i].y;
                    at_x2=At[i].x+10;//+At[i].wide;
                    at_y2=At[i].y+1;//+At[i].high;

                    if(!(cat_x2<at_x1 || cat_x1>at_x2||
                       cat_y2<at_y1 || cat_y1>at_y2)){
                        IsEnding=1;
                    }
            }
        }
    }

}

void boundaryCheck_Cat(CatNode *cat)
{
    if (cat[0].x < 0) cat[0].x = 0;
    if (cat[0].y < 0) cat[0].y = 0;
    if (cat[0].x >= WIDTH-50) cat[0].x = WIDTH-50;
    if (cat[0].y >= HIHG-25) cat[0].y = HIHG-25;
}
