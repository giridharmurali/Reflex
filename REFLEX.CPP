//*********************REFLEX-The Game********************|
//------------------C>B>S>E-P>R>O>J>E>C>T-----------------|
//------------------By M.Giridhar XII F2------------------|
#include"dos.h"
#include"time.h"
#include"stdio.h"
#include"conio.h"
#include"ctype.h"
#include"stdlib.h"
#include"process.h"
#include"graphics.h"
//********************Global variables ********************//
//
int successflag=0,failureflag=0,speedcount=0;
int sel;
int regame=0;
int menucount=0;
int speed[15]={44,40,36,32,28,22,18,16,14,12,10,9,8,7,6};
int cy1=138,cy2=162;
char * dispscore="0";
char op;
class var                     //class to store score,level,speed info.
{
 public:
 char * a;
 char * scstr;
 char * lestr;
 char * spstr;
 int score;
 int level;
 var()
  {
    score=0;
	level=1;
    spstr="  ";
	a=" ";
    scstr="        ";
	lestr="  ";
  }
};
//*****************Functions Declarations*******************//
//
void init();                  //To initialize graphics
void score_brd(int b,var *s); //To calculate score each turn
void rrectangle(int x1,int y1,int x2,int y2,int rad,int fill=0);
			      //To display rectangle with rounded edges
void controls();              //To display controls menu
void abtgame();               //To display about:game menu
void abtprjt();               //To display about:project menu
void abtmen();                // To display about menu
void gammen();                // To display game menu
int about();                  // To execute about menu
int genzoom(var *s);          //To generate random alphabet and zoom.
void gamemanager(var *s);     //The game environment controller
void game();                  // The base game function
void fillpanel(int p,char* a);//To fill trials panel
void quit();                  // To display the ending graphics
void mainmenu();              // To display the mainmenu
int gamemainmen();            //To execute the game menu
void entrance();              //To display entrance screen
void platform();              //Basement function to carry out the game
void loading();               //To display loading banner
void playsound(int snd);
void abandon();
void main()
{
	 platform();
	 getch();
}
//*****************Function definitions***********************//
void abandon()
{
 setcolor(14);
 settextstyle(1,0,5);
 outtextxy(100,200,"GAME TERMINATED!");
 sleep(1);
 cleardevice();
 ::regame=1;
 ::successflag=0;
 ::failureflag=0;
 ::speedcount=0;
 platform();
}
void playsound(int snd)
 {
  int i;
 switch(snd)
 {
  case 1:
  {
  for(i=0;i<10;i++)
  {
  sound(1500);delay(10);
  sound(2000);delay(20);
  sound(2500);delay(30);
  sound(1000);delay(15);
  nosound();
 }
 break;
 }
case 2:
{
 for(i=10;i>0;i--)
  {
   sound(1000+(100*i)+(10*i)+(2*i));delay(200);
   sound(2500);delay(20);
   nosound();
  }
 break;
 }
 case 3:
  {
 for(i=2;i>0;i--)
 {
 sound(2000);delay(5);
 sound(550);delay(10);
 sound(750);delay(20);
 sound(2500);delay(15);
 nosound();
 }
 break;
 }
}
}
void init()
{
  int gd=DETECT,gm;
  initgraph(&gd,&gm,"");
}
void score_brd(int b,var *s)
{
  if(::speedcount==14)
  {
	cleardevice();
	setcolor(15);
	settextstyle(1,0,7);
	outtextxy(60,100,"Congratulations!");
	setcolor(14);
	settextstyle(1,0,4);
	outtextxy(55,200,"You have finished the challenge!");
	sleep(2);
	exit(0);
  }
  else
  {
	setcolor(1);
	settextstyle(2,0,5);
	outtextxy(81,getmaxy()-14,s->spstr);
	outtextxy(81,getmaxy()-30,s->lestr);
	settextstyle(1,0,3);
    outtextxy(532,getmaxy()-30,s->scstr);
    settextstyle(2,0,5);
	s->score=s->score+2+s->level;
    if(b%10==0)
	 {
      s->level++;
      ::speedcount++;
	 }
	moveto(getmaxx()-100,500);
	itoa(s->score,s->scstr,10);
    itoa(s->level,s->lestr,10);
    itoa(::speedcount+1,s->spstr,10);
    setcolor(15);
    settextstyle(1,0,3);
	outtextxy(532,getmaxy()-30,s->scstr);
    dispscore=s->scstr;
    s->scstr="        ";
    settextstyle(2,0,5);
	outtextxy(81,getmaxy()-30,s->lestr);
    s->lestr="  ";
	outtextxy(81,getmaxy()-14,s->spstr);
    s->spstr="  ";
  }
}
void game()
{
  cleardevice();
  var s;
  gamemanager(&s);
  char cont;
  cleardevice();
  setbkcolor(0);
  setcolor(15);
  settextstyle(1,0,3);
  outtextxy(230,220,"Play Again ?");
  outtextxy(240,260,"Yes / No");
  while(1)
  {
   cont=getch();
   if(cont=='n'||cont=='N')
	{
	  cleardevice();
	  quit();
	}
   else if(cont=='y'||cont=='Y')
	{
	 cleardevice();
	 ::regame=1;
	 ::successflag=0;
	 ::failureflag=0;
	 ::speedcount=0;
	 platform();
	}
  }
}
void rrectangle(int x1,int y1,int x2,int y2,int rad,int fill)
 {
  line(x1+rad,y1,x2-rad,y1);
  arc(x2-rad,y1+rad,0,90,rad);
  line(x2,y1+rad,x2,y2-rad);
  arc(x2-rad,y2-rad,270,360,rad);
  line(x2-rad,y2,x1+rad,y2);
  arc(x1+rad,y2-rad,180,270,rad);
  line(x1,y2-rad,x1,y1+rad);
  arc(x1+rad,y1+rad,90,180,rad);
  if(fill)
   floodfill((x1+x2)/2,(y1+y2)/2,getcolor());
 }
void controls()
{
  setbkcolor(0);
  setfillstyle(1,0);
  bar(0,0,getmaxx(),getmaxy());
  setcolor(1);
  rectangle(1,1,getmaxx()-1,getmaxy()-1);
  settextstyle(1,0,3);
  setcolor(2);
  outtextxy(200,10,"C-O-N-T-R-O-L-S");
  setcolor(1);
  line(1,45,getmaxx()-1,45);
  settextstyle(2,0,4);
  setcolor(15);
  outtextxy(50,80,"This game doesn't require any external help on controls.But anyway these hints would be of");
  outtextxy(50,100,"great use while you play 'REFLEX'.");
  setcolor(14);
  outtextxy(50,140,"YOU ARE SUPPOSED TO USE ONLY THE ALPHABETS WHILE YOU PLAY REFLEX.USE OF ANY OTHER KEY MAY");
  outtextxy(50,165,"RESULT IN UNWANTED LOSS IN LIFE.THIS GAME DOESN'T CONFUSE YOU ON THE PROPER KEY TO USE,BUT");
  outtextxy(50,190,"THE PROPER POSITION OF THE KEY....");
  setcolor(5);
  outtextxy(50,250,"WARNING : FAILING TO USE A KEY WHEN REQD.MAY ALSO LEAD TO A LIFE-LOSS.");
  setcolor(15);
  settextstyle(2,0,4);
  outtextxy(390,420,"Press space-bar to return to Game-Menu..");
  outtextxy(210,300,"For help regarding score scheme goto About->Game");
  while(1)
  {
    if(kbhit()!=0)
	 {
	  op=getch();
      if(int(op)==32)
	  break;
     }
   }
 }
void abtgame()
{
 setbkcolor(0);
 cleardevice();
 setcolor(15);
 settextstyle(2,0,5);
 outtextxy(320,450,"Press any key to go back to about menu..");
 setcolor(5);
 settextstyle(3,0,4);
 outtextxy(195,10,"ABOUT : GAME");
 setcolor(14);
 outtextxy(193,10,"ABOUT : GAME");
 settextstyle(2,0,5);
 outtextxy(30,100,"PLAYERS       : SINGLE");
 outtextxy(30,120,"SPEED         : INCREASES WITH LEVEL");
 outtextxy(30,140,"LEVELS        : 14");
 outtextxy(30,160,"TIME          : AS PER USER'S SPEED");
 outtextxy(30,180,"DIFFICULTY    : DEFAULT");
 outtextxy(30,200,"SCORE FORMULA : Score/turn = 2 + level");
 outtextxy(30,220,"LANGUAGE      : C++");
 setcolor(15);
 getch();
}
void abtprjt()
{
 cleardevice();
 setbkcolor(0);
 setcolor(15);
 settextstyle(2,0,5);
 outtextxy(320,450,"Press any key to go back to about menu..");
 setcolor(5);
 settextstyle(3,0,4);
 outtextxy(195,10,"ABOUT : PROJECT");
 setcolor(14);
 outtextxy(193,10,"ABOUT : PROJECT");
 settextstyle(2,0,6);
 outtextxy(30,100,"PROJECT      : C.B.S.E");
 outtextxy(30,120,"SUBJECT      : COMPUTER SCIENCE");
 outtextxy(30,140,"DEVELOPER    : M.GIRIDHAR");
 outtextxy(30,160,"CLASS        : XII F2");
 outtextxy(30,180,"SCHOOL       : P.S.B.B.Sr.Sec.School");
 outtextxy(30,200,"THANKS TO    : My Comp.Sci teachers Mrs.Latha,Mrs.Radhika,");
 outtextxy(180,220,"Mrs.Aruna,my parents,my brother and almighty.");
 outtextxy(180,240,"Finally I thank Mrs.Rukmini for her valuable");
 outtextxy(180,260,"suggestions..");
 setcolor(15);
 getch();
}
void abtmen()
{
  setbkcolor(0);
  settextstyle(3,0,4);
  setcolor(1);
  outtextxy(getmaxx()/2-90,10,"ABOUT-MENU");
  setcolor(15);
  outtextxy(getmaxx()/2-94,6,"ABOUT-MENU");
  setcolor(12);
  setfillstyle(2,BLUE);
  bar(getmaxx()/2-170,140,getmaxx()/2+140,160);
  bar(getmaxx()/2-170,200,getmaxx()/2+140,220);
  bar(getmaxx()/2-170,260,getmaxx()/2+140,280);
  settextstyle(3,0,3);
  setcolor(14);
  outtextxy(getmaxx()/2-50,134,"GAME");
  outtextxy(getmaxx()/2-65,194,"PROJECT");
  outtextxy(getmaxx()/2-40,254,"BACK");
  setcolor(12);
  settextstyle(2,0,5);
  outtextxy(200,getmaxy()-40,"Use arrow keys to navigate");
  outtextxy(210,getmaxy()-20,"Use return key to select");
  setcolor(11);
}
void gammen()
{
  setbkcolor(0);
  settextstyle(7,0,4);
  setcolor(BLUE);
  outtextxy(getmaxx()/2-90,10,"GAME-MENU");
  setcolor(WHITE);
  outtextxy(getmaxx()/2-94,6,"GAME-MENU");
  setcolor(12);
  setfillstyle(2,BLUE);
  bar(getmaxx()/2-170,140,getmaxx()/2+140,160);
  bar(getmaxx()/2-170,200,getmaxx()/2+140,220);
  bar(getmaxx()/2-170,260,getmaxx()/2+140,280);
  settextstyle(3,0,3);
  setcolor(14);
  outtextxy(getmaxx()/2-95,134,"PLAY REFLEX");
  outtextxy(getmaxx()/2-110,194,"VIEW CONTROLS");
  outtextxy(getmaxx()/2-40,254,"BACK");
  setcolor(12);
  settextstyle(2,0,5);
  outtextxy(200,getmaxy()-40,"Use arrow keys to navigate");
  outtextxy(210,getmaxy()-20,"Use return key to select");
  setcolor(11);
}
int about()
{
   while(1)
   {
	   cy1=138,cy2=162;
	   sel=1;
	   cleardevice();
	   abtmen();
	   rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
	   for(int i=0;;i++)
	   {
	if(i%2==0)
	 {
	  setcolor(1);
	 }
	else
	 setcolor(3);
	settextstyle(3,1,2);
	outtextxy(10,getmaxy()/2,"About Menu");
	outtextxy(12,getmaxy()/2,"About Menu");
	op=getch();
	if(int(op)==72)
	  {
		playsound(3);
		if(sel!=1)
		 {
		  setcolor(0);
		  rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
		  cy1-=60;
		  cy2-=60;
		  setcolor(11);
		  rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
		  sel--;
		 }
	   }
	if(int(op)==80)
	  {
		playsound(3);
	   if(sel!=3)
	    {
		 setcolor(0);
	     rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
	     cy1+=60;
		 cy2+=60;
	     setcolor(11);
	     rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
		 sel++;
	   }
	  }
	if(int(op)==13)
	{
	  if(sel==1)
	   {
	     abtgame();
		 break;
	   }
	  if(sel==2)
	   {
		abtprjt();
	    break;
	   }
	  if(sel==3)
	   {
		return 0;
	   }
	}
     }
  }
}
int genzoom(var *s)
{
  int t;
  char* alp;
  int asc;
  randomize();
  t=rand()%26;
  switch(t)                                 //To create maximum randomness.
  {
   case 1:
   {
     alp="S";
     asc=115;
	 break;
   }
   case 2:
   {
	 alp="A";
	 asc=97;
	 break;
   }
   case 3:
   {
     alp="H";
	 asc=104;
	 break;
   }
   case 4:
   {
	 alp="P";
	 asc=112;
	 break;
   }
   case 5:
   {
	 alp="Y";
     asc=121;
	 break;
   }
   case 6:
   {
	 alp="K";
     asc=107;
	 break;
   }
   case 7:
   {
     alp="N";
	 asc=110;
	 break;
   }
   case 8:
   {
	 alp="G";
     asc=103;
	 break;
   }
   case 9:
   {
	 alp="O";
     asc=111;
	 break;
   }
   case 10:
   {
	 alp="M";
     asc=109;
	 break;
   }
   case 11:
   {
     alp="F";
	 asc=102;
	 break;
   }
   case 12:
   {
	 alp="C";
     asc=99;
	 break;
   }
   case 13:
   {
     alp="J";
	 asc=106;
	 break;
   }
   case 14:
   {
	 alp="W";
	 asc=119;
	 break;
   }
   case 15:
   {
	 alp="Z";
     asc=122;
	 break;
   }
   case 16:
   {
	 alp="L";
     asc=108;
	 break;
   }
   case 17:
   {
     alp="X";
	 asc=120;
	 break;
   }
   case 18:
   {
	 alp="I";
	 asc=105;
	 break;
   }
   case 19:
   {
     alp="D";
     asc=100;
	 break;
   }
   case 20:
   {
	 alp="Q";
	 asc=113;
	 break;
   }
   case 21:
   {
     alp="B";
     asc=98;
	 break;
   }
   case 22:
   {
	 alp="E";
     asc=101;
	 break;
   }
   case 23:
   {
     alp="R";
     asc=114;
	 break;
   }
   case 24:
   {
	 alp="U";
	 asc=117;
	 break;
   }
   case 25:
   {
     alp="T";
	 asc=116;
	 break;
   }
   case 26:
   {
	 alp="V";
     asc=118;
	 break;
   }
   case 0:
   {
	 alp="V";
     asc=118;
	 break;
   }
 }
for(int q=0;q<80;q++)
{
  if(q==79)
  {
  setfillstyle(1,0);
  setcolor(0);
  }
  else
  {
  setfillstyle(1,5);
  setcolor(14);
  }
  int x=getmaxx()/2,y=getmaxy()/2;
  bar(x-q,y-q,x+q,y+q);
  rectangle(x-q+1,y-q+1,x+q-1,y+q-1);
  rectangle(x-q-1,y-q-1,x+q+1,y+q+1);
  settextstyle(1,0,q/10);
  if(q!=79)
  {
  if(q<25)
  setcolor(0);
  else
  setcolor(4);
  }
  else
  setcolor(0);
  outtextxy(x-q+24,y-q+34,alp);
  if(kbhit())
  {
	char ch=getch();
	ch=tolower(ch);
	if(int(ch)==asc)
	{
	 ::successflag++;
	 score_brd(::successflag,s);
	 setfillstyle(1,0);
	 bar(x-q-1,y-q-1,x+q+1,y+q+1);
	 return 0;
	 }
   if(int(ch)==13)
   {
	abandon();
   }
	 else
	 {
	   if(::failureflag<12)
	   {
		fillpanel(::failureflag,alp);
		::failureflag++;
	   }
	   else if(::failureflag==12)
	   {
	return 0;
	   }
	  }
	 }
delay(::speed[::speedcount]);
}
fillpanel(::failureflag,alp);
::failureflag++;
}
void gamemanager(var *s)
{
  setbkcolor(0);
  settextstyle(2,1,4);
  setcolor(14);
  outtextxy(0,3,"-TRIALS-");
  setcolor(5);
  rectangle(11,0,getmaxx(),54);
  setcolor(2);
  rectangle(13,2,getmaxx()-2,52);
  for(int i=0;i<600;i+=52)
  {
   setcolor(15);
   rectangle(15+i,6,65+i,48);
   }
   settextstyle(1,0,1);
   setcolor(2);
   outtextxy(36,14,"1");
   outtextxy(86,14,"2");
   outtextxy(136,14,"3");
   outtextxy(188,14,"4");
   outtextxy(240,14,"5");
   outtextxy(292,14,"6");
   outtextxy(344,14,"7");
   outtextxy(392,14,"8");
   outtextxy(442,14,"9");
   outtextxy(492,14,"10");
   outtextxy(542,14,"11");
   outtextxy(592,14,"12");
   setfillstyle(1,1);
   setcolor(15);
   bar3d(0,getmaxy()-30,getmaxx(),getmaxy(),1,20);
   settextstyle(2,0,4);
   setcolor(14);
   outtextxy(8,getmaxy()-28,"L E V E L : ");
   outtextxy(8,getmaxy()-12,"S P E E D : ");
   settextstyle(2,0,5);
   outtextxy(445,getmaxy()-22,"S C O R E : ");
   settextstyle(7,0,1);
   setcolor(15);
   outtextxy(145,getmaxy()-32,"Giridhar's");
   settextstyle(8,0,2);
   setcolor(14);
   outtextxy(250,getmaxy()-30,"REFLEX");
   setcolor(15);
   settextstyle(2,0,5);
   outtextxy(350,getmaxy()-60,"PRESS RETURN TO TERMINATE GAME");
   do
   {
	genzoom(s);
	delay(1);
	}while(::failureflag<12);
	settextstyle(7,0,5);
	setcolor(1);
	outtextxy(getmaxx()/2-130,getmaxy()/2-10,"GAME-OVER");
	setcolor(15);
	outtextxy(getmaxx()/2-127,getmaxy()/2-12,"GAME-OVER");
	settextstyle(7,0,1);
	delay(1000);
	setcolor(14);
	outtextxy(getmaxx()/2-100,getmaxy()/2+42,"Thanks for playing..");
	sleep(1);
	cleardevice();
	settextstyle(1,0,3);
	setcolor(14);
	outtextxy(150,200,"Your Score : ");
	outtextxy(340,200,dispscore);
	settextstyle(2,0,5);
	setcolor(15);
	sleep(3);
	outtextxy(getmaxx()-150,getmaxy()-50,"Press any key ...");
	getch();
   }
void fillpanel(int p,char* a)
{
  setfillstyle(1,5);
  bar(15+(52*p),6,65+(52*p),48);
  setcolor(14);
  rectangle(17+(52*p),8,63+(52*p),46);
  settextstyle(1,0,2);
  setcolor(15);
  outtextxy(32+(52*p),15,a);
}
void quit()
{
 int d=5,l=7,m=12,t=150;
 int midx=getmaxx()/2+5,midy=getmaxy()/2;
 cleardevice();
 setcolor(4);
 for(int r=0;r<200;r++)
 {
   setfillstyle(1,4);
   fillellipse(getmaxx()/2,getmaxy()/2,r,r);
   delay(5);
 }
 sleep(1);
 for(r=0;r<100;r++)
 {
   setfillstyle(1,0);
   fillellipse(getmaxx()/2,getmaxy()/2,r,r);
   delay(5);
 }
 settextstyle(8,0,4);
 setcolor(5);
 outtextxy(260,100,"REFLEX");
 settextstyle(3,0,1);
 setcolor(14);
 sleep(1);
 outtextxy(270,180,"Project by:");
 sleep(1);
 settextstyle(1,0,2);
 setcolor(d);
 outtextxy(midx-100,midy,"M");
 delay(t);
 setcolor(m);
 outtextxy(midx-100,midy,"M");
 delay(t);
 setcolor(l);
 outtextxy(midx-100,midy,"M");
 setcolor(d);
 outtextxy(midx-80,midy,".");
 delay(t);
 setcolor(m);
 outtextxy(midx-80,midy,".");
 delay(t);
 setcolor(l);
 outtextxy(midx-80,midy,".");
 setcolor(d);
 outtextxy(midx-70,midy,"G");
 delay(t);
 setcolor(m);
 outtextxy(midx-70,midy,"G");
 delay(t);
 setcolor(l);
 outtextxy(midx-70,midy,"G");
 setcolor(d);
 outtextxy(midx-50,midy,"I");
 delay(t);
 setcolor(m);
 outtextxy(midx-50,midy,"I");
 delay(t);
 setcolor(l);
 outtextxy(midx-50,midy,"I");
 setcolor(d);
 outtextxy(midx-30,midy,"R");
 delay(t);
 setcolor(m);
 outtextxy(midx-30,midy,"R");
 delay(t);
 setcolor(l);
 outtextxy(midx-30,midy,"R");
 setcolor(d);
 outtextxy(midx-10,midy,"I");
 delay(t);
 setcolor(m);
 outtextxy(midx-10,midy,"I");
 delay(t);
 setcolor(l);
 outtextxy(midx-10,midy,"I");
 setcolor(d);
 outtextxy(midx+10,midy,"D");
 delay(t);
 setcolor(m);
 outtextxy(midx+10,midy,"D");
 delay(t);
 setcolor(l);
 outtextxy(midx+10,midy,"D");
 setcolor(d);
 outtextxy(midx+30,midy,"H");
 delay(t);
 setcolor(m);
 outtextxy(midx+30,midy,"H");
 delay(t);
 setcolor(l);
 outtextxy(midx+30,midy,"H");
 setcolor(d);
 outtextxy(midx+50,midy,"A");
 delay(t);
 setcolor(m);
 outtextxy(midx+50,midy,"A");
 delay(t);
 setcolor(l);
 outtextxy(midx+50,midy,"A");
 setcolor(d);
 outtextxy(midx+70,midy,"R");
 delay(t);
 setcolor(m);
 outtextxy(midx+70,midy,"R");
 delay(t);
 setcolor(l);
 outtextxy(midx+70,midy,"R");
 sleep(1);
 outtextxy(290,280,"XII F2");
 sleep(2);
 setcolor(0);
 for(r=0;r<getmaxx()/4;r++)
 {
  line(r,0,r,getmaxy());
  line(getmaxx()-r,0,getmaxx()-r,getmaxy());
  delay(10);
 }
 sleep(1);
 for(r=0;r<getmaxy()/2;r++)
 {
   line(0,r,getmaxx(),r);
   line(0,getmaxy()-r,getmaxx(),getmaxy()-r);
   delay(20);
 }
 exit(0);
}
void mainmenu()
{
   ::menucount++;
   setbkcolor(BLACK);
   setfillstyle(1,MAGENTA);
   int xb=180,yb=0;
   for(int banner=0;banner<10;banner++)
   {
	 cleardevice();
	 setcolor(12);
	 bar3d(xb,yb,xb+230,yb+80,5,1);
	 settextstyle(3,0,4);
	 setcolor(14);
	 outtextxy(xb+40,yb+20,"-REFLEX-");
	 if(banner==0)
	 {
	  sleep(1);
	 }
	 yb+=12;
	 int z=0;
	 for(int j=0;j<banner;j++)
	 {
	   setcolor(12);
	   ellipse(240,z,0,360,4,6);
	   ellipse(350,z,0,360,4,6);
	   z+=12;
	  }
	  delay(120);
	 }
	 sleep(1);
	 setcolor(14);
	 setfillstyle(0,0);
	 setcolor(14);
	 circle(110,400,50);
	 circle(310,400,50);
	 circle(510,400,50);
	 setcolor(14);
	 settextstyle(2,1,6);
	 outtextxy(10,110,"Thrill to the core...");
	 settextstyle(3,0,3);
	 setcolor(14);
	 outtextxy(273,385,"A");
	 outtextxy(488,385,"E");
	 outtextxy(85,385,"G");
	 setcolor(5);
	 outtextxy(100,385,"AME");
	 outtextxy(288,385,"BOUT");
	 outtextxy(503,385,"XIT");
	 setcolor(6);
	 rrectangle(100,200,489,320,10);
	 setcolor(1);
	 rrectangle(102,202,487,318,10);
	 settextstyle(2,0,4);
	 setfillstyle(1,0);
	 bar(104,204,485,316);
	 setcolor(15);
	 outtextxy(105,205,"'REFLEX' as the name suggests , is a game to test your reflexes.");
	 outtextxy(105,220,"In this game a random alphabet is zoomed onto the screen and you ");
	 outtextxy(105,235,"are supposed to hit the key corresponding to that alphabet.But the");
	 outtextxy(105,250,"challenge becomes tougher as you proceed... As the levels progress");
	 outtextxy(105,265,"the game gains speed and before you could take a look at the");
	 outtextxy(105,280,"alphabet,it's gone.So,get ready to grip your keys!");
	 outtextxy(365,300,"- M . Giridhar XII F2");
	 setcolor(12);
	 settextstyle(2,0,5);
	 outtextxy(200,getmaxy()-20,"G-> Game A-> About E-> Exit");
	 if(::menucount==1)
	 playsound(2);
	}
int gamemainmen()
{
   while(1)
   {
	 cy1=138,cy2=162;
	 sel=1;
	 cleardevice();
	 gammen();
	 rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
	 for(int i=0;;i++)
	 {
	if(i%2==0)
	 {
	  setcolor(1);
	  delay(2);
	 }
	 else
	 setcolor(3);
	 settextstyle(3,1,2);
	 outtextxy(10,getmaxy()/2,"Reflex Game Menu");
	 outtextxy(12,getmaxy()/2,"Reflex Game Menu");
	op=getch();
	if(int(op)==72)
	  {
		playsound(3);
	   if(sel!=1)
	   {
		 setcolor(0);
		 rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
		 cy1-=60;
		 cy2-=60;
		 setcolor(11);
		 rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
		 sel--;
	   }
	  }
	if(int(op)==80)
	{
	  playsound(3);
	  if(sel!=3)
	   {
		 setcolor(0);
		 rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
		 cy1+=60;
		 cy2+=60;
		 setcolor(11);
		 rrectangle(getmaxx()/2-172,cy1,getmaxx()/2+142,cy2,5);
		 sel++;
	   }
	}
	if(int(op)==13)
	{
	  if(sel==1)
	  {
		game();
		break;
	  }
	  if(sel==2)
	  {
		controls();
		break;
	  }
	  if(sel==3)
	  {
		return 0;
	  }
	   }
	}
  }
}
void loading()
{
   settextstyle(3,0,1);
   setcolor(15);
   setbkcolor(0);
   outtextxy(getmaxx()/2-80,getmaxy()-50,"L o a d i n g . . .");
   for(int telebanner=getmaxx()/2-80;telebanner<getmaxx()/2+82;telebanner++)
	{
	  if(telebanner%4==0)
	  setcolor(14);
	  else
	  setcolor(RED);
	  line(telebanner,getmaxy()-20,telebanner,getmaxy()-16);
	  delay(80);
	 }
   delay(500);
   setcolor(0);
   setfillstyle(1,0);
   playsound(1);
   bar(getmaxx()/2-150,getmaxy()-100,getmaxx()/2+100,getmaxy()-10);
 }
void entrance()
	{
	 randomize();
	 int *ptx,*pty;
	 ptx=new int[600];
	 pty=new int[600];
	 for(int i=0;i<600;i++)
	   {
		 ptx[i]=random(getmaxx())+1;
		 pty[i]=random(getmaxy())+1;
		 putpixel(ptx[i],pty[i],LIGHTGRAY);
	   }
	  setcolor(GREEN);
	  settextstyle(10,0,7);
	  outtextxy(55,20,"  REFLEX  ");
	  setcolor(1);
	  settextstyle(3,0,2);
	  outtextxy(getmaxx()/2-110,200,"By:");
	  setcolor(14);
	  outtextxy(getmaxx()/2-75,200,"M.GIRIDHAR XII-F2");
	  time_t t1,t2;
	  t2=time(NULL);
	  setcolor(BLACK);
	  settextstyle(3,0,4);
	  loading();
	  while(1)
		{
		 t1=time(NULL);
		 int k=random(600);
		 for(int j=0;j<k;j++)
		{
		  i=random(600);
		  putpixel(ptx[i],pty[i],WHITE);
		}
		if(t1-t2>=1) setcolor(WHITE);
		if(t1-t2>=2) {setcolor(BLACK); t2=t1;}
		if(kbhit())
			if(getch()==13)
			 {
			  cleardevice();
			  break;
			 }
		settextstyle(3,0,4);
		outtextxy(221,400,"PRESS ENTER");
		for(j=0;j<600;j++)
		  {
			putpixel(ptx[j],pty[j],LIGHTGRAY);
		   }
		}
   delete[]ptx;
   delete[]pty;
 }
void platform()
{
 if(::regame==0)
 {
  init();
  setbkcolor(BLACK);
  entrance();
 }
  while(1)
  {
   cleardevice();
   mainmenu();
   while(1)
   {
	op=getch();
	op=tolower(op);
	if(op=='g')
	{
	  setfillstyle(SOLID_FILL,BLACK);
	  bar3d(0,0,getmaxx(),getmaxy(),1,0);
	  gamemainmen();
	  break;
   }
	if(op=='a')
	{
	  setfillstyle(SOLID_FILL,BLACK);
	  bar3d(0,0,getmaxx(),getmaxy(),1,0);
	  about();
	  break;
	}
	if(op=='e')
	{
	  quit();
	}
  }
  }
}
