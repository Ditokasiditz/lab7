#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>
#include<time.h>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE) , c);
}

int main(){
int xs,ys,i,m,n;
	srand(time(NULL));
	for(i=0;i<20;i++){
		m=rand(); ys=xs%10;
		n=rand(); xs=xs%100;
	
		if(ys>5 || ys<2){
			do{m=rand(); ys=m%10;}
			while(ys<=5 && ys>=2);
		}
		
		if(xs<10 || xs>70){
			do{n=rand(); xs=n%100;}
			while(xs<=70 && xs>=10);
		}
		
		
		gotoxy(xs,ys);
	
		printf("*");
	}
}