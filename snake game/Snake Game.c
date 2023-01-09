#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <dos.h>

//constant values
#define N 20
#define M 40

//global variables
int i, j, Field[N][M], x, y, Gy, Head, Tail, Game, Frogs, a, b, var, dir, score, HighScore, Speed;

FILE *f;

void main();
void GameOver();

void lineLoop(){
	int ctr;
	printf("\n");
	for(ctr=0;ctr<120;ctr++){
		printf("=");
	}
	printf("\n");
}
void snakeInitialization()
{
	f = fopen("highscore.txt", "r");
	fscanf(f, "%d", &HighScore);
	fclose(f);

	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			Field[i][j] = 0;
		}
	}

	x = N / 2;
	y = M / 2;
	Gy = y;
	Head = 5;
	Tail = 1;
	Game = 0, Frogs = 0, dir = 'd', score = 0, Speed = 99;

	for (i = 0; i < Head; i++)
	{
		Gy++;
		Field[x][Gy - Head] = i + 1;
	}
}

void print()
{
	for (i = 0; i <= M + 1; i++)
	{
		if (i == 0)
		{
			printf("%c", 201);
		}
		else if (i == M + 1)
		{
			printf("%c", 187);
		}
		else
		{
			printf("%c", 205);
		}
	}
	printf("   Current Score: %d  HighScore: %d", score, HighScore);
	printf("\n");

	for (i = 0; i < N; i++)
	{
		printf("%c", 186);

		for (j = 0; j < M; j++)
		{
			if (Field[i][j] == 0)
				printf(" ");
			if (Field[i][j] > 0 && Field[i][j] != Head)
				printf("%c", 176);
			if (Field[i][j] == Head)
				printf("%c", 178);
			if (Field[i][j] == -1)
				printf("%c", 15);
			if (j == M - 1)
				printf("%c\n", 186);
		}
	}

	for (i = 0; i <= M + 1; i++)
	{
		if (i == 0)
		{
			printf("%c", 200);
		}
		else if (i == M + 1)
		{
			printf("%c", 188);
		}
		else
		{
			printf("%c", 205);
		}
	}
}
void ResetScreenPosition()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Random()
{
	srand(time(0));
	a = 1 + rand() % 18;
	b = 1 + rand() % 38;

	if (Frogs == 0 && Field[a][b] == 0)
	{
		Field[a][b] = -1;
		Frogs = 1;
		if (Speed > 10 && score != 0)
			Speed = Speed - 5;
	}
}

int getch_noblock()
{
	if (_kbhit())
		return _getch();
	else
		return -1;
}

void movement(){
    var = getch_noblock();
    var = tolower(var);

    if(((var=='d'||var=='a')||(var=='w'||var=='s'))
       &&(abs(dir-var)>5)) dir = var;
    if(dir =='d'){
        y++;
        if(y==M-1) y = 0;
        if(Field[x][y]!=0 && Field[x][y]!=-1) GameOver();
        if(Field[x][y]==-1){
            Frogs = 0;
            score+=5;
            Tail -= 1;
			Beep(500,10);        
        }

        Head++;
        Field[x][y] = Head;
    }

    if(dir =='a'){
        y--;
        if(y==0) y = M-1;
        if(Field[x][y]!=0 && Field[x][y]!=-1) GameOver();
        if(Field[x][y]==-1){
            Frogs = 0;
            score+=5;
            Tail -= 1;
            Beep(500,10);      
        }
        Head++;
        Field[x][y] = Head;
    }

    if(dir =='w'){
        x--;
        if(x==-1) x = N-1;
        if(Field[x][y]!=0 && Field[x][y]!=-1) GameOver();
        if(Field[x][y]==-1){
            Frogs = 0;
            score+=5;
            Tail -= 1;
            Beep(500,10);      
        }
        Head++;
        Field[x][y] = Head;
    }

    if(dir =='s'){
        x++;
        if(x==N) x = 0;
        if(Field[x][y]!=0 && Field[x][y]!=-1) GameOver();
        if(Field[x][y]==-1){
            Frogs = 0;
            score+=5;
            Tail -= 1;
            Beep(500,10);      
        }
        Head++;
        Field[x][y] = Head;
    }
}

void movement2()
{
	var = getch_noblock();
	var = tolower(var);

	if (((var == 'd' || var == 'a') || (var == 'w' || var == 's')) && (abs(dir - var) > 5))
		dir = var;
	if (dir == 'd')
	{
		y++;

		if (Field[x][y] != 0 && Field[x][y] != -1 || y == M )
			GameOver();
		if (Field[x][y] == -1)
		{
			Frogs = 0;
			score += 5;
			Tail -= 1;
			Beep(500,10);      
		}

		Head++;
		Field[x][y] = Head;
	}

	if (dir == 'a')
	{
		y--;

		if (Field[x][y] != 0 && Field[x][y] != -1 || y == -1) 
			GameOver();
		if (Field[x][y] == -1)
		{
			Frogs = 0;
			score += 5;
			Tail -= 1;
			Beep(500,10);      
		}
		Head++;
		Field[x][y] = Head;
	}

	if (dir == 'w')
	{
		x--;

		if (Field[x][y] != 0 && Field[x][y] != -1 || x == -1)
			GameOver();
		if (Field[x][y] == -1)
		{
			Frogs = 0;
			score += 5;
			Tail -= 1;
			Beep(500,10);      
		}
		Head++;
		Field[x][y] = Head;
	}

	if (dir == 's')
	{
		x++;

		if (Field[x][y] != 0 && Field[x][y] != -1 || x == N)
			GameOver();
		if (Field[x][y] == -1)
		{
			Frogs = 0;
			score += 5;
			Tail -= 1;
			Beep(500,10);      
		}
		Head++;
		Field[x][y] = Head;
	}
}


void TailRemove()
{
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < M; j++)
		{
			if (Field[i][j] == Tail)
			{
				Field[i][j] = 0;
			}
		}
	}
	Tail++;
}

void GameOver()
{
	printf("\a");
	Sleep(1500);
	system("Cls");

	if (score > HighScore)
	{
		printf("\t++ New HighScore %d ++\n\n", score);
		system("pause");
		f = fopen("highscore.txt", "w");
		fprintf(f, "%d", score);
		fclose(f);
	}

	system("Cls");
	printf("\n\n\t\t++ GAME OVER ++ \n\n");
	printf("\t\t** Score : %d **\n\n", score);
	printf("\t\tPress ENTER to play again or ESC to exit ... \n");

	while (1)
	{
		var = getch_noblock();
		if (var == 13)
		{
			system("Cls");
			main();
			break;
		}
		else if (var == 27)
		{
			system("Cls");
			Game = 1;
			printf("\n\n\t++ Coded by: June Udtohan ++\n\n\t- Reference: https://youtube.com/playlist?list=PL3pKgZpYZLjmNpbeZrcL8pBSq3YPb-8G6\n\n\n\n\t\t\t\t\t\tTHE PROGRAM EXITED...\n\n\n");
			break;
		}
	}
	
}

void main()
{
	char ans;
main:
	system("CLS");
	printf("\n\t\t\t\t\t\t++ S N A K E   G A M E ++");
	lineLoop();
	printf("\n\tRules:\n\t\t1. You are the snake and you should eat the frog.\n\t\t2. Don\'t eat or bump yourself.\n\t\t3. If Easy and Normal, you can pass through the walls. \n\t\t4. If hard, you cannot pass through the walls.\n\t\t5. Use W,A,S,D for movements.\n");
	lineLoop();
	printf("\n\tDIFFICULTY:\n\n\t[a] - Easy\n\t[b] - Normal\n\t[c] - Hard\n\n\t==============\n\n\tEnter(a,b,c): ");
	scanf("%c", &ans);
	fflush(stdin);
	if (toupper(ans) != 'A' && toupper(ans) != 'B' && toupper(ans) != 'C')
	{
		printf("\n\t\tA,B,C only. Press any key to enter again...");
		getch();
		goto main;
	}
	
	system("CLS");
	
	if(toupper(ans)== 'A'){
		
		snakeInitialization();

		while (Game == 0)
		{
			print();
			ResetScreenPosition();
			Random();
			movement();
			TailRemove();
			Sleep(Speed);
		}
		
	}else if(toupper(ans)=='B'){
		snakeInitialization();

		while (Game == 0)
		{
			print();
			ResetScreenPosition();
			Random();
			movement();
			TailRemove();
			Sleep(Speed/5);
		}
	}else{
		
		snakeInitialization();

		while (Game == 0)
		{
			print();
			ResetScreenPosition();
			Random();
			movement2();
			TailRemove();
			Sleep(1);
		}
		
	}
	
}
