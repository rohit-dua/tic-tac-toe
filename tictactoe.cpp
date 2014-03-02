#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#include<dos.h>
#include<process.h>
#include<graphics.h>
#define unit 6
#define matx 30
#define maty 5


void circle0(float x,float y,float r=2*unit/5)
{
 float y1,y2,x1,ycord;
 for(x1=x-r;x1<=x+r;x1=x1+0.01)
 {
  ycord=sqrt(pow(r,2)-pow(x1-x,2));
  y1=ycord+y;
  y2=y-ycord;
  gotoxy(x1,y1);
	printf(".");
  gotoxy(x1,y2);
	printf(".");
 }
}



void line0(int x1, int y1, int x2, int y2)
{
 float x,y;
 char c;
 if(x1==x2)
  c='|';
 else if(y1==y2)
   c='-';
 else
  c='.';
 if(x1==x2)
 {
  for(y=y1;y<=y2;y=y+0.01)
  {
	gotoxy(x1,y);
	printf("%c",c);
  }
 }
 else
  for(x=x1;x<=x2;x=x+0.01)
  {
	y=y1+(((y2-y1)/(x2-x1))*(x-x1));
	gotoxy(x,y);
	printf("%c",c);
  }

}




float dist(int x1, int y1, int x2, int y2)
{
 return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}




int aprintf(char txt[50], char type='s',int x=1, int y=unit*4+maty+7,int time=50)     //Animated printf()
{
 int i,temp;
 if(type=='c')
 {
  if(x==1)
  {
   gotoxy(x,y);
   printf("\t\t\t\t\t\t\n\t\t\t\t\t\n\t\t\t\t\t\t");
  }
  else
   {
   gotoxy(x,y);
   printf("\t\t");
   }
  gotoxy(x,y);
 }
 for(i=0;txt[i]!='\0';i++)
 {

  printf("%c",txt[i]);
  delay(time);
 }
 return 0;
}




void cross(int x, int y)
{
 float u=2*unit/5;
 line0(x-u,y-u,x+u,y+u);
 line0(x-u,y+u,x+u,y-u);
}




void matrix(float x, float y)
{
 int i=1,xcoord,ycoord;
 line0(x,y,x,y+unit*3);                        	  //left vertical
 line0(x+unit,y,x+unit,y+unit*3);                   //right vertical
 line0(x-unit,y+unit,x+2*unit,y+unit);              //up horizontal
 line0(x-unit,y+(2*unit),x+2*unit,y+(2*unit));      //down horizontal
 for(ycoord=y+unit-1;ycoord<y+unit*3;ycoord+=unit)
 {
  for(xcoord=x-1;xcoord<x+unit*2;xcoord+=unit)
  {
	gotoxy(xcoord,ycoord);
	printf("%d",i++);
  }
 }
}




void draw(int choice, int region, int quad[9])    //quad[9] to assign symbol value before drawing
{
 quad[region-1]=choice;
 float x[3],y[3];
 int a,b;
 x[0]=matx-unit/2; y[0]=maty+unit/2;
 x[1]=x[0]+unit; y[1]=y[0]+unit;
 x[2]=x[1]+unit; y[2]=y[1]+unit;
 switch(region)
 {
  case 1: a=0,b=0;
			 break;
  case 2: a=1,b=0;
			 break;
  case 3: a=2,b=0;
			 break;
  case 4: a=0,b=1;
			 break;
  case 5: a=1,b=1;
			 break;
  case 6: a=2,b=1;
			 break;
  case 7: a=0,b=2;
			 break;
  case 8: a=1,b=2;
			 break;
  case 9: a=2,b=2;
			 break;
 }
 if(choice==1)
  circle0(x[a],y[b]);
 else if(choice==2)
  cross(x[a],y[b]);
}



int* checkmat(int quad[9], int sno) //sno- bot's symbol number(0:1 X:2)
{
 /*KEY:b:bot's  u:user's
 6-points*scores
 5-b triplet
 4-u triplet
 3-b double trick
 2-u double trick
 1-b doublet
 0-u doublet
 */

 /*
 Points:
 b triplet +4
 b double trick +1
 u doublet  -2
 */

 /*
 Address:
 1:col 1
 2:col 2
 3:col 3
 4:row 1
 5:row 2
 6:row 3
 7:diagonal L TO R
 8:diagonal R TO L
 */

  int i,j,sum,cxor=0,addr=1;
  static int checked[9];       // checked[7]: [5] refer to KEY [6]th refers to point sum [7]th refers to address where u's doublet formed  [8]th addr b's doblet formed
  for(i=0;i<9;i++)
	checked[i]=0;

 // vertical check
 for(i=0;i<3;i++)
 {
  sum=0,cxor=0;
  for(j=i;j<=i+6;j=j+3)
  {
	sum=sum+quad[j];
	cxor=cxor^quad[j];
  }
	switch(sum)
	{
	 case 6: sno==2?checked[5]++:checked[4]++;
				break;
	 case 4: cxor==0?(sno==2?checked[1]++:checked[0]++):1;
				cxor==0?(sno==2?checked[8]=addr:checked[7]=addr):0;
				break;
	 case 3: cxor==1?(sno==2?checked[4]++:checked[5]++):1;
				break;
	 case 2: cxor==0?(sno==2?checked[0]++:checked[1]++):1;
				cxor==0?(sno==2?checked[7]=addr:checked[8]=addr):0;
				break;
	}
  addr++;

 }
  //horizontal check
  for(i=0;i<7;i=i+3)
  {
	sum=0,cxor=0;
	for(j=i;j<i+3;j++)
	{
	 sum=sum+quad[j];
	 cxor=cxor^quad[j];
	}
	switch(sum)
	{
	 case 6: sno==2?checked[5]++:checked[4]++;
				break;
	 case 4: cxor==0?(sno==2?checked[1]++:checked[0]++):1;
				cxor==0?(sno==2?checked[8]=addr:checked[7]=addr):0;
				break;
	 case 3: cxor==1?(sno==2?checked[4]++:checked[5]++):1;
				break;
	 case 2: cxor==0?(sno==2?checked[0]++:checked[1]++):1;
				cxor==0?(sno==2?checked[7]=addr:checked[8]=addr):0;
				break;
	}
  addr++;
  }
  //diagonal 1 check L TO R
  sum=quad[0]+quad[4]+quad[8];
  cxor=(quad[0]^quad[4])^quad[8];
  switch(sum)
  {
	case 6: sno==2?checked[5]++:checked[4]++;
			  break;
	case 4: cxor==0?(sno==2?checked[1]++:checked[0]++):1;
			  cxor==0?(sno==2?checked[8]=addr:checked[7]=addr):0;
			  break;
	case 3: cxor==1?(sno==2?checked[4]++:checked[5]++):1;
			  break;
	case 2: cxor==0?(sno==2?checked[0]++:checked[1]++):1;
			  cxor==0?(sno==2?checked[7]=addr:checked[8]=addr):0;
			  break;
  }
  addr++;

  //diagonal 2 check R TO L
  sum=quad[2]+quad[4]+quad[6];
  cxor=(quad[2]^quad[4])^quad[6];
  switch(sum)
  {
	case 6: sno==2?checked[5]++:checked[4]++;
			  break;
	case 4: cxor==0?(sno==2?checked[1]++:checked[0]++):1;
			  cxor==0?(sno==2?checked[8]=addr:checked[7]=addr):0;
			  break;
	case 3: cxor==1?(sno==2?checked[4]++:checked[5]++):1;
			  break;
	case 2: cxor==0?(sno==2?checked[0]++:checked[1]++):1;
			  cxor==0?(sno==2?checked[7]=addr:checked[8]=addr):0;
			  break;
  }

  //double trick check
  checked[1]>1?checked[3]++:1;
  checked[0]>1?checked[2]++:1;

  //assigning point sum to checked[6]
  checked[6]=4*checked[5]+1*checked[3]-2*checked[0];

  return &checked[0];
}





int findnull(int quad[9], int addr)
{
 int i,start=0,var=0;
 switch(addr)
 {
  case 1: start=0; var=3;
			 break;
  case 2: start=1; var=3;
			 break;
  case 3: start=2; var=3;
			 break;
  case 4: start=0; var=1;
			 break;
  case 5: start=3; var=1;
			 break;
  case 6: start=6; var=1;
			 break;
  case 7: start=0; var=4;
			 break;
  case 8: start=2; var=2;
			 break;

 }

 for(i=start;i<=start+2*var;i=i+var)
 {
  if(quad[i]==0)
	return i;
 }
}






char bot(int quad[9], int level, int sno, char multiplayer='n') //sno: bot's symbol number 0:1 X:2
{
 int *result;
 result=checkmat(quad,sno);
 if(result[5])
  return 'b';
 if(result[4])
  return 'u';
 else if(multiplayer=='y' || quad[0]*quad[1]*quad[2]*quad[3]*quad[4]*quad[5]*quad[6]*quad[7]*quad[8]!=0)
  return 'n';
 if(multiplayer==1)
  aprintf("BOT 1",'c',matx-(unit*4),maty,0);
 else if(multiplayer==2)
  aprintf("BOT 2",'c',matx+(unit*3),maty,0);
 switch(level)
 {

  case 1: int check, *verify,location;
		  verify=checkmat(quad,sno);
		  if(verify[0]||verify[1])
		  {

			 location=verify[1]?findnull(quad,verify[8]):findnull(quad,verify[7]);
			  draw(sno,location+1,quad);
			  break;
		  }
		  randomize();
		  do{
			check=random(9);
		  }while(quad[check]!=0);
		  draw(sno,check+1,quad);
		  break;

  case 2:
		 if(quad[4]==3^sno && quad[0]+quad[1]+quad[2]+quad[3]+quad[5]+quad[6]+quad[7]+quad[8]==0)    //special case1
		 {
		  int temp[]={1,3,5,7};
		  draw(sno,temp[random(4)]+1,quad);
		  break;
		 }
		 if((quad[6]==3^sno||quad[7]==3^sno) && quad[0]+quad[1]+quad[2]+quad[3]+quad[5]+quad[4]+quad[8]==0 && (quad[6]==0||quad[7]==0) ) //special case 2
		 {
		  int temp[]={0,1,2,3,4,5,8};
		  draw(sno,temp[random(7)]+1,quad);
		  break;
		 }


		 int i,j,k, *checked[9],max=0;
		 for(i=0;i<9;i++)
		 {
		  if(!quad[i])
		  {
			quad[i]=sno;
			checked[i]=checkmat(quad,sno);
			if(checked[i][6]>=2)  //if bots triplet forming
			{
			 draw(sno,i+1,quad);
			 break;
			}
			if(checked[max][6]<checked[i][6])
			 max=i;
			quad[i]=0;
		  }

		 }
		 if(checked[i][6]>=2)
		  break;
		 if(checked[max][6]>=0)  // if user's triplet forming
		 {
		  quad[max]=sno;
		  draw(sno,max+1,quad);
		 }

		 if(checked[max]==0)
		 {

		 }

		 break;

 }

 result=checkmat(quad,sno);
 if(result[5])
  return 'b';                          //bot wins
 else if(result[4])
  return 'u';                          //user wins
 else return 'n';                      //no one wins(either draw/game continues..)
}






int main()
{
 //sound(350);
 /*
 mouseposi(int xpos,int ypos,int click);
 printf("x:%d y:%d click:%d,xpos,ypos,click");
 */
randomize();
 textcolor(GREEN);
 char name[15],name2[15],result='n',multiplayer,valid;
 int inchoice=0, quad[9];
 int inquad,level=0,type,savedchoice,botno=1,chance;
 clrscr();
 for(int i=0;i<9;i++)
  quad[i]=0;
 aprintf( "***** *  ****     *****   **    ****     *****  ****  *****"
		  "\n  *   * *    *      *    *  *  *    *      *   *    * *     "
		  "\n  *   * *           *   *    * *           *   *    * ***** "
		  "\n  *   * *           *   ****** *           *   *    * *     "
		  "\n  *   * *    *      *   *    * *    *      *   *    * *     "
		  "\n  *   *  ****       *   *    *  ****       *    ****  *****\n\n",'s',0,unit*4+maty-3,0);

 aprintf("W.e.l.c.o.m.e.\n");
 aprintf("What should I call you:");
 fgets(name,15,stdin);
 clrscr();
 matrix(matx, maty);
 gotoxy(1,unit*4+maty+5);
 printf("________________________________________________________________\n");
 printf("COMMAND SHELL");
 aprintf("Hello ",'c'); aprintf(name); printf("(press any key..)");
 getch();
 fflush(stdin);
 while(type!=1 && type!=2 & type!=3)
 {
  aprintf("choose: 1.)player vs player\n\t2.)bot vs player\n\t3.)bot vs bot:",'c');
  scanf("%d",&type);
 }
 if(type==1)
 {
  aprintf("What should I call player2 :",'c');
  fflush(stdin);													 //cleared buffer
  fgets(name2,15,stdin);
 }
 fflush(stdin);
 if(type==2 || type==3)
 {
  //-----------construction-------------
  while(level!=1)
  {
	aprintf("choose: 1.)level 1\n\t2.)level 2:",'c');
	scanf("%d",&level);
	if(level==2)
	{
	 aprintf("LEVEL 2 UNDER CONSTRUCTION (press any key..) \a",'c');
	 getch();
	}
	if(level!=1 && level!=2)
	{
	 aprintf("Thats Rude (press any key..) \a",'c');
	 getch();
	}
  }
  //-----------ends here----------------
  if(type==2)
  {
   chance=random(2);
  }
 }
 while(inchoice!=1 && inchoice!=2)
 {
  aprintf("choose: 1.)CIRCLE\n\t2.)CROSS:",'c');    type==1?printf("(for %s):",name):1;      type==3?printf("(for BOT 1):"):1;
  scanf("%d",&inchoice);
  if(inchoice>2)
  {
	aprintf("Isint ",'c'); printf("%d",inchoice); printf(" greater than 2!(press any key..)\a",'c');
	getch();
  }
  else if(inchoice<1)
  {
	aprintf("Isint ",'c'); printf("%d",inchoice); aprintf(" less than 1!(press any key..)\a",'c');
	getch();
  }
 }
 type==1?savedchoice=inchoice:1;
 i=0;
 while((i<5&&type==2 || i<9&&(type==1||type==3&&chance!=0) || i<10&&type==1&&chance==0) && result=='n')
 {
  i++;
  if((i%2!=0 && type==1) || (type==2 && chance!=0))
	aprintf(name,'c',matx+(unit*3),maty,0);
  else if(type==1)
	aprintf(name2,'c',matx-(unit*4),maty,0);
  valid='n';
  if(type!=3 && chance!=0)
  {
	while(valid!='y')
	{
		aprintf("Choose quadrant:",'c');
		scanf("%d",&inquad);
		if(!quad[inquad-1])
		 valid='y';
	}
	draw(inchoice,inquad,quad);
  }
  chance=chance==0?1:1;
  if(type==1)
  {

	inchoice=3^inchoice;
  }
  aprintf(" ",'c',matx+(unit*3),maty,0);
  multiplayer=(type==1?'y':type==3?botno:'n');
  botno=3^botno;
  if(type==1)
	result=bot(quad,level,3^savedchoice,multiplayer);
  else if(type==2)
	result=bot(quad,level,3^inchoice,multiplayer);
  else if(type==3)
  {
	result=bot(quad,level,inchoice,multiplayer);
	inchoice=3^inchoice;
	if(i%2==0 && result!='n')
	 result=('b'^'u')^result;
	delay(300);
  }

  aprintf(" ",'c',matx-(unit*4),maty,0);
  switch(result)
  {
  case 'b':  printf("\a");
				 if(type==1)
				 {
				  aprintf("Winner :",'c'); printf(name2);
				 }
				 else
				 {
				  aprintf("Winner: BOT",'c'); type==3?printf("1"):1;
				 }
				 break;
  case 'u':  printf("\a");
				 if(type!=3)
				 {
				  aprintf("Winner: ",'c'); aprintf(name);
				 }
				 else
				  aprintf ("Winner: BOT2",'c');
				 break;
  }
 }
 result=='n'?aprintf("Match Draw \a",'c'):1;

 getch();
 return 0;

}
