#include "iGraphics.h"
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#define PI acos(-1)
int w=1366;
int h=768;
int mid=h/2;


int st=0;
int chicken_x=0;
int basket_x=w/2;
int dir=10;
typedef struct Node node;
struct Node{
    int x,y;
};
node eggs[4];
int id=0,tm=0;
int score=0;
char str[1000];
char str_time[1000];
int check=1;
int type[4];
char Score[]="SCORE:";
int TIME;
int time_elapsed=0;
//clock_t start_time=0,end_time;
int tme;
typedef struct Player player;
struct Player{
    char name[200];
    int sc;
};
const int N=10;
player info[N];
int mode=0;
int len=0;
char name_str[200];
char saved_name[200];
int game_end=0;
int show_2=0,show_3=0;


void swap(player* xp,player* yp)
{
    player temp;
    strcpy(temp.name,xp->name);
    temp.sc=xp->sc;
    strcpy(xp->name,yp->name);
    xp->sc=yp->sc;
    strcpy(yp->name,temp.name);
    yp->sc=temp.sc;
}


void selectionSort()
{
    int i, j, max_idx;
    for (i = 0; i < N-1; i++)
    {
        max_idx = i;
        for (j = i+1; j < N; j++)
        if(info[j].sc > info[max_idx].sc)
            max_idx = j;
        swap(&info[i], &info[max_idx]);
    }
}

//void calc_time()
//{
//    end_time=clock();
//    time_elapsed=(double)(end_time-start_time)/CLOCKS_PER_SEC;
//}


void new_game()
{
    FILE* fp=fopen("newgame.txt","r");
    if(!fp){
        printf("Error opening file\n");
        exit(0);
    }
    fscanf(fp,"%d",&id);
    fscanf(fp,"%d%d%d%d%d%d%d%d",&type[id],&chicken_x,&eggs[id].x,&eggs[id].y,&basket_x,&time_elapsed,&TIME,&score);
    printf("%d %d %d %d %d %d %d %d %d",id,type[id],chicken_x,eggs[id].x,eggs[id].y,basket_x,time_elapsed,TIME,score);
    for(int i=0;i<4;i++)
    {
        if(i!=id){
            eggs[i].y=2*h;
        }
    }
    fclose(fp);
}



void resume_read()
{
    FILE* fp=fopen("resume.txt","r");
    if(!fp){
        printf("Error opening file\n");
        exit(0);
    }
    fscanf(fp,"%d",&id);
    fscanf(fp,"%d%d%d%d%d%d%d%d",&type[id],&chicken_x,&eggs[id].x,&eggs[id].y,&basket_x,&time_elapsed,&TIME,&score);
    printf("%d %d %d %d %d %d %d %d %d",id,type[id],chicken_x,eggs[id].x,eggs[id].y,basket_x,time_elapsed,TIME,score);
//    for(int i=0;i<4;i++)
//    {
//        if(i!=id){
//            eggs[i].y=2*h;
//        }
//    }
    fclose(fp);
}


void resume_write()
{
    FILE* fp=fopen("resume.txt","w");
    if(!fp){
        printf("Error opening file\n");
        exit(0);
    }
    fprintf(fp,"%d %d %d %d %d %d %d %d %d",id,type[id],chicken_x,eggs[id].x,eggs[id].y,basket_x,time_elapsed,TIME,score);
    fclose(fp);
}


void resume_write1()
{
    FILE* fp=fopen("resume.txt","w");
    if(!fp){
        printf("Error opening file\n");
        exit(0);
    }
    int i=(id-1);
    if(i<0) i+=4;
    fprintf(fp,"%d %d %d %d %d %d %d %d %d",i,type[i],chicken_x,eggs[i].x,eggs[i].y,basket_x,time_elapsed,TIME,score);
    fclose(fp);
}

void change()
{
    if(st==2){
        time_elapsed++;
        type[id]=(rand() % (3-0+1))+0;
        chicken_x=(rand() % (w - 0 + 1)) + 0;
        eggs[id].x=chicken_x;
        eggs[id].y=1.5*mid;
        id=(id+1)%4;
        //calc_time();
        if(time_elapsed>=TIME) st=3;
    }
}

void change1()
{
    if(st==2) for(int i=0;i<4;i++) if(eggs[i].y<=1.5*mid) eggs[i].y-=50;
}


void update2()
{
    FILE* fp= fopen("highscore2.txt","r");
    if(!fp){
        printf("Error opening file\n");
        exit(0);
    }
    int i=0;
    for(i=0;i<N;i++) fscanf(fp,"%d %[^\n]%*c",&info[i].sc,info[i].name);
    selectionSort();
    //for(i=0;i<N;i++) printf("%d %s\n",info[i].sc,info[i].name);
    int min_score=info[N-1].sc;
    fclose(fp);
    FILE* fw=fopen("highscore2.txt","w");
    if(!fw){
        printf("Error opening file\n");
        exit(0);
    }
    if(score>=min_score){
        strcpy(info[N-1].name,saved_name);
        info[N-1].sc=score;
    }
    selectionSort();
    for(i=0;i<N;i++) fprintf(fw,"%d %s\n",info[i].sc,info[i].name);
    fclose(fw);
    game_end=0;
    st=4;
    show_2=1;
    show_3=0;
}



void update3()
{
    FILE* fp= fopen("highscore3.txt","r");
    if(!fp){
        printf("Error opening file\n");
        exit(0);
    }
    int i=0;
    for(i=0;i<N;i++) fscanf(fp,"%d %[^\n]%*c",&info[i].sc,info[i].name);
    selectionSort();
    //for(i=0;i<N;i++) printf("%d %s\n",info[i].sc,info[i].name);
    int min_score=info[N-1].sc;
    fclose(fp);
    FILE* fw=fopen("highscore3.txt","w");
    if(!fw){
        printf("Error opening file\n");
        exit(0);
    }
    if(score>=min_score){
        strcpy(info[N-1].name,saved_name);
        info[N-1].sc=score;
    }
    selectionSort();
    for(i=0;i<N;i++) fprintf(fw,"%d %s\n",info[i].sc,info[i].name);
    fclose(fw);
    game_end=0;
    st=4;
    show_3=1;
    show_2=0;
}


void show_highscore2()
{
    FILE* fp=fopen("highscore2.txt","r");
    if(!fp){
        printf("Error opening file\n");
        exit(0);
    }
    for(int i=0;i<N;i++){
        fscanf(fp,"%d %[^\n]%*c",&info[i].sc,info[i].name);
        char temp1[200],temp2[200],space[]="  ";
        strcpy(temp1,info[i].name);
        itoa(info[i].sc,temp2,10);
        strcat(temp1,space);
        strcat(temp1,temp2);
        iText(w/2-200,mid*1.5-(i+1)*30,temp1,GLUT_BITMAP_TIMES_ROMAN_24);
    }
    fclose(fp);
}


void show_highscore3()
{
    FILE* fp=fopen("highscore3.txt","r");
    if(!fp){
        printf("Error opening file\n");
        exit(0);
    }
    for(int i=0;i<N;i++){
        fscanf(fp,"%d %[^\n]%*c",&info[i].sc,info[i].name);
        char temp1[200],temp2[200],space[]="  ";
        strcpy(temp1,info[i].name);
        itoa(info[i].sc,temp2,10);
        strcat(temp1,space);
        strcat(temp1,temp2);
        iText(w/2-200,mid*1.5-(i+1)*30,temp1,GLUT_BITMAP_TIMES_ROMAN_24);
    }
    fclose(fp);
}


void iDraw()
{
    iClear();
    if(st==0){
        iShowBMP(0,0,"menu.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(0.75*w,1.5*mid,200,75);
        iSetColor(255,255,255);
        iText(0.75*w+30,1.5*mid+30,"CONTINUE",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,0,0);
        iFilledRectangle(0.75*w,1.5*mid-100,200,75);
        iSetColor(255,255,255);
        iText(0.75*w+30,1.5*mid+30-100,"NEW GAME",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,0,0);
        iFilledRectangle(0.75*w,1.5*mid-200,200,75);
        iSetColor(255,255,255);
        iText(0.75*w+30,1.5*mid+30-200,"HIGHSCORE",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,0,0);
        iFilledRectangle(0.75*w,1.5*mid-300,200,75);
        iSetColor(255,255,255);
        iText(0.75*w+30,1.5*mid+30-300,"EXIT",GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if(st==1){
        iShowBMP(0,0,"time.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(0.75*w,1.5*mid,200,75);
        iSetColor(255,255,255);
        iText(0.75*w+30,1.5*mid+30,"SELECT TIME:",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,0,0);
        iFilledRectangle(0.75*w,1.5*mid-100,200,75);
        iSetColor(255,255,255);
        iText(0.75*w+30,1.5*mid+30-100,"2 MIN",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,0,0);
        iFilledRectangle(0.75*w,1.5*mid-200,200,75);
        iSetColor(255,255,255);
        iText(0.75*w+30,1.5*mid+30-200,"3 MIN",GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if(st==2){
        iShowBMP(0,0,"background.bmp");
        iSetColor(0,0,0);
        iLine(0,1.5*mid,w,1.5*mid);
        iSetColor(0,0,0);
        iFilledRectangle(w-200,h-100,200,100);
        iFilledRectangle(0,h-70,200,70);
        iShowBMP2(chicken_x,1.5*mid-3,"chicken.bmp",0x00ffffff);
        iShowBMP2(basket_x,100,"basket.bmp",0x00ffffff);
        itoa(score,str,10);
        tme=(int)time_elapsed;
        itoa(tme,str_time,10);
        iSetColor(255,255,255);
        iText(10,h-40,"TIME:",GLUT_BITMAP_TIMES_ROMAN_24);
        iText(100,h-40,str_time,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(w-195,h-50,Score,GLUT_BITMAP_TIMES_ROMAN_24);
        iText(w-100,h-50,str,GLUT_BITMAP_TIMES_ROMAN_24);
        for(int i=0;i<4;i++){
            if(eggs[i].y>=150){
                if(type[i]==0)iShowBMP2(eggs[i].x,eggs[i].y,"egg.bmp",0x00ffffff);
                if(type[i]==1)iShowBMP2(eggs[i].x,eggs[i].y,"blueegg.bmp",0x00ffffff);
                if(type[i]==2)iShowBMP2(eggs[i].x,eggs[i].y,"goldenegg.bmp",0x00ffffff);
                if(type[i]==3)iShowBMP2(eggs[i].x,eggs[i].y,"poop.bmp",0x00ffffff);
            }
            if(eggs[i].y<150){
                eggs[i].y=2*h;
                if(eggs[i].x>=basket_x && eggs[i].x+10<=basket_x+105){
                    iShowBMP2(basket_x,100,"basket.bmp",0x00ffffff);
                    if(type[i]==0) score++;
                    if(type[i]==1) score+=5;
                    if(type[i]==2) score+=10;
                    if(type[i]==3) score-=10;
                    itoa(score,str,10);
                    iSetColor(255,255,255);
                    iText(w-100,h-50,str,GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(w-195,h-50,Score,GLUT_BITMAP_TIMES_ROMAN_24);
                }
                else{
                    if(type[i]!=3) iShowBMP2(eggs[i].x,100,"cracked.bmp",0x00ffffff);
                    else iShowBMP2(eggs[i].x,100,"poop.bmp",0x00ffffff);
                    iShowBMP2(basket_x,100,"basket.bmp",0x00ffffff);
                }
            }
        }
    }
    if(st==3){
        //iShowBMP(0,0,"gameover.bmp");
        iShowBMP(0,0,"highscore.bmp");
        iSetColor(0,0,0);
        iFilledRectangle(0.75*w-100,1.5*mid,225,75);
        iSetColor(255,255,255);
        char SS[]="Your Score:  ";
        strcat(SS,str);
        iText(0.75*w+30-100,1.5*mid+30,SS,GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,0,0);
        iFilledRectangle(0.75*w-100,1.5*mid-100,325,75);
        iSetColor(255,255,255);
        iText(0.75*w+15-100,1.5*mid+30-100,"Your Name: ",GLUT_BITMAP_TIMES_ROMAN_24);
        if(mode){
            iSetColor(255,255,255);
            iText(0.75*w+50,1.5*mid+30-100,name_str,GLUT_BITMAP_TIMES_ROMAN_24);
        }
        if(game_end && TIME==120) update2();
        if(game_end && TIME==180) update3();
    }
    if(st==4){
        iShowBMP(0,0,"halloffame.bmp");
        if(show_2){
            iText(w/2,mid*1.5,"HALL OF FAME FOR TWO MINUTES:",GLUT_BITMAP_TIMES_ROMAN_24);
            show_highscore2();
        }
        if(show_3){
            iText(w/2,mid*1.5,"HALL OF FAME FOR THREE MINUTES:",GLUT_BITMAP_TIMES_ROMAN_24);
            show_highscore3();
        }
    }
    if(st==5){
        iShowBMP(0,0,"halloffame.bmp");
        iText(w/2-150,mid*1.5,"HALL OF FAME",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255);
        iRectangle(w/2-150,1.5*mid-100,200,75);
        iSetColor(255,255,255);
        iText(w/2-150+30,1.5*mid+30-100,"FOR 2 MIN:",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(255,255,255);
        iRectangle(w/2-150,1.5*mid-200,200,75);
        iSetColor(255,255,255);
        iText(w/2-150+30,1.5*mid+30-200,"FOR 3 MIN:",GLUT_BITMAP_TIMES_ROMAN_24);
    }
}


void iKeyboard(unsigned char key)
{
//    if(st==0) if(key=='m'|| key=='M') st=2;
    if(st==1){
        if(key=='b' || key=='B'){
            st=0;
        }
    }
    if(st==2){
        if(key=='p' || key=='P'){ iPauseTimer(0); iPauseTimer(1); }
        if(key=='r' || key=='R'){ iResumeTimer(0); iResumeTimer(1); }
        if(key=='m'|| key=='M'){
            st=0;
            resume_write();
        }
    }
    if(st==3){
        if(mode){
            if(key=='\r'){
                game_end=1;
                strcpy(saved_name,name_str);
                //printf("%s %d\n",saved_name,score);
                mode=0;
                name_str[0]=0;
                len=0;
            }
            else if(key=='\b'){
                name_str[len-1]=' ';
                len--;
            }
            else{
                name_str[len++]=key;
            }
        }
    }
    else if(st==4){
        if(key=='b' || key=='B'){
            st=5;
            if(show_2) show_2=0;
            if(show_3) show_3=0;
            //if(TIME) TIME=0;
        }
    }
    else if(st==5){
        if(key=='b' || key=='B'){
            st=0;
            if(show_2) show_2=0;
            if(show_3) show_3=0;
            //if(TIME) TIME=0;
        }
    }
}



void iSpecialKeyboard(unsigned char key)
{
    if(key==GLUT_KEY_LEFT){
        if(basket_x-75 <=0) basket_x=0;
        else basket_x-=40;
    }
    if(key==GLUT_KEY_RIGHT){
        if(basket_x+75 >= w) basket_x=w-150;
        else basket_x+=40;
    }
    if(key== GLUT_KEY_END){
        resume_write1();
        exit(0);
    }
}


void iMouseMove(int mx, int my)
{
    basket_x=mx;
    if(basket_x<0) basket_x=0;
    if(basket_x>w-150) basket_x=w-75;
}


void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(st==0){
            if(mx>=0.75*w && mx<=(0.75*w+200) && my>=1.5*mid && my<=(1.5*mid+75)){
                resume_read();
                if(TIME==0) exit(0);
                st=2;
            }
            else if(mx>=0.75*w && mx<=(0.75*w+200) && my>=(1.5*mid-100) && my<=(1.5*mid+75-100)){
                st=1;
            }
            else if(mx>=0.75*w && mx<=(0.75*w+200) && my>=(1.5*mid-200) && my<=(1.5*mid+75-200)){
                st=5;
            }
            else if(mx>=0.75*w && mx<=(0.75*w+200) && my>=(1.5*mid-300) && my<=(1.5*mid+75-300)){
                //resume_write();
                exit(0);
            }
        }
        else if(st==1){
            if(mx>=0.75*w && mx<=(0.75*w+200) && my>=1.5*mid && my<=(1.5*mid+75)){

            }
            else if(mx>=0.75*w && mx<=(0.75*w+200) && my>=(1.5*mid-100) && my<=(1.5*mid+75-100)){
                st=2;
                new_game();
                TIME=120;
                //TIME=5;
                //start_time=clock();
            }
            else if(mx>=0.75*w && mx<=(0.75*w+200) && my>=(1.5*mid-200) && my<=(1.5*mid+75-200)){
                st=2;
                new_game();
                TIME=180;
                //TIME=5;
                //start_time=clock();
            }
        }
        else if(st==3){
            if(mx>=0.75*w && mx<=(0.75*w+225) && my>=(1.5*mid-100) && my<=(1.5*mid-100+75)){
                mode=1;
            }
        }
        else if(st==5){
            if(mx>=(w/2 -150) && mx<=(w/2 - 150+ 200) && my>=(1.5*mid-100) && my<=(1.5*mid-100+75)){
                st=4;
                show_2=1;show_3=0;
            }
            else if(mx>=(w/2 -150) && mx<=(w/2 - 150+ 200) && my>=(1.5*mid-200) && my<=(1.5*mid-200+75)){
                st=4;
                show_3=1;show_2=0;
            }
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {


    }
}


int main()
{
    iSetTimer(1000,change);
    iSetTimer(100,change1);
    iInitialize(w,h,"game");
    return 0;
}
