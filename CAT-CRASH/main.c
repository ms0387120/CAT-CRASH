#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include "console_draw3.h"
#include "audio.h"
#include "font.h"
#include "image.h"
#include "kb_input2.h"
#include "framework.h"
#include "easygame.h"
#define WIDTH     300
#define HIHG      110
#define SIZE      (WIDTH*HIHG)  /* 地圖的大小 */
#define OFFSET_X  10
#define OFFSET_Y  10
#define NUM_KEYS 11
void openinganimation(void);
void endinganimation(void);
int main(void)
{
    openinganimation();
    clearScreen();
    int IsEnding=0,k=0;
    int key_val[NUM_KEYS] = {VK_UP, VK_DOWN, VK_SPACE, VK_RIGHT, VK_LEFT, VK_ESCAPE};
    int key_down[NUM_KEYS]={0};
    int yokai=0,doraemon=0,easy=0,hard=0,incredible=0;
    Menu mainmenu;
    Audio audio[4];
    openAudioFile("mainmenu.wav", &audio[0]);
    openAudioFile("yokaibgm.wav", &audio[1]);
    openAudioFile("doraemonbgm.wav", &audio[2]);
    openAudioFile("meow.wav", &audio[3]);
    Image *banner=read_image("banner.pixel","banner.color");
    Image *lize=read_image("lize.pixel","lize.color");
    Image *star1=read_image("star1.pixel","star1.color");
    Image *star2=read_image("star2.pixel","star2.color");
    Image *fungi=read_image("fungi.pixel","fungi.color");
    Font *large_font=read_font("font.txt");

    initializeKeyInput();
    setMainmenu(&mainmenu);
    show_image(banner,20,10);
    saveScreen();

    while(!IsEnding){
        putStringLarge(mainmenu.large_font,75,2,"CAT CRASH",12);
        playAudio(&audio[3]);
        //playAudio(&audio[0]);
        showMenu(&mainmenu);
        drawCmdWindow();
        for (k=0; k<NUM_KEYS; k++) {
            if(KEY_DOWN(key_val[k]) && !key_down[k]) {
                key_down[k] = 1;
                switch (key_val[k]) {
                case VK_ESCAPE:
                    pauseAudio(&audio[3]);
                    endinganimation();
                    IsEnding=1;
                    break;
                case VK_UP:
                    scrollMenu(&mainmenu, -1);
                    break;
                case VK_DOWN:
                    scrollMenu(&mainmenu, +1);
                    break;
                case VK_SPACE:
                    if (IsOnItem(&mainmenu, 0)) {
                        pauseAudio(&audio[3]);
                        playAudio(&audio[1]);
                        easygame1();
                        pauseAudio(&audio[1]);
                        endinganimation();
                        IsEnding=1;
                        break;
                    }
                    else if (IsOnItem(&mainmenu, 1)) {
                        clearScreen();
                        putStringLarge(large_font,60,15,"RULES",11);
                        putStringLarge(large_font,1,25,"You only have one life",9);
                        putStringLarge(large_font,1,35,"Once you are attacked",9);
                        putStringLarge(large_font,1,45,"or touch monsters",9);
                        putStringLarge(large_font,1,55,"You will lose",9);
                        putStringLarge(large_font,45,70,"Good Luck",11);
                        show_image(fungi,180,45);
                        drawCmdWindow();
                        break;
                    }
                    else if (IsOnItem(&mainmenu, 2)) {
                        pauseAudio(&audio[3]);
                        endinganimation();
                        IsEnding=1;
                        break;
                    }
                }
            }
            if(KEY_UP(key_val[k]) && key_down[k]) {
                key_down[k] = 0;
            }
        }
    }
    clearScreen();
    return 0;
}

void openinganimation(void)
{
    int flag = 0;
    int n = 9;
    Audio audio[2];
    openAudioFile("start.wav",&audio[0]);
    Image * start0 = read_image("start0.pixel","start0.color");
    Image * start1 = read_image("start1.pixel","start1.color");
    Image * start2 = read_image("start2.pixel","start2.color");
    Image * start3 = read_image("start3.pixel","start3.color");
    Image * start4 = read_image("start4.pixel","start4.color");
    Image * start5 = read_image("start5.pixel","start5.color");
    Image * start6 = read_image("start6.pixel","start6.color");
    while(n > 0){
    clearScreen();
    flag = (flag+1)%9;
    if(flag==1){
        show_image(start0,4,2);
        playAudio(&audio[0]);
    }
    else if(flag==2)show_image(start1,4,2);
    else if(flag==3)show_image(start2,4,2);
    else if(flag==4)show_image(start3,4,2);
    else if(flag==5)show_image(start4,4,2);
    else if(flag==6)show_image(start6,4,2);
    else if(flag==7)show_image(start5,4,2);
    else if(flag==8)show_image(start6,4,2);
    else show_image(start5,4,2);
    drawCmdWindow();
    Sleep(500);
    n--;
    }
    destroy_image(start0);
    destroy_image(start1);
    destroy_image(start2);
    destroy_image(start3);
    destroy_image(start4);
    destroy_image(start5);
    destroy_image(start6);
    pauseAudio(&audio[0]);
    return;
}

void endinganimation(void)
{
    int flag = 0;
    int n = 16;
    Audio audio[2];
    openAudioFile("end.wav",&audio[1]);
    Image * end0 = read_image("end0.pixel","end0.color");
    Image * end1 = read_image("end1.pixel","end1.color");
    Image * end2 = read_image("end2.pixel","end2.color");
    Image * end3 = read_image("end3.pixel","end3.color");
    Image * end4 = read_image("end4.pixel","end4.color");
    Image * end5 = read_image("end5.pixel","end5.color");
    Image * end6 = read_image("end6.pixel","end6.color");
    while(n > 0){
    clearScreen();
    flag = (flag+1)%7;
    if(flag==1)show_image(end0,4,2);
    else if(flag==2){
            show_image(end1,4,2);
            playAudio(&audio[1]);
    }
    else if(flag==3)show_image(end2,4,2);
    else if(flag==4)show_image(end3,4,2);
    else if(flag==5)show_image(end4,4,2);
    else if(flag==6)show_image(end5,4,2);
    else {
            show_image(end6,4,2);
            restartAudio(&audio[1]);
    }
    drawCmdWindow();
    Sleep(500);
    n--;
    }
    destroy_image(end0);
    destroy_image(end1);
    destroy_image(end2);
    destroy_image(end3);
    destroy_image(end4);
    destroy_image(end5);
    destroy_image(end6);
    return ;
}
