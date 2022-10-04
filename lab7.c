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


int main(){
	char ch='.';
	int x=38,y=20;
	int bx,by,i;
	int bullet = 0;
	draw_ship(x,y);
	setcursor(0);
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
		if (by==2) { bullet=0;} else { draw_bullet(bx,--by); }
	}
	Sleep(100);
} while (ch!='x');
return 0;
}