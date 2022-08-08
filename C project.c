#include<stdio.h>
int main() {
	for (int i = 0;i<=100;i++) {
		printf("%d\n", i);
	}
	return 0;
}
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#pragma warning(disable:4996)
/*====================================*/
#define randomize() srand(time(NULL))
#define random(n) (rand()%(n))
#define MAXBULLET 2
#define MAXENEMY 20
#define MAXENEMYBULLET 20 
#define SUB 13
/*====================================*/

/*====================================*/

typedef struct
{
	char name[21];
	int score;
}Player_Rank;


struct {
	BOOL exist;
	int x, y;
} Bullet[MAXBULLET];

struct {
	BOOL exist;
	int x, y;
	int dest;
	int nFrame;
	int type;
	int nStay;
}Enemy[MAXENEMY];

char* Enemyit[] = { "※■※","▲■▲","◎◆◎","▒▤▒" };
/*====================================*/
struct {
	BOOL exist;
	int x, y;
	int nStay;
	int nFrame;
}EnemyBullet[MAXENEMYBULLET];
/*====================================*/
void Cursorview(char show) {
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
void Color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*====================================*/

enum {
	BLACK, 
	DARK_BLUE,
	DARK_GREEN,
	DARK_SKYBLUE,
	DARK_RED, 
	DARK_VIOLET,
	DARK_YELLOW,
	GRAY,
	DARK_GRAY,
	BLUE,
	GREEN,
	SKYBLUE,
	RED,
	VIOLET,
	YELLOW, 
	WHITE
};

/*================================================================*/

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

/*=================================================================*/

void Start();
void length();
void Userinter();
void Drawplayer();
void Eraseplayer();
void Moveplayer();
void Drawbullet(int i);
void Movebullet();
void Erasebullet(int i);
void Drawmissile();
void Erasemissile();
void Movemissile();
void Drawenemy();
void Moveenemy();
void Drawenb(int i);
void Eraseenb(int i);
void Shootenb(int i);
void Moveenb();
void Enemycollision();
void Playercollision();
void Gameover();
void Overment();
void Menu();
void Nonum();
void Game();
void Info();
void Rank_System();
int keycontrol();
void Rank_arr();
void Rank_Draw();

/*-------------------------------------------*/

int px = 43;
int bx = -1, by;
int mx = -1, my;
int score = 0;

/*-------------------------------------------*/
int main() {
	system("mode con: lines=40");

	system("pause>null");
	
	Cursorview(0);
	
	Menu();
	return 0;
}
void Menu() {
	
	int n;
	while (1) {
		Color(BLUE);
		
		system("cls");
		
		printf("\n\n\n\n\n\n");
		printf("                         ■■■■■     ■■■      ■■■       ■■■■       ■■■\n");
		printf("                         ■            ■    ■    ■    ■     ■       ■    ■    ■\n");
		printf("                         ■            ■     ■   ■     ■   ■         ■   ■     ■\n");
		printf("                         ■■■■■    ■    ■    ■    ■   ■           ■  ■    ■\n");
		printf("                         ■            ■  ■      ■  ■     ■           ■  ■  ■\n");
		printf("                         ■            ■   ■     ■    ■    ■         ■   ■    ■\n");
		printf("                         ■            ■    ■    ■     ■    ■       ■    ■     ■\n");
		printf("                         ■■■■■    ■      ■  ■      ■    ■■■■      ■      ■\n\n\n\n\n\n\n\n");
		printf("                                                  1번:GAME START                                                        \n\n");
		printf("                                                  2번:INFORMATION                                                       \n\n");
		printf("                                                   3번:RANKING                                                           \n\n");
		printf("                                                   번호 입력>>                                                         \n\n");
		
		gotoxy(64, 28); scanf("%d", &n);
		
		if (n == 1) {
			Game();
		}
		
		else if (n == 2) {
			Info();
		}
		
		else if (n == 3) {
			Rank_System();
		}
		
		else {
			Nonum();
		}
	}
}

void length() {
	for (int i = 0; i < 40; i++) {
		gotoxy(89, i); printf("◈");
	}
}

void Userinter() {
	gotoxy(95, 2); printf("   ◀ E R R O R ▶    ");
	gotoxy(93, 4); printf("  ◀ S H O O T I N G ▶  ");

	gotoxy(93, 8); printf("MOVE : LEFT ←  → RIGHT");

	gotoxy(95, 14); printf("<< GUN : SPACE BAR >>");
	
	gotoxy(95, 17); printf("<< MISSILE KEY : D >>");
	
	gotoxy(98, 21); printf("※별사탕은 2발씩!");
	
	gotoxy(93, 25); printf("<< PLAYER COLOR : GREEN >>");
	
	gotoxy(94, 27); printf("<< ERROR COLOR : BLUE >>");
	
	gotoxy(98, 33); printf("<< GOOD LUCK! >>");
	
	gotoxy(100, 35); printf("SCORE : %d", score);
}

void Drawplayer() {
	Color(RED);
	gotoxy(px, 39); printf("<◀▲▶>");
	Color(GRAY);
}

void Moveplayer() {
	int i;
	char ch;
	if (GetAsyncKeyState(VK_LEFT) < 0 && px > 2) {
		Eraseplayer();
		px -= 2;
		Drawplayer();

	}
	else if (GetAsyncKeyState(VK_RIGHT) < 0 && px < 81) {
		Eraseplayer();
		px += 2;
		Drawplayer();
	}
	if (_kbhit()) {
		ch = _getch();
		switch (ch)
		{
		case ' ':
			for (i = 0; i < MAXBULLET && Bullet[i].exist == TRUE; i++) { ; }
			if (i != MAXBULLET) {
				Bullet[i].x = px + 3;
				Bullet[i].y = 38;
				Bullet[i].exist = TRUE;
			}
			break;
		case 'F':
			if (mx == -1) {
				my = px + 3;
				my = 38;
			}
			break;
		case 'f':
			if (mx == -1) {
				mx = px + 3;
				my = 38;
			}
			break;
		}
	}
}

void Eraseplayer() {
	gotoxy(px, 39); printf("        ");
}

void Drawbullet(int i) {
	Color(GREEN);
	gotoxy(Bullet[i].x, Bullet[i].y); printf("★");
	Color(GRAY);
}

void Erasebullet(int i) {
	gotoxy(Bullet[i].x, Bullet[i].y); printf("  ");

}

void Movebullet() {
	int i;
	for (i = 0; i < MAXBULLET; i++) {
		if (Bullet[i].exist == TRUE) {
			Erasebullet(i);
			if (Bullet[i].y == 0) {
				Bullet[i].exist = FALSE;
			}
			else {
				Bullet[i].y -= 2;
				Drawbullet(i);
				Sleep(2);
			}
		}
	}
}

void Drawmissile() {
	Color(RED);
	gotoxy(mx, my - 2); printf("▲▲");
	gotoxy(mx, my - 1); printf("★★");
	gotoxy(mx, my);     printf("※※");
	Color(GRAY);
}

void Erasemissile() {
	gotoxy(mx, my - 2); printf("    ");
	gotoxy(mx, my - 1); printf("    ");
	gotoxy(mx, my);     printf("    ");
}

void Movemissile() {
	if (mx != -1) {
		Erasemissile();
		if (my - 2 == 0) {
			mx = -1;
		}
		else {
			my--;
			Drawmissile();
		}
	}
}

void Drawenemy() {
	BOOL Found;
	int i, j;
	if (random(100) == 0) {
		for (i = 0; i < MAXENEMY && Enemy[i].exist == TRUE; i++) { ; }

		if (i != MAXENEMY) {
			if (random(2) == 0) {
				Enemy[i].x = 5;
				Enemy[i].dest = 1;
			}
			else {
				Enemy[i].x = 45;
				Enemy[i].dest = -1;
			}
			while (1)
			{
				Enemy[i].y = random(10) + 1;
				for (Found = FALSE, j = 0; j < MAXENEMY; j++) {
					if (Enemy[i].exist == TRUE && Enemy[j].y == Enemy[i].y) {
						Found = TRUE;
						break;
					}
				}
				if (Found == FALSE)
					break;
			}
			Enemy[i].nFrame = Enemy[i].nStay = random(6) + 1;
			Enemy[i].type = random(sizeof(Enemyit) / sizeof(Enemyit[0]));
			Enemy[i].exist = TRUE;
		}
	}
}

void Moveenemy() {
	int i;
	for (i = 0; i < MAXENEMY; i++) {

		if (Enemy[i].exist == FALSE)
			continue;

		if (--Enemy[i].nStay == 0) {
			if (Enemy[i].type == -1) {
				gotoxy(Enemy[i].x - 3, Enemy[i].y);     printf("                                                              ");
				gotoxy(Enemy[i].x - 3, Enemy[i].y - 1); printf("                                                              ");
				gotoxy(Enemy[i].x - 3, Enemy[i].y - 2); printf("                                                              ");
				Enemy[i].exist = FALSE;
				continue;
			}

			Enemy[i].nStay = Enemy[i].nFrame;

			if (Enemy[i].x > 84 || Enemy[i].x < 4) {
				Enemy[i].exist = FALSE;
				gotoxy(Enemy[i].x - 3, Enemy[i].y);
				printf("                ");
			}
			else {
				gotoxy(Enemy[i].x - 3, Enemy[i].y);
				printf(" ");
				gotoxy(Enemy[i].x + 2, Enemy[i].y);
				printf(" ");
				Enemy[i].x += Enemy[i].dest;
				gotoxy(Enemy[i].x - 3, Enemy[i].y);
				printf(Enemyit[Enemy[i].type]);

				Shootenb(i);
			}
		}
	}
}

void Drawenb(int i) {
	gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
	printf("↓");
}

void Eraseenb(int i) {
	gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
	printf("    ");
}

void Moveenb() {
	int i;
	for (i = 0; i < MAXBULLET; i++) {
		if (EnemyBullet[i].exist == FALSE)
			continue;

		if (--EnemyBullet[i].nStay == 0) {
			EnemyBullet[i].nStay = EnemyBullet[i].nFrame;
			Eraseenb(i);

			if (EnemyBullet[i].y > 37) {
				EnemyBullet[i].exist = 0;
			}

			else {
				if (random(3)) {
					if (EnemyBullet[i].x < px)
						EnemyBullet[i].x++;
					else
						EnemyBullet[i].x--;
				}
				EnemyBullet[i].y += 8;
				Drawenb(i);
			}
		}
	}
}

void Shootenb(int i) {
	int j;

	if (random(20) == 0) {
		for (j = 0; j < MAXENEMYBULLET && EnemyBullet[j].exist == TRUE; j++) { ; }
		if (j != MAXENEMYBULLET) {
			EnemyBullet[j].x = Enemy[i].x + 2;
			EnemyBullet[j].y = Enemy[i].y + 1;
			EnemyBullet[j].nFrame = EnemyBullet[j].nStay = Enemy[i].nFrame + 6;
			EnemyBullet[j].exist = TRUE;
		}
	}
}

void Enemycollision() {
	int i;
	for (i = 0; i < MAXENEMY; i++) {
		if (Enemy[i].exist == FALSE || Enemy[i].type == -1)
			continue;
		if (Enemy[i].y == Bullet[i].y && abs(Enemy[i].x - Bullet[i].x) <= 7) {
			gotoxy(Bullet[i].x, Bullet[i].y); printf("     ");
			Bullet[i].exist = FALSE;
			Enemy[i].type = -1;

			gotoxy(Enemy[i].x - 3, Enemy[i].y);
			printf("+20점 획득!");
			score += 20;
			Enemy[i].nFrame = Enemy[i].nStay = 50;
			break;
		}
		if (Enemy[i].y == my && abs(Enemy[i].x - mx) <= 7) {
			gotoxy(mx, my); printf("     ");
			mx = -1;
			Enemy[i].type = -1;

			gotoxy(Enemy[i].x - 3, Enemy[i].y);
			printf("+10점 획득!");
			score += 10;
			Enemy[i].nFrame = Enemy[i].nStay = 50;
			break;
		}
	}
}

void Playercollision() {
	int i;
	char ch;
	for (i = 0;i < MAXENEMYBULLET;i++) {
		if (EnemyBullet[i].exist == FALSE)
			continue;

		if (EnemyBullet[i].y >= 39 && abs(EnemyBullet[i].x - px) <= 5) {
			for (i = 0; i < MAXENEMYBULLET; i++) {
				EnemyBullet[i].exist = 0;
			}

			Color(RED);
			gotoxy(px - 3, 37); printf("CRASH!!!!");
			gotoxy(px - 3, 38); printf("CRASH!!!!");
			gotoxy(px - 3, 39); printf("CRASH!!!!");
			Sleep(1000);
			Gameover();
		}
	}
}

void Overment() {
	Color(RED);
	gotoxy(44, 17);
	if (score <= 50) {
		printf("이런 점수가 나올 수가 없을텐데..");
	}
	else if (50 < score && score <= 100) {
		printf("음 점수가 아쉬운데요 더 화이팅!");
	}
	else if (100 < score && score <= 150) {
		printf("집중력 최고! 더 높은 곳까지ㄱ!!");
	}
	else if (150 < score && score <= 200) {
		printf("진짜 대단하네요 여기까지오다니!");
	}
	else {
		printf("칭찬스티커 300개!! 너무 잘해요!");
	}

}

void Gameover() {
	system("cls");
	char ch;
	gotoxy(52, 12); printf("당신의 SCORE는?!");
	gotoxy(38, 14); printf("▣◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆▣");
	gotoxy(38, 15); printf("▣              SCORE : %d                 ▣", score);
	gotoxy(38, 16); printf("▣                                        ▣");
	gotoxy(38, 17); printf("▣                                        ▣");
	gotoxy(38, 18); printf("▣                                        ▣");
	gotoxy(38, 19); printf("▣◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆▣");
	
	while (1) {
		Overment();
		ch = getch();
		if (ch == 'q' || ch == 'Q') {
			Color(GRAY);
			Menu();
		}
	}
}

void Game() {
	system("cls");
	Color(RED);
	gotoxy(px, 39); printf("<◀▲▶>");
	Color(GRAY);
	randomize();
	score = 0;
	while (1)
	{
		length();
		
		Userinter();
		
		Moveplayer();
		
		Movebullet();
		
		Sleep(20);
		
		Movemissile();
		
		Color(BLUE);
		
		Drawenemy();
		
		Moveenemy();
		
		Moveenb();
		
		Color(GRAY);
		
		Enemycollision();
		
		Color(BLUE);
		
		Playercollision();
	}

	Gameover();
}

void Nonum() {
	system("cls");
	char ch;

	gotoxy(47, 18); printf("지원하지 않는 기능입니다.");
	gotoxy(49, 33); printf("돌아가려면 'q' 클릭!");

	while (1) {
		ch = getch();
		if (ch == 'q' || ch == 'Q')
			Menu();
	}
}

void Info() {
	char ch;
	system("cls");
	gotoxy(45, 3); printf("곳곳에서 나타나고 움직이는 오류들을");

	gotoxy(42, 8); printf("별사탕과 미사일을 발사해 물리치는 슈팅게임을");

	gotoxy(51, 13); printf("c언어로 구현하였습니다!");

	gotoxy(43, 18); printf("※오류들은 일정 확률로 공격을 회피합니다!");

	gotoxy(35, 23); printf("★ 별사탕을 잘 피하기 때문에 별사탕으로 맞춘다면 +20 점입니다!");

	gotoxy(36, 28); printf("※오류들은 자신들의 총알을 사라지지 않게 하는 오류를 남깁니다.");
	
	gotoxy(44, 33); printf("※조작법은 게임화면에 구현 되어 있습니다.");

	gotoxy(50, 36); printf("돌아가려면 'q' 더블 클릭!");

	gotoxy(52, 39); printf("Made by. 이운린,김민수");
	
	Cursorview(0);
	system("pause>null");
	
	while (1) {
		ch = getch();
		if (ch == 'Q' || ch == 'q')
			Menu();
	}
}

void Rank_Draw() {
	system("cls");
	
	printf("\n\n\n");
	printf("                   ★-★-★-★-★-★-★-★-★-★-★-★<RA◈NK>★-★-★-★-★-★-★-★-★-★-★-★-★\n");

	printf("                         <NAME>                                                      <SCORE>        \n");


}

int keycontrol() {
	char temp = getch();
	
	if (temp == '\n') {
		return SUB;
	}
}

void Rank_arr() {
	int count = 0;   
	//파일에서 랭킹을 불러오는 수를 저장함(이 수로 버블정렬을 돌려서 연산을 최소화함)
	int temp;

	int i = 0;
	int score[10] = { 0, };
	
	FILE* fp = fopen("rank.txt", "r");   // 파일을 읽기속성으로 열어줌
	if (fp == NULL) {

		printf("랭킹 불러오기에 실패했습니다..");
	
	}
	else {
		Player_Rank player_rank[30] = { 0, };
		Player_Rank P_R = { 0,0 };
		for (int i = 0; i < 30; i++) {
			fscanf(fp, "%s%d", player_rank[i].name, &player_rank[i].score);
			if (player_rank[i].name != NULL) {     
				//만약 다음 입력받는 값이 NULL이면 더이상 파일에서 정보를 그만받음

			}
			else {
				break;
			}
			count++;
		}
		for (int i = 0; i < 10; i++) {  //버블정렬로 정리
			for (int j = 1; j < count - 1; j++) {
				if (player_rank[j - 1].score < player_rank[j].score) {
					P_R = player_rank[j];
					player_rank[j] = player_rank[j - 1];
					player_rank[j - 1] = P_R;

				}
			}
		}
		for (int i = 0; i < 9; i++) {     //여기에 숫자9는 역시 너가 출력해줄 랭킹의 수를 이야기
			if (i < 1) {
			
				Color(YELLOW);
				gotoxy(20, 5 + i);
				printf("◐"); //첫번쨰 순위를 별로 앞에 붙여주는것

			}
			Color(GRAY);
			if (i < 1) {
				
				Color(RED);
			
			}

			else if (0 < i && i < 2) {

				Color(SKYBLUE);
			
			}

			else if (1 < i && i < 3) {
			
				Color(GREEN);
			
			}

			gotoxy(25, 5 + i);
			printf("%s", player_rank[i].name);  //랭킹들 출력
			gotoxy(87, 5 + i);
			printf("%d", player_rank[i].score);
			Color(GRAY);
		}
		fclose(fp);
	}
	/*for (int i = 0; i < 5; i++)
	{
		name=(char*)malloc(sizeof(char) * 21);
		fgets(name, 21, fp);
		rank3[i] = name;
		printf("%s", name);
	}*/

}

void Rank_System() {

	Rank_Draw();

	Rank_arr();
	
	gotoxy(0, 15);
	Color(BLUE);
	printf("                     ★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★-★ \n");
	Color(GRAY);
	char name[21] = "";
	gotoxy(50, 20); printf("\n				    랭킹을 등록하시겠습니까 ? (Y / N)");
	
	while (1) {
		int num1 = keycontrol(0);
		
		if (num1 == 'Y' || num1 == 'y') {
			FILE* fp = fopen("rank.txt", "a+");
			//타입을 a+(전에 있던 데이터를 덮어쓰는게 아니라 있던 데이터에 추가함)로 설정해 전에있던 랭킹들과 새로 추가된 랭킹들이 있을 수 있게했다.
			
			if (fp == NULL) {
				printf("       파일 로딩에 실패했습니다.");
			}
			
			gotoxy(50, 23); printf("\n				    10글자 이내로 닉네임을 적어주세요:");
			scanf("%s", name);
			//name문자열배열에 닉네임을 저장하고 name배열에 문자열을 fprintf를 이용해서 파일에 저장해준다.
			fprintf(fp, "%s  %d\n", name, score);

			fclose(fp);
			//오류가 일어나지않게 파일을 닫아줌
			break;
		}
		else if (num1 == 'n' || num1 == 'N') {
			break;
			//n이 눌리면 랭킹을 입력받지 않겠다는것으로 간주,메인화면으로 돌려보낸다
		}
	}

	gotoxy(50, 30); printf("\n      ※ 엔터를 누르면 메인메뉴로 이동합니다...");



	while (1) {

		int num = keycontrol(0);

		if (num == SUB) {
			Menu();

			score = 0;
			return;
		}
	}
}