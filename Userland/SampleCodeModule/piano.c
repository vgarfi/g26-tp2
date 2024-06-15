#include "include/syscalls.h"
#include "include/stdio.h"
#include "include/colors.h"
#include "include/utils.h"
#include "include/piano.h"
#define ESC 27
#define BLACKPRESS 0x00505050
static int scale = 4;
static char scaleC[2] = {'4','\0'};
static int press[13] = {0};
void initP(){
    sysHideCursor();
    sysClearScreen();
    sysSetZoomLevel(4);
    sysSetCursorPosition(0,0);
    printColor("You are in piano mode\n",YELLOW);
    sysSetCursorPosition(0,2);
    printColor("Change scale (octave) with number\n",YELLOW);
    sysSetCursorPosition(0,4);
    printColor("Notes are:\n",YELLOW);
    sysSetCursorPosition(1,5);
    printColor("C# = e  D# = r  F# = y  G# = u  A# = i\n",YELLOW);
    sysSetCursorPosition(0,6);
    printColor("C = s  D = d  E = f  F = g  G = h  A = j  B = k\n",YELLOW);
    sysSetCursorPosition(0,7);
    printColor("Octave:",YELLOW);
    sysSetCursorPosition(8,7);
    printColor(scaleC,YELLOW);
    sysSetCursorPosition(9,7);
    printColor("\n",YELLOW);
    drawPiano(8);
}

void drawKey(int idx,uint32_t color){
    switch (idx)
    {
    case 0:
    case 3:
         sysPrintRectangle(120+idx*100 + idx*5,400,75,250,color);
         sysPrintRectangle(120+idx*100 + idx*5,650,100,50,color);
        break;
    
    case 2:
    case 6:
         sysPrintRectangle(120+20+idx*100 + idx*5,400,80,250,color);
         sysPrintRectangle(120+idx*100 + idx*5,650,100,50,color);
         break;
    case 1:
    case 4:
    case 5:
            sysPrintRectangle(120+20+idx*100 + idx*5,400,55,250,color);
            sysPrintRectangle(120+idx*100 + idx*5,650,100,50,color);
            break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
            sysPrintRectangle(120+70+(idx-7)*100 + (idx-7)*5,400,5,250,color);
            sysPrintRectangle(120+70+(idx-7)*100 + (idx-7)*5,650,60,5,color);
            sysPrintRectangle(120+75+50+(idx-7)*100 + (idx-7)*5,400,5,250,color);
            break;
    default:
        break;
    }
    
}

void piano(){
    initP();
    char c,k;
    while ((c = getchar()) != ESC)
    {   
        k = getReleaseKey();
        if(c >= '0' && c <= '8'){
            scale = (c - '0');
            scaleC[0] = c;
            sysSetCursorPosition(8,7);
            printColor(scaleC,YELLOW);
            sysSetCursorPosition(9,7);
            printColor("\n",YELLOW);
            continue;
        }
        if ( k == 's' || k == 'd' || k == 'f' || k == 'g' || k == 'h' || k == 'j' || k == 'k' || k == 'e'  || k == 'r'  || k == 'y'  || k == 'u'  || k == 'i')
        {
            sysSilence();
            if(press[0]){
                drawKey(0,WHITE);press[0] = 0;}
            if(press[1]){
                drawKey(1,WHITE);press[1] = 0;}
            if(press[2]){
                drawKey(2,WHITE);press[2] = 0;}
            if(press[3]){
                drawKey(3,WHITE);press[3] = 0;}
            if(press[4]){
                drawKey(4,WHITE);press[4] = 0;}
            if(press[5]){
                drawKey(5,WHITE);press[5] = 0;}
            if(press[6]){
                drawKey(6,WHITE);press[6] = 0;}
            if(press[7]){
                drawKey(7,WHITE);press[7] = 0;}
            if(press[8]){
                drawKey(8,WHITE);press[8] = 0;}
            if(press[10]){
                drawKey(10,WHITE);press[10] = 0;}
            if(press[11]){
                drawKey(11,WHITE);press[11] = 0;}
            if(press[12]){
                drawKey(12,WHITE);press[12] = 0;}
            continue;
        }
        else{
        
        switch (c)
        {
        case 's':
            sysPlaySound(notes[scale][0]);
            drawKey(0,BLACKPRESS);
            press[0] = 1;

            break;
        case 'e':
            sysPlaySound(notes[scale][1]);
            drawKey(7,BLACKPRESS);
            press[7] = 1;
            break;
        case 'd':
            sysPlaySound(notes[scale][2]);
            drawKey(1,BLACKPRESS);
            press[1] = 1;
            break;
        case 'r':
            sysPlaySound(notes[scale][3]);
            drawKey(8,BLACKPRESS);
            press[8] = 1;
            break;
        case 'f':
            sysPlaySound(notes[scale][4]);
            drawKey(2,BLACKPRESS);
            press[2] = 1;
            break;
        case 'g':
            sysPlaySound(notes[scale][5]);
            drawKey(3,BLACKPRESS);
            press[3] = 1;
            break;
        case 'y':
            sysPlaySound(notes[scale][6]);
            drawKey(10,BLACKPRESS);
            press[10] = 1;
            break;
        case 'h':
            sysPlaySound(notes[scale][7]);
            drawKey(4,BLACKPRESS);
            press[4] = 1;
            break;
        case 'u':
            sysPlaySound(notes[scale][8]);
            drawKey(11,BLACKPRESS);
            press[11] = 1;
            break;
        case 'j':
            sysPlaySound(notes[scale][9]);
            drawKey(5,BLACKPRESS);
            press[5] = 1;
            break;
        case 'i':
            sysPlaySound(notes[scale][10]);
            drawKey(12,BLACKPRESS);
            press[12] = 1;
            break;
        case 'k':
            sysPlaySound(notes[scale][11]);
            drawKey(6,BLACKPRESS);
            press[6] = 1;
            break;
        default:
            break;
        }
        }
    }
    sysClearScreen();
    sysSetZoomLevel(4);
    return;
}

void drawPiano(int idx){
    for (int i = 0,j=0; i < 7 *100;j++, i+=100)
    {
        if(idx != j){
       sysPrintRectangle(120+i + j*5,400,100,300,0x00FFFFFF);
        }
        else{
             sysPrintRectangle(120+i + j*5,400,100,300,0x00FFFF00);
        }
    
    }
    for (int i = 0,j=0; i < 6 *100;j++, i+=100)
    {
        if(j != 2){
       sysPrintRectangle(120+75+i + j*5,400,50,250,0x00000000);
        }
    }


}