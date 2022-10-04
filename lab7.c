#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<stdbool.h>

void setcursor(bool visible){
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console,&lpCursor);
}

void setcolor(int fg,int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg*16+fg);
}

void gotoxy(int x, int y){
	COORD c = { x, y };
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

void draw_ship(int x,int y){
	setcolor(2,4);gotoxy(x,y); printf(" <-0-> ");
}

void erase_ship(int x,int y){
	gotoxy(x,y);
	setcolor(0,0);
	printf("       ");
}

void draw_bullet(int x,int y){
	setcolor(1,3); gotoxy(x,y); printf("|");
}

void clear_bullet(int x,int y){
	setcolor(0,0); gotoxy(x,y); printf(" ");
}

void draw_star(){
	int xs,ys,i;
	srand(time(NULL));
	for(i=0;i<20;i++){
		ys=rand(); ys=xs%10;
		xs=rand(); xs=xs%100;
	
		if(ys>5 || ys<2){
			while(ys>5 || ys<2){ys=rand();ys=ys%10;	}
		}
		if(xs<10 || xs>70){
			while(xs<10 || xs>70){xs=rand(); xs=xs%100;	}
		}
		gotoxy(xs,ys);
		setcolor(7,0);
		printf("*");
	}
}

void fill_star(){
	int xs,ys,i;
	ys=rand(); ys=xs%10;
	xs=rand(); xs=xs%100;
	
	if(ys>5 || ys<2){
		while(ys>5 || ys<2){ys=rand();ys=ys%10;	}
	}
	if(xs<10 || xs>70){
		while(xs<10 || xs>70){xs=rand(); xs=xs%100;	}
	}
	gotoxy(xs,ys);
	setcolor(7,0);
	printf("*");
}

char cursor(int x, int y){
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = {x,y}; DWORD num_read;
	if(!ReadConsoleOutputCharacter(hStd,(LPTSTR)buf,1,c,(LPDWORD)&num_read) )
		return '\0';
	else
		return buf[0];
}

void change_score(int x){
	gotoxy(92,0);setcolor(7,0);printf("%d",x);
}

int main(){
	char ch='.';
	int x=38,y=25;
	int bullet = 0,bx,by;
	int score=0;
	setcursor(0);
	draw_star();
	draw_ship(x,y);
	gotoxy(85,0);setcolor(7,0);printf("score:");
	change_score(score);
	
	do {
		if (_kbhit()){
			ch=_getch();
			if(ch=='a') {erase_ship(x,y);draw_ship(--x,y);}
			if(ch=='s') {erase_ship(x,y);draw_ship(++x,y);}
			if(bullet!=1 && ch==' ') {bullet=1; bx=x+3; by=y-1;}
			fflush(stdin);
		}
		
	if (bullet==1) {
		clear_bullet(bx,by);
		if (by==2) { bullet=0;} 
		else { 
			if(cursor(bx,by-1)=='*'){
				Beep(9000,200);
				clear_bullet(bx,by);
				gotoxy(bx,by-1);printf(" ");
				fill_star();
				score=score+100;
				change_score(score);
				bullet=0;
			}
			else{
				draw_bullet(bx,--by);
				Beep(5000,100);}  }
	}
	Sleep(100);
} while (ch!='x');
return 0;
}