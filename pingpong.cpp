#include<iostream>
#include<cstdlib>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
bool GameOver,pause;
int x1,x2,xm,ym,xc,yc,a,b,length,err,t=5,c,d; //x1 up x2 down
int y1,y2,p1,p2;
int lim=100; //spacing on the left and right
int step=25; //steps the paddles move on one key press

void ball();

void border()   //draw boundary limits
{
    line(lim-10,0,lim-10,ym);
    line(xm-2*lim+10,0,xm-2*lim+10,ym);
}

void drawer()   //draws paddles
{
    border();
    setfillstyle(1,YELLOW);
    bar(x1,y1,x1+length,y1-t);
    bar(x2,y2,x2+length,y2+t);
}

void Setup() //initialize the game
{
    pause=false;
    GameOver=false;
    xm=getmaxx();
    ym=getmaxy();
    x1=xm/2;
    x2=xm/2;
    y1=50;
    y2=ym-50;
    xc=x1;
    yc=200;
    a=3;
    b=3;
    length=60;
    err=10;
}

void ball() //control motion of ball
{
    if(c!=b)
    {
       d=rand()%15;
    }
    //setfillstyle(1,WHITE);//White ball
    setfillstyle(1,d);setcolor(d); // set color
    fillellipse(xc, yc,10,10);
    c=b;
  xc = xc + a;
  yc = yc + b;

  if(xc > xm-2*lim) { //check if ball touched right wall
    xc = xm-2*lim;
    a = -a;

  }
  if(yc > y2-t && xc<=x2+length && xc>=x2) {//check if ball touched the lower paddle
    yc = y2-t;
    b = -b;
  }
  if(xc < lim) { //check if ball touched the right wall
    xc = lim;
    a = -a;

  }
  if(yc < y1+t && xc<=x1+length && xc>=x1) { //check if ball touched the upper paddle
    yc = y1+t;
    b = -b;
  }

}

void Input()
{
    ball();
    if(kbhit())
    {
            switch(getch())
            {
            case 'p':
             {
                outtextxy(xm/2-100,ym/2,"Game is Paused");
                while(getch()!='p')
                {

                }
                cleardevice();
                drawer();
                break;
             }

            case 'a':
            {
                if(x1>lim+err)
                x1-=step;
                break ;
            }
            case 'd':
            {
                if(x1+length+err<xm-2*lim)
                x1+=step;
                break ;
            }

            case 75:
            {
                if(x2>lim+err)
                x2-=step;
                break ;
            }
            case 77:
            {
                if(x2+length+err<xm-2*lim)
                x2+=step;
                break ;
            }
            case 27:
            {
                exit(1);
            }
            default:
            {
                break;
            }
        }
    }
        cleardevice();
        drawer();
        ball();
}


int main()
{
    int gd=DETECT;
    int gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    Setup();
    outtextxy(200,100,"Ping pong");
    outtextxy(200,250,"Instructions:");
    outtextxy(200,270,"Press Esc to Exit");
    outtextxy(200,290,"Press P to Pause");
    outtextxy(200,330,"Controls:");
    outtextxy(200,350,"Player 1: A and D");
    outtextxy(200,370,"Player 2: left arrow and right arrow keys");
    outtextxy(200,410,"Press any key to continue.");
    getch();
    char arr[50],arr1[50];
    char stop=0;
    p1=0;p2=0;
    while(stop!=27)
    {
        Setup();
        while(!GameOver)
        {
            drawer();
            Input();
            Sleep(29);
            ball();
            Sleep(0.1);
            cleardevice();
            if(yc>ym-50)
            {
                GameOver=true;
                p1+=1;
            }
            if(yc<50)
            {
                GameOver=true;
                p2+=1;
            }
        }
        setcolor(WHITE);
        sprintf(arr,"p1:%d",p1);
        outtextxy(300,250,arr);
        sprintf(arr1,"p2:%d",p2);
        outtextxy(300,270,arr1);
        Sleep(2000);
        outtextxy(xm/4,ym/2+100,"Press Esc to exit or press any other key to continue");
        stop=getch();
    }
    cleardevice();
    outtextxy(xm/2,ym/2,"GameOver");
    getch();
    return 0;
}
