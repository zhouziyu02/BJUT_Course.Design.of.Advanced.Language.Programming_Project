#include<graphics.h>
#include <conio.h>
#include<stdio.h>
#include<stdlib.h> 
#include <time.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define WIDTH 640
#define HEIGHT 480
#define n 10


IMAGE welcome;
IMAGE back;
IMAGE p1;
IMAGE p2;
IMAGE p3;
IMAGE p4;
IMAGE login;


typedef struct user {
	char name[20];
	int  score = 0;
	char time[10];
	char num[10];
}USER;

typedef struct node {
	int data1, data2, ans;
	int locx;
	int locy;
	char sign;
	struct node* next;
}NODE;

void background();
void displayButton();
int checkButton(int mouseX, int mouseY);
int drawtime(int sec, int time, int start, int t1, int t2);
void funtime(int c, int flag, char* str);
void initname(USER& user);
int inittime(USER& user);
void initnum(USER& user);
void output(NODE*& hT, NODE*& p, NODE*& hF);
void stoptime(int &t);
void skip(NODE*& p);
void drawscore(int score);
int checkmouse();
void showrule();
void save(USER& user, NODE* hT, NODE* orip, NODE* hF, int t1);

NODE* create(USER& user)
{
	int x, y, flag;
	int i = 30;
	int j = 10;
	int t = 0;
	int num = atoi(user.num);
	NODE* p, * h;
	h = (NODE*)malloc(sizeof(NODE));
	h->data1 = 0;
	h->data2 = 0;
	h->ans = 0;
	h->next = NULL;
	srand((unsigned)time(NULL));
	for (int k = 0; k < num; k++) {
		x = rand() % 9+1;
		y = rand() % 9+1;
		flag = rand() % 2;
		p = (NODE*)malloc(sizeof(NODE));
		p->data1 = x;
		p->data2 = y;
		p->locx = i;
		p->locy = num*(-60)+j;
		i += 30;
		j += 60;
		
		if (flag == 1) {
			p->sign = '+';
			p->ans = p->data1 + p->data2;
		}
		else {
			p->sign = '-';
			p->ans = p->data1 - p->data2;
		}
		if (p->sign == '-') {
			if (p->data1 < p->data2) {
				t = p->data1;
				p->data1 = p->data2;
				p->data2 = t;
				p->ans *= -1;
			}
		}
		p->next = h->next;
		h->next = p;
	}
	return h;
}


void judgeT(NODE* p, NODE* hT)
{
	NODE* f;
	NODE* x;
	x = p;
	f = x;
	x = x->next;
	while (x != NULL) {
		f->next = x->next;
		x->next = hT->next;
		hT->next = x;
		x = f->next;
		break;
	}
}

void judgeF(NODE* p, NODE* hF)
{
	NODE* f;
	NODE* x;
	x = p;
	f = x;
	x = x->next;
	while (x != NULL) {
		f->next = x->next;
		x->next = hF->next;
		hF->next = x;
		x = f->next;
		break;
	}
}


int main()
{
	
	USER user;
	int Time;
	NODE node;
	NODE* b;
	NODE* hT;
	NODE* hF;
	int mouseX;
	int mouseY;
	int flag = 0;
	int i = rand() % 400;
	int iori = i;
	int j = 10;
	int i1 = rand() % 400;
	int j1 = 10;
	int num = 10;
	int k = 1;
	int x = 0;
	int time1;
	int time2=0;
	time1 = atoi(user.time);
	int sign1 = 1;
	int sign2 = 1;
	int sign3 = 0;
	loadimage(&welcome, "image\\welcome.jpg", WIDTH, HEIGHT);
	loadimage(&back, "image\\background.jpg", WIDTH, HEIGHT);
	loadimage(&p1, "image\\fish02.jpg");
	loadimage(&p2, "image\\fish01.jpg");
	loadimage(&p3, "image\\fish04.jpg");
	loadimage(&p4, "image\\fish03.jpg");
	loadimage(&login, "image\\login.jpg", WIDTH, HEIGHT);

	MOUSEMSG mmsg;
	NODE* p;
	hT = (NODE*)malloc(sizeof(NODE));
	hT->next = NULL;
	hF = (NODE*)malloc(sizeof(NODE));
	hF->next = NULL;
	initgraph(WIDTH, HEIGHT, SHOWCONSOLE);
	mciSendString("open D:\\Desktop\\4.22\\Debug\\music.mp3 alias bkmusic", 0 , 0, 0);
	mciSendString("play bkmusic", 0, 0, 0);
	BeginBatchDraw();
	putimage(0, 0, &welcome);
	while (1) {
		FlushBatchDraw(0, 0, 640, 480);
		Sleep(10);
		setfillcolor(BLUE);
		settextstyle(20, 0, "圆体");
		setlinecolor(RED);
		settextcolor(RED);
		setbkmode(TRANSPARENT);
		fillrectangle(200, 50, 440, 100);
		outtextxy(270, 60, "导弹算术题");
		fillrectangle(200, 170, 440, 230);
		outtextxy(295, 185, "START");
		fillrectangle(200, 320, 440, 380);
		outtextxy(270, 330, "INTRODUCTION");
		x = checkmouse();
		if (x == 5) {
			break;
		}
		else if (x == 7) {
			showrule();
			break;
		}
		EndBatchDraw();
	}
	cleardevice();

	putimage(0, 0, &login);
	setbkcolor(WHITE);
	setlinestyle(PS_SOLID, 2);
	srand((unsigned)time(NULL));
	initname(user);
	initnum(user);
	Time = inittime(user);
	background();
	displayButton();
	outtextxy(590, 260, user.name);
	outtextxy(565, 300, user.time);
	while (1) {
		while (flag!=-1) {
			clock_t start;
			start = clock();
			flag = checkmouse();
			
			if (flag == 1) {
				flag = 0;
				p = create(user);
				b = p->next;
				
				while (x!=-1) {
					 
					x = checkmouse();
					BeginBatchDraw();
					putimage(-150, 0, &back);
					while (b != NULL) {
					putimage(b->locx, b->locy, &p1, SRCAND);
					putimage(b->locx, b->locy, &p2, SRCINVERT);
						char r[20], s[20], t[20];
						sprintf_s(r, "%d", b->data1);
						outtextxy(b->locx + 20, b->locy + 50, r);
						sprintf_s(s, "%c", b->sign);
						outtextxy(b->locx + 40, b->locy + 50, s);
						sprintf_s(t, "%d", b->data2);
						outtextxy(b->locx + 60, b->locy + 50, t);
						b = b->next;	
					}

					b = p->next;
					while(b!=NULL) {
						b->locx += 1.1*sign1;
						b->locy += 1;
						if ( b->locx > 405 ) {
							sign1 *=-1;
						}
						b = b->next;
					}
					b = p->next;

					clock_t finish;
					finish = clock();
					Sleep(12);
					if (_kbhit() != 0)
					{
						int l = 0;
						char g[20], m[20];
						while (1) {
							m[l] = _getch();
							outtextxy(550 +10 * l, 375, m[l]);
							FlushBatchDraw();
							if (m[l] == 13) {
								break;
							}
							l++;
						}

						int j = atoi(m);
						if (j == b->ans) {
							user.score += 1;
							clearrectangle(541, 427, 573, 460);
							setfillcolor(YELLOW);
							fillrectangle(542, 428, 572, 458);
							drawscore(user.score);
							judgeT(p, hT);
						}
						else if (j!=b->ans || b->locy>480){
							user.score -= 1;
							clearrectangle(541, 427, 573, 460);
							setfillcolor(YELLOW);
							fillrectangle(542, 428, 572, 458);
							drawscore(user.score);
							judgeF(p, hF);
						}
						clearrectangle(541, 364, 573, 396);
						setfillcolor(YELLOW);
						fillrectangle(542 ,365, 572, 395);
					}

					if (x == 2) {
						FlushBatchDraw(0, 0, 640, 480);
						stoptime(time2);
						
						x = 0;
					}
					if (x == 3) {
						b = b->next;
						skip(p);
						x = 0;
					}
					if (x == 4) {
						output(hT, p, hF);
						FlushBatchDraw(0, 0, 640, 480);
						stoptime(time2);
						x = 0;
					}
					if (x == -1) {
						save(user, hT, p, hF, time2);
						break;
					}
				
					clearrectangle(564, 300, 585, 320);
					time1=drawtime(finish,Time,start,time2,time1);
					FlushBatchDraw();
					EndBatchDraw();	
				}
			}
			outtextxy(515, 260, "用户名： ");
			outtextxy(515, 300, "时间： ");
			outtextxy(515, 340, "我的答案： ");
			outtextxy(515, 405, "当前得分： ");
		}
		break;
	}
	closegraph();
	return 0;
}


void skip(NODE*& p)
{
	NODE* t, * b;
	b = p->next;
	t = p;
	while (t->next != NULL) {
		t = t->next;
	}
	b->locy = t->locy - 100;
	p->next = b->next;
	b->next = NULL;
	t->next = b;
}

void showrule()
{
	int x = 0;
	setfillcolor(BLUE);
	fillrectangle(100, 40, 500, 440);
	settextstyle(20, 0, "圆体");
	settextcolor(YELLOW);
	outtextxy(125, 70, "游戏规则介绍：");
	outtextxy(125, 100, "请在游戏开始之前输入用户名、题目数量");
	outtextxy(125, 130, "和总时间。答题前按Shift表示开始输入");
	outtextxy(125, 160, "答案，按回车键表示结束作答。答题开始");
	outtextxy(125, 190, "系统会自动计时，中途如果选择暂停或者");
	outtextxy(125, 220, "查看当前做题情况则计时停止。答题结束");
	outtextxy(125, 250, "会自动保存目前做题情况。");

	setfillcolor(YELLOW);
	fillrectangle(520, 400, 620, 430);
	settextcolor(BLUE);
	outtextxy(530, 405, "continue");
	while (x!=8) {
		x = checkmouse();
	}
}

void output(NODE* &hT, NODE* &p, NODE* &hF) 
{
	NODE* f;
	int i = 80;
	int j = 0;
	char s[20];
	setfillcolor(BLUE);
	fillrectangle(50, 50, 400, 400);
	outtextxy(100, 70, "作对的题：");
	outtextxy(100, 200, "作错的题：");
	outtextxy(100, 330, "剩余题目：");
	f = hT->next;
	while (f != NULL) {
		sprintf_s(s, "%d", f->data1);
		outtextxy(i+20, j+90, s);
		sprintf_s(s, "%c", f->sign);
		outtextxy(i+30, j+90, s);
		sprintf_s(s, "%d", f->data2);
		outtextxy(i+40, j+90, s);
		i += 40;
		f = f->next;
		if (i > 400) {
			j += 20;
			i = 0;
		}
	}
	f = hF->next;
	i = 80;
	j = 0;
	while (f != NULL) {
		sprintf_s(s, "%d", f->data1);
		outtextxy(i + 20, j + 220, s);
		sprintf_s(s, "%c", f->sign);
		outtextxy(i + 30, j + 220, s);
		sprintf_s(s, "%d", f->data2);
		outtextxy(i + 40, j + 220, s);
		i += 40;
		f = f->next;
		if (i > 400) {
			j += 20;
			i = 0;
		}
	}

	f = p->next;
	i = 80;
	j = 0;
	while (f != NULL) {
		sprintf_s(s, "%d", f->data1);
		outtextxy(i + 20, j + 360, s);
		sprintf_s(s, "%c", f->sign);
		outtextxy(i + 30, j +360, s);
		sprintf_s(s, "%d", f->data2);
		outtextxy(i + 40, j + 360, s);
		i += 40;
		f = f->next;
		if (i > 400) {
			j += 20;
			i = 0;
		}
	}
}

void stoptime(int &t)
{
	int x = 0;
	clock_t t1, t2;
	int t3;
	t1 = clock();
	while (1) {
		Sleep(20);
		t2 = clock();
		t3 = (t2 - t1) / 1000;
		x = checkmouse();
		if (  x==1 || x == 4) {
			break;
		}
	}
	t+= t3;
}


void save(USER& user, NODE *hT, NODE *orip, NODE *hF, int t1) {
	FILE* fp;
	NODE* p;
	errno_t err = fopen_s(&fp, "D:\\Desktop\\4.22\\game.txt", "w");
	if (fp != NULL) {
		fprintf(fp, "name:%s score:%d time:%d\n", user.name, user.score, t1);
		fprintf(fp, "正确的:");
	}
    p = hT->next;
	while (p != NULL) {
		if (p->next != NULL) {
			fprintf(fp, " %d%c%d= ", p->data1, p->sign, p->data2);
			p = p->next;
		}
		else {
			fprintf(fp, " %d%c%d= ", p->data1, p->sign, p->data2);
			p = p->next;
		}
	}

	fprintf(fp, "\n");
	fprintf(fp, "还没做的:");
	p = orip->next;
	while (p != NULL) {
		if (p->next != NULL) {
			fprintf(fp, " %d%c%d= ", p->data1, p->sign, p->data2);
			p = p->next;
		}
		else {
			fprintf(fp, " %d%c%d= ", p->data1, p->sign, p->data2);
			p = p->next;
		}
	}

	fprintf(fp, "\n");
	fprintf(fp, "做错的:");
	p = hF->next;
	while (p != NULL) {
		if (p->next != NULL) {
			fprintf(fp, " %d%c%d= ", p->data1, p->sign, p->data2);
			p = p->next;
		}
		else {
			fprintf(fp, " %d%c%d= ", p->data1, p->sign, p->data2);
			p = p->next;
		}
	}
	fprintf(fp, "\n");
	fclose(fp);
}

int checkmouse() {
	int x = 0;
	MOUSEMSG mmsg;
	int mouseX;
	int mouseY;
	if (MouseHit()) {
		mmsg = GetMouseMsg();
		switch (mmsg.uMsg) {
		case WM_LBUTTONDOWN:
			mouseX = mmsg.x;
			mouseY = mmsg.y;
			x = checkButton(mouseX, mouseY);
		}
	}
	return x;
}


void displayButton()
{
	setfillcolor(BLUE);
	settextstyle(20, 0, "圆体");
	setlinecolor(RED);
	settextcolor(RED);
	setbkmode(TRANSPARENT);
	fillrectangle(520, 10, 600, 50);
	outtextxy(530, 20, "START");
	setfillcolor(BLUE);
	fillrectangle(520, 55, 600, 95);
	outtextxy(530, 65, "PAUSE");
	fillrectangle(520, 100, 600, 140);
	outtextxy(530, 110, "SKIP");
	fillrectangle(520, 145, 600, 185);
	outtextxy(530, 155, "REVIEW");
	fillrectangle(520, 190, 600, 225);
	outtextxy(530, 195, "LOGOUT");
	setfillcolor(YELLOW);
	fillrectangle(542, 365, 572, 395);
	fillrectangle(542, 428, 572, 458);
	setcolor(RED);
	setlinestyle(PS_SOLID, 2);
	line(490, 0, 490, 480);
	line(490, 250, 640, 250);
}

int inittime(USER& user)
{
	int Time = 0;
	InputBox(user.time, 50, "请输入时间：");
	Time = atoi(user.time);
	return Time;
}

void initname(USER& user)
{
	InputBox(user.name, 50, "请输入用户名：");	
}

void initnum(USER& user)
{
	InputBox(user.num, 50, "请输入题目数量：");
}

void  background()
{
	loadimage(&back, "image\\background.jpg", WIDTH, HEIGHT);
	cleardevice();
	setcolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	putimage(-150, 0, &back);
	setlinestyle(PS_SOLID, 2);
	rectangle(1, 1, WIDTH - 2, HEIGHT - 2);
	line(490, 0, 490, 480);
	line(490, 250, 640, 250);

}

void drawscore(int score)
{
	char s[100];
	sprintf_s(s, "%d", score);
	outtextxy(550, 435, s);
}

int drawtime(int sec, int time,int start,int t1,int t2)
{
	char buf[10];
	t1= time + (start - sec)/1000+t2/1000;
	sprintf_s(buf, "%d", t1);
	outtextxy(565, 300, buf);
	return t1;
}




int checkButton(int mouseX, int mouseY)
{
	if (mouseX >= 520 && mouseX <= 600 && mouseY >= 10 && mouseY <= 50) {
		clearrectangle(519, 9, 601, 51);
		outtextxy(530, 20, "START");
		Sleep(20);
		setfillcolor(BLUE);
		fillrectangle(520, 10, 600, 50);
		outtextxy(530, 20, "START");
		return 1;
	}
		
	else if (mouseX >= 520 && mouseX <= 600 && mouseY >= 55 && mouseY <= 95) {
		clearrectangle(520, 55, 599, 94);
		outtextxy(530, 65, "PAUSE");
		Sleep(20);
		setfillcolor(BLUE);
		fillrectangle(520, 55, 600, 95);
		outtextxy(530, 65, "PAUSE");
		return 2;
	}
		
	else if (mouseX >= 520 && mouseX <= 600 && mouseY >= 100 && mouseY <= 140) {
		clearrectangle(519, 99, 601, 141);
		outtextxy(530, 110, "SKIP");
		Sleep(20);
		setfillcolor(BLUE);
		fillrectangle(520, 100, 600, 140);
		outtextxy(530, 110, "SKIP");
		return 3;
	}
	else if (mouseX >= 520 && mouseX <= 600 && mouseY >= 145 && mouseY <= 185) {
		clearrectangle(520, 145, 599, 184);
		outtextxy(530, 155, "REVIEW");
		Sleep(20);
		setfillcolor(BLUE);
		fillrectangle(520, 145, 600, 185);
		outtextxy(530, 155, "REVIEW");
		return 4;
	}
	
	else if (mouseX >= 200 && mouseX <= 440 && mouseY >= 170 && mouseY <= 230) {
		return 5;
	}
	else if (mouseX >= 200 && mouseX <= 440 && mouseY >= 320 && mouseY <= 380) {
		return 7;
	}
	else if (mouseX >= 520 && mouseX <= 620 && mouseY >= 400 && mouseY <=480) {
		return 8;
	}

	else if (mouseX >= 520 && mouseX <= 600 && mouseY >= 190 && mouseY <= 225) {
		clearrectangle(520, 190, 600, 225);
		outtextxy(530, 195, "LOGOUT");
		Sleep(20);
		setfillcolor(BLUE);
		fillrectangle(520, 190, 600, 225);
		outtextxy(530, 195, "LOGOUT");
		return -1;
	}
}
