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
int x1,x2,xm,y1,y2,ym; //UpperPaddle(x1,y1), LowerPaddle(x2,y2)
int length,err,t=5;//length of paddle; t= thickness of paddle;
int xc,yc;//position of ball
int c,d;// used for randomizing colors
char arr[50],arr1[50];//for displaying scores
int a,b;//increments along x and y axis for the ball(a,b)
int lim=100; //spacing on the left and right
int step=20; //steps the paddles move on one key press
int cal;
int p1,p2;//scores of player 1 and player 2
char stop;//check if esc is pressed
int lvl;
void ball();//controls ball's movements
void game();//sets up the game
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
    xm=getmaxx()-9;
    ym=getmaxy();
    x1=xm/2;
    x2=xm/2;
    y1=50;
    y2=ym-50;
    xc=x1;
    yc=ym/2;
    a=2*((rand()%10)%2?1:-1);
    b=2*((rand()%10)%2?1:-1);
    length=60;
    err=10;
    cal=0;
    stop=0;
    lvl=2;

}

void ball() //control motion of ball
{
    if(c!=b)
    {
       d=rand()%15;
       if(d==BLACK || d==BLUE)
            d=2;
    }
    //setfillstyle(1,WHITE);//White ball
    setfillstyle(1,d);setcolor(d); // set color
    fillellipse(xc, yc,10,10);
    a=(((rand()%10)%2)+2)*a/abs(a);
    b=(((rand()%10)%2)+2)*b/abs(b);
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
void render()
{
    setfillstyle(1,d);setcolor(d); // set color
    fillellipse(xc, yc,10,10);
}

void Input2()//for single player input
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
                game();
            }
            default:
            {
                break;
            }
        }
    }
    if(yc<ym/2 && b<=0) // computer's paddle control
        {
            cal+=1;
            if(cal==lvl)
            {
            if(xc<=x1 && x1-step>lim)
            {
                x1-=step;
            }
            if(xc>=x1+length && x1+length+step<xm-lim)
            {
                x1+=step;
            }
            cal=0;
            }
        }

        cleardevice();
        drawer();
        ball();
}

void Input()//double player paddle control
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
                if(x1+length+err-10<xm-2*lim)
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
                if(x2+length+err-10<xm-2*lim)
                x2+=step;
                break ;
            }
            case 27:
            {
                game();
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

void singlePlayer()//configuration for single player mode
{

    while(stop!=27)
    {   Setup();
        while(!GameOver)
        {
            drawer();
            Input2();
            Sleep(40);
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
        do
        {
            outtextxy(xm/3,ym/2+100,"Press Esc to exit or press Enter to continue");
            stop=getch();

        }while(stop!=13 && stop!=27);
    }
}

void doublePlayer()//configuration for double player mode
{

    while(stop!=27)
    {
        Setup();
        while(!GameOver)
        {
            drawer();
            Input();
            Sleep(25);
            render();
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
}

    void game()//main game set up HOMESCREEN
    {
    cleardevice();
    setcolor(WHITE);
    int mod=2;
    Setup();
    outtextxy(200,100,"Ping pong");
    outtextxy(200,190,"Main Menu");
    outtextxy(200,220,"1.Single Player");
    outtextxy(200,250,"2.Double Player");
    char in;
    do{
    in=getch();
    if(in=='1')
        mod=0;
    else if(in=='2')
        mod=1;
    else if(in==21)
        exit(1);
    else
    {
        outtextxy(200,320,"INVALID OPTION");
    }

    }while(mod==2);
    cleardevice();
    outtextxy(200,100,"Ping pong");
    outtextxy(200,250,"Instructions:");
    outtextxy(200,270,"Press Esc to Exit TO MAIN MENU");
    outtextxy(200,290,"Press P to Pause");
    outtextxy(200,330,"Controls:");

    if(mod==0)
    {
            outtextxy(200,370,"Player: left arrow and right arrow keys");
            outtextxy(200,410,"Press any key to continue.");
            if(getch()==27)
                game();
            p1=0;p2=0;
            singlePlayer();
    }

    else
    {
            outtextxy(200,350,"Player 1: A and D");
            outtextxy(200,370,"Player 2: left arrow and right arrow keys");
            outtextxy(200,410,"Press any key to continue.");
            if(getch()==27)
                game();
            getch();
            p1=0;p2=0;
            doublePlayer();
    }
    };
int main()
{
    int gd=DETECT;
    int gm;
    initgraph(&gd,&gm,"C:\\TC\\BGI");
    do
    {
    game();
    cout<<xm;
    cleardevice();
    outtextxy(xm/2-50,ym/2,"GameOver");
    outtextxy(100,300,"Press esc to close the game and any other key to return to main menu");
    }while(getch()!=27);
    return 0;
}

