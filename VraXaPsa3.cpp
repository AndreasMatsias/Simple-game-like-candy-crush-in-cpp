#include <GL/gl.h>     // openGL header
#include <GL/glu.h>   // glut header
#include <GL/glut.h>   // glut header
#include<stdlib.h>
#include<stdio.h>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <ostream>

#define dx 30
#define dy 30
//some_Protoypes//////////////////////////////////////////////////////////////////////////
void esc (unsigned char key, int x, int y);
void create_grid(void);
void create_game_grid(void);
void vanish();
void threesame();
void init();
void loadTextureFromFile(const char *filename);
////////////////////////////////////////////////////////////////////////////////////
int count=0;
int moves=30;
int score=0;
GLsizei winWidth = 500, winHeight = 500;  // Initial display-window size.
GLfloat red = 1, green = 1, blue = 1;  // Initial triangle color: white.
int firstWindow,secondWindow; 
typedef struct tile{
	GLfloat xzero,yzero,x1,y1;
	int color;
}tile;
tile board[20][20];
GLfloat color[6][3]={{red,0,0},{0,0,blue},{0,green,0},{0,green,blue},{red,0,blue},{1,1,1}};
GLfloat xzero=0;
GLfloat yzero=0;
GLint i,j,stroke=0,pastx,pasty,nextx,nexty,swapthetwo=0;

void init (void)
{
	int i,j;
	time_t t;
	srand((unsigned) time(&t));
	glClearColor (0.0, 0.0, 0.0, 0.0);	
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();// start with identity matrix
	gluOrtho2D(0.0,499.0,0.0,499.0); 
	glutPostRedisplay();
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{
			board[i][j].xzero=xzero+i*dx+1.5;
			board[i][j].x1=xzero+(i+1)*dx-1.5;
			board[i][j].yzero=yzero+j*dy+1.5;
			board[i][j].y1=yzero+(j+1)*dy-1.5;
			board[i][j].color=rand()%5;
		}	
	}
	threesame();
	threesame();
	threesame();
	threesame();
	threesame();
}
void threesame()
{
	for(i=0;i<15;i++)
			{
			for(j=0;j<15;j++)
			{
				if(board[i][j].color==board[i+1][j].color && board[i+1][j].color==board[i+2][j].color&& board[i][j].color==board[i+2][j].color)
				{
					if(board[i][j].color==0)
					{
						int a1,a2,a3;
						a1=rand()%2?1:2;
						a2=rand()%2?3:4;
						a3=rand()%2?a1:a2;
						board[i][j].color=a3;
					}
					if(board[i][j].color==1)
					{
						int b1,b2,b3;
						b1=rand()%2?0:2;
						b2=rand()%2?3:4;
						b3=rand()%2?b1:b2;
						board[i][j].color=b3;
					}
					if(board[i][j].color==2)
					{
						int c1,c2,c3;
						c1=rand()%2?1:0;
						c2=rand()%2?3:4;
						c3=rand()%2?c1:c2;
						board[i][j].color=c3;
					}
					if(board[i][j].color==3)
					{
						int d1,d2,d3;
						d1=rand()%2?1:2;
						d2=rand()%2?0:4;
						d3=rand()%2?d1:d2;
						board[i][j].color=d3;
					}
					if(board[i][j].color==4)
					{
						int e1,e2,e3;
						e1=rand()%2?1:2;
						e2=rand()%2?3:0;
						e3=rand()%2?e1:e2;
						board[i][j].color=e3;
					}
				}
				if(board[i][j].color==board[i][j+1].color && board[i][j+1].color==board[i][j+2].color && board[i][j].color==board[i][j+2].color)
				{
					if(board[i][j].color==0)
					{
						int f1,f2,f3;
						f1=rand()%2?1:2;
						f2=rand()%2?3:4;
						f3=rand()%2?f1:f2;
						board[i][j].color=f3;
					}
					if(board[i][j].color==1)
					{
						int g1,g2,g3;
						g1=rand()%2?0:2;
						g2=rand()%2?3:4;
						g3=rand()%2?g1:g2;
						board[i][j].color=g3;
					}
					if(board[i][j].color==2)
					{
						int h1,h2,h3;
						h1=rand()%2?1:0;
						h2=rand()%2?3:4;
						h3=rand()%2?h1:h2;
						board[i][j].color=h3;
					}
					if(board[i][j].color==3)
					{
						int j1,j2,j3;
						j1=rand()%2?1:2;
						j2=rand()%2?0:4;
						j3=rand()%2?j1:j2;
						board[i][j].color=j3;
					}
					if(board[i][j].color==4)
					{
						int k1,k2,k3;
						k1=rand()%2?1:2;
						k2=rand()%2?3:0;
						k3=rand()%2?k1:k2;
						board[i][j].color=k3;
					}
							
				}
		}
	}
}
void vanish()
{
		for(i=0;i<15;i++)
		{
			for(j=0;j<15;j++)
			{
				if(board[i][j].color==0 &&board[i+1][j].color==0 && board[i+2][j].color==0)
				{
					board[i][j].color=5;
					board[i+1][j].color=5;
					board[i+2][j].color=5;
					score=score+10;
				}
				if(board[i][j].color==0 &&board[i][j+1].color==0 &&board[i][j+2].color==0)
				{

					board[i][j].color=5;
					board[i][j+1].color=5;
					board[i][j+2].color=5;
					score=score+10;	
				}
				if(board[i][j].color==1 &&board[i+1][j].color==1 && board[i+2][j].color==1)
				{
					board[i][j].color=5;
					board[i+1][j].color=5;
					board[i+2][j].color=5;
					score=score+10;
				}
				if(board[i][j].color==1 &&board[i][j+1].color==1 &&board[i][j+2].color==1)
				{					
					board[i][j].color=5;
					board[i][j+1].color=5;
					board[i][j+2].color=5;	
					score=score+10;
				}
				//ORIZONTIA
				if(board[i][j].color==4 &&board[i+1][j].color==4 && board[i+2][j].color==4)
				{
					board[i][j].color=5;
					board[i+1][j].color=5;
					board[i+2][j].color=5;
					score=score+10;
					//apostash 1
					for(int k=0;k<3;k++)
					{
						if(board[i+k][j-1].color!=3)//16
						{
							board[i+k][j-1].color=5;
							score=score+2;
						}
						if(board[i+k][j-1].color==3){
							score=score-1;
						}
					}
					if(board[i-1][j].color!=3)
					{
						board[i-1][j].color=5;
						score=score+2;
					}
					if(board[i+3][j].color!=3)
					{
						board[i+3][j].color=5;
						score=score+2;
					}
					if(board[i-1][j].color==3){
						score=score-1;
					}
					if(board[i+3][j].color==3){
						score=score-1;
					}
					for(int k=2;k>-1;k--)
					{
						if(board[i+k][j+1].color!=3)
						{
							board[i+k][j+1].color=5;
							score=score+2;
						}
						if(board[i+k][j+1].color==3){
							score=score-1;
						}
					}
					////apostash 2
					for(int k=-1;k<4;k++)
					{
						if(board[i+k][j-2].color==2)
						{
							board[i+k][j-2].color=5;
							score=score+3;
						}
					}
					for(int k=-1;k<2;k++)
					{
						if(board[i+4][j+k].color==2)
						{
							board[i+4][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=3;k>-2;k--)
					{
						if(board[i+k][j+2].color==2)
						{
							board[i+k][j+2].color=5;
							score=score+3;
						}
					}
					for(int k=1;k>-2;k--)
					{
						if(board[i-2][j+k].color==2)
						{
							board[i-2][j+k].color=5;
							score=score+3;
						}
					}
					//apostash3
					for(int k=-2;k<5;k++)
					{
						if(board[i+k][j-3].color==2)
						{
							board[i+k][j-3].color=5;
							score=score+3;
						}
					}
					for(int k=-2;k<6;k++)
					{
						if(board[i+5][j+k].color==2)
						{
							board[i+5][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=4;k>-3;k--)
					{
						if(board[i+k][j+3].color==2)
						{
							board[i+k][j+3].color=5;
							score=score+3;
						}
					}
					for(int k=2;k>-3;k--)
					{
						if(board[i-3][j+k].color==2)
						{
							board[i-3][j+k].color=5;
							score=score+3;
						}
					}	
				}
				if(board[i][j].color==2 &&board[i+1][j].color==2 && board[i+2][j].color==2)
				{
					board[i][j].color=5;
					board[i+1][j].color=5;
					board[i+2][j].color=5;
					score=score+10;
					//apostash 1
					for(int k=0;k<3;k++)
					{
						if(board[i+k][j-1].color!=4)
						{
							board[i+k][j-1].color=5;
							score=score+2;
						}
						if(board[i+k][j-1].color==4){
							score=score-1;
						}
					}
					if(board[i-1][j].color!=4)
					{
						board[i-1][j].color=5;
							score=score+2;
					}
					if(board[i-1][j].color==4){
						score=score-1;
					}
					if(board[i+3][j].color!=4)
					{
						board[i+3][j].color=5;
						score=score+2;
					}
					if(board[i+3][j].color==4){
						score=score-1;
					}
					for(int k=2;k>-1;k--)
					{
						if(board[i+k][j+1].color!=4)//16
						{
							board[i+k][j+1].color=5;
							score=score+2;
						}
						if(board[i+k][j+1].color==4){
							score=score-1;
						}
					}
					////apostash 2
					for(int k=-1;k<4;k++)
					{
						if(board[i+k][j-2].color==3)
						{
							board[i+k][j-2].color=5;
							score=score+3;
						}
					}
					for(int k=-1;k<2;k++)
					{
						if(board[i+4][j+k].color==3)
						{
							board[i+4][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=3;k>-2;k--)
					{
						if(board[i+k][j+2].color==3)
						{
							board[i+k][j+2].color=5;
							score=score+3;
						}
					}
					for(int k=1;k>-2;k--)
					{
						if(board[i-2][j+k].color==3)
						{
							board[i-2][j+k].color=5;
							score=score+3;
						}
					}
					//apostash3
					for(int k=-2;k<5;k++)
					{
						if(board[i+k][j-3].color==3)
						{
							board[i+k][j-3].color=5;
							score=score+3;
						}
					}
					for(int k=-2;k<6;k++)
					{
						if(board[i+5][j+k].color==3)
						{
							board[i+5][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=4;k>-3;k--)
					{
						if(board[i+k][j+3].color==3)
						{
							board[i+k][j+3].color=5;
							score=score+3;
						}
					}
					for(int k=2;k>-3;k--)
					{
						if(board[i-3][j+k].color==3)
						{
							board[i-3][j+k].color=5;
							score=score+3;
						}
					}	
				}
				if(board[i][j].color==3 &&board[i+1][j].color==3 && board[i+2][j].color==3)
				{
					board[i][j].color=5;
					board[i+1][j].color=5;
					board[i+2][j].color=5;
					score=score+10;
					//apostash 1
					for(int k=0;k<3;k++)
					{
						if(board[i+k][j-1].color!=2)//16
						{
							board[i+k][j-1].color=5;
							score=score+2;
						}
						if(board[i+k][j-1].color==2){
							score=score-1;
						}
					}
					if(board[i-1][j].color!=2)
					{
						board[i-1][j].color=5;
							score=score+2;

					}
					if(board[i-1][j].color==2){
						score=score-1;
					}
					if(board[i+3][j].color!=2)
					{
						board[i+3][j].color=5;
							score=score+2;
					}
					if(board[i+3][j].color==2){
						score=score-1;
					}
					for(int k=2;k>-1;k--)
					{
						if(board[i+k][j+1].color!=2)//16
						{
							board[i+k][j+1].color=5;
							score=score+2;

						}
						if(board[i+k][j+1].color==2){
							score=score-1;
						}
					}
					////apostash 2
					for(int k=-1;k<4;k++)
					{
						if(board[i+k][j-2].color==4)
						{
							board[i+k][j-2].color=5;
							score=score+3;
						}
					}
					for(int k=-1;k<2;k++)
					{
						if(board[i+4][j+k].color==4)
						{
							board[i+4][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=3;k>-2;k--)
					{
						if(board[i+k][j+2].color==4)
						{
							board[i+k][j+2].color=5;
							score=score+3;
						}
					}
					for(int k=1;k>-2;k--)
					{
						if(board[i-2][j+k].color==4)
						{
							board[i-2][j+k].color=5;
							score=score+3;
						}
					}
					//apostash3
					for(int k=-2;k<5;k++)
					{
						if(board[i+k][j-3].color==4)
						{
							board[i+k][j-3].color=5;
							score=score+3;
						}
					}
					for(int k=-2;k<6;k++)
					{
						if(board[i+5][j+k].color==4)
						{
							board[i+5][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=4;k>-3;k--)
					{
						if(board[i+k][j+3].color==4)
						{
							board[i+k][j+3].color=5;
							score=score+3;
						}
					}
					for(int k=2;k>-3;k--)
					{
						if(board[i-3][j+k].color==4)
						{
							board[i-3][j+k].color=5;
							score=score+3;
						}
					}	
				}
				//KATHETA
				if(board[i][j].color==4 &&board[i][j+1].color==4 &&board[i][j+2].color==4)
				{
					board[i][j].color=5;
					board[i][j+1].color=5;
					board[i][j+2].color=5;
					score=score+10;
					//apostash 1
					for(int k=0;k<3;k++)
					{
						if(board[i+1][j+k].color!=3)
						{
							board[i+1][j+k].color=5;
							score=score+2;
						}
						if(board[i+1][j+k].color==3){
							score=score-1;
						}
					}
					if(board[i][j-1].color!=3)
					{
						board[i][j-1].color=5;
						score=score+2;
					}
					if(board[i][j-1].color==3){
						score=score-1;
					}
					if(board[i][j+3].color!=3)
					{
						board[i][j+3].color=5;
						score=score+2;
					}
					if(board[i][j+3].color==3){
						score=score-1;
					}
					for(int k=2;k>-1;k--)
					{
						if(board[i-1][j+k].color!=3)
						{
							board[i-1][j+k].color=5;
							score=score+2;
						}
						if(board[i-1][j+k].color==3){
							score=score-1;
						}
					}
					////apostash 2
					for(int k=-1;k<2;k++)
					{
						if(board[i+k][j-2].color==2)
						{
							board[i+k][j-2].color=5;
							score=score+3;
						}
					}
					for(int k=-1;k<4;k++)
					{
						if(board[i+2][j+k].color==2)
						{
							board[i+2][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=1;k>-2;k--)
					{
						if(board[i+k][j+4].color==2)
						{
							board[i+k][j+4].color=5;
							score=score+3;
						}
					}
					for(int k=3;k>-2;k--)
					{
						if(board[i-2][j+k].color==2)
						{
							board[i-2][j+k].color=5;
							score=score+3;
						}
					}
					//apostash3
					for(int k=-2;k<3;k++)
					{
						if(board[i+k][j-3].color==2)
						{
							board[i+k][j-3].color=5;
							score=score+3;
						}
					}
					for(int k=-2;k<5;k++)
					{
						if(board[i+3][j+k].color==2)
						{
							board[i+3][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=2;k>-3;k--)
					{
						if(board[i+k][j+5].color==2)
						{
							board[i+k][j+5].color=5;
							score=score+3;
						}
					}
					for(int k=4;k>-3;k--)
					{
						if(board[i-3][j+k].color==2)
						{
							board[i-3][j+k].color=5;
							score=score+3;
						}
					}	
				}
				if(board[i][j].color==2 &&board[i][j+1].color==2 &&board[i][j+2].color==2)
				{
					board[i][j].color=5;
					board[i][j+1].color=5;
					board[i][j+2].color=5;
					score=score+10;
					//apostash 1
					for(int k=0;k<3;k++)
					{
						if(board[i+1][j+k].color!=4)
						{
							board[i+1][j+k].color=5;
							score=score+2;
						}
						if(board[i+1][j+k].color==4){
							score=score-1;
						}
					}
					if(board[i][j-1].color!=4)
					{
						board[i][j-1].color=5;
						score=score+2;
					}
					if(board[i][j-1].color==4){
						score=score-1;
					}
					if(board[i][j+3].color!=4)
					{
						board[i][j+3].color=5;
						score=score+2;
					}
					if(board[i][j+3].color==4){
						score=score-1;
					}
					for(int k=2;k>-1;k--)
					{
						if(board[i-1][j+k].color!=4)
						{
							board[i-1][j+k].color=5;
							score=score+2;
						}
						if(board[i-1][j+k].color==4){
							score=score-1;
						}
					}
					////apostash 2
					for(int k=-1;k<2;k++)
					{
						if(board[i+k][j-2].color==3)
						{
							board[i+k][j-2].color=5;
							score=score+3;
							
						}
					}
					for(int k=-1;k<4;k++)
					{
						if(board[i+2][j+k].color==3)
						{
							board[i+2][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=1;k>-2;k--)
					{
						if(board[i+k][j+4].color==3)
						{
							board[i+k][j+4].color=5;
							score=score+3;
						}
					}
					for(int k=3;k>-2;k--)
					{
						if(board[i-2][j+k].color==3)
						{
							board[i-2][j+k].color=5;
							score=score+3;
						}
					}
					//apostash3
					for(int k=-2;k<3;k++)
					{
						if(board[i+k][j-3].color==3)
						{
							board[i+k][j-3].color=5;
							score=score+3;
						}
					}
					for(int k=-2;k<5;k++)
					{
						if(board[i+3][j+k].color==3)
						{
							board[i+3][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=2;k>-3;k--)
					{
						if(board[i+k][j+5].color==3)
						{
							board[i+k][j+5].color=5;
							score=score+3;
						}
					}
					for(int k=4;k>-3;k--)
					{
						if(board[i-3][j+k].color==3)
						{
							board[i-3][j+k].color=5;
							score=score+3;
						}
					}	
				}
				if(board[i][j].color==3 &&board[i][j+1].color==3 &&board[i][j+2].color==3)
				{
					board[i][j].color=5;
					board[i][j+1].color=5;
					board[i][j+2].color=5;
					score=score+10;
					//apostash 1
					for(int k=0;k<3;k++)
					{
						if(board[i+1][j+k].color!=2)
						{
							board[i+1][j+k].color=5;
							score=score+2;
						}
						if(board[i+1][j+k].color==2){
							score=score-1;
						}
					}
					if(board[i][j-1].color!=2)
					{
						board[i][j-1].color=5;
						score=score+2;
					}
					if(board[i][j-1].color==2){
						score=score-1;
					}
					if(board[i][j+3].color!=2)
					{
						board[i][j+3].color=5;
						score=score+2;
					}
					if(board[i][j+3].color==2){
						score=score-1;
					}
					for(int k=2;k>-1;k--)
					{
						if(board[i-1][j+k].color!=2)
						{
							board[i-1][j+k].color=5;
							score=score+2;
						}
						if(board[i-1][j+k].color==2){
							score=score-1;
						}
					}
					////apostash 2
					for(int k=-1;k<2;k++)
					{
						if(board[i+k][j-2].color==4)
						{
							board[i+k][j-2].color=5;
							score=score+3;
						}
					}
					for(int k=-1;k<4;k++)
					{
						if(board[i+2][j+k].color==4)
						{
							board[i+2][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=1;k>-2;k--)
					{
						if(board[i+k][j+4].color==4)
						{
							board[i+k][j+4].color=5;
							score=score+3;
						}
					}
					for(int k=3;k>-2;k--)
					{
						if(board[i-2][j+k].color==4)
						{
							board[i-2][j+k].color=5;
							score=score+3;
						}
					}
					//apostash3
					for(int k=-2;k<3;k++)
					{
						if(board[i+k][j-3].color==4)
						{
							board[i+k][j-3].color=5;
							score=score+3;
						}
					}
					for(int k=-2;k<5;k++)
					{
						if(board[i+3][j+k].color==4)
						{
							board[i+3][j+k].color=5;
							score=score+3;
						}
					}
					for(int k=2;k>-3;k--)
					{
						if(board[i+k][j+5].color==4)
						{
							board[i+k][j+5].color=5;
							score=score+3;
						}
					}
					for(int k=4;k>-3;k--)
					{
						if(board[i-3][j+k].color==4)
						{
							board[i-3][j+k].color=5;
							score=score+3;
						}
					}	
				}
				
	
			}
		}
}
void mouse(int btn,int status,int x,int y)
{
	int c=0;
	y=500-y;
	if(stroke==0&&btn==GLUT_LEFT_BUTTON&&status==GLUT_DOWN)
	{
		stroke=1;
		pastx=x;
		pasty=y;
		//printf("pastx=%d,%d\n",pastx/dx,pasty/dy);
		vanish();
	}
	
	if(stroke==1&&btn==GLUT_LEFT_BUTTON&&status==GLUT_UP)
	{
		
		stroke=0;
		nextx=x;
		nexty=y;
		//printf("nextx=%d,%d\n",nextx/dx,nexty/dy);
		
		if(abs(pastx/dx-nextx/dx)==1&&pasty/dy==nexty/dy)
		{
			swapthetwo=1;
			count++;
			moves--;
			printf("=================\n");
			printf("MOVES_LEFT:%d\n",moves);
			printf("=================\n");
		}
		if(abs(pasty/dy-nexty/dy)==1&&pastx/dx==nextx/dx)
		{
			swapthetwo=1;
			count++;
			moves--;
			printf("=================\n");
			printf("MOVES_LEFT:%d\n",moves);
			printf("=================\n");
			printf("=================\n");
			printf("SCORE:%d\n",score);
			printf("=================\n");
		}
		if(board[nextx/dx][nexty/dy].color==4 &&board[nextx/dx-1][nexty/dy].color==2 ) {
				board[i-1][nexty/dy].color=5;
				score=score+2;
		}
		if(board[nextx/dx][nexty/dy].color==4 &&board[nextx/dx][nexty/dy+1].color==2 ){
			board[nextx/dx][nexty/dy+1].color=5;
			score=score+2;
		}
		if(board[nextx/dx][nexty/dy].color==4 &&board[nextx/dx+1][nexty/dy].color==2 ){
			board[nextx/dx+1][nexty/dy].color=5;
			score=score+2;
				}
		if(board[nextx/dx][nexty/dy].color==4 &&board[nextx/dx][nexty/dy-1].color==2 ){
			board[nextx/dx][nexty/dy-1].color=5;
			score=score+2;
		}

		if(board[nextx/dx][nexty/dy].color==2 &&board[nextx/dx-1][nexty/dy].color==3 ) {
			board[nextx/dx-1][nexty/dy].color=5;
			score=score+2;
		}
		if(board[nextx/dx][nexty/dy].color==2 &&board[nextx/dx][nexty/dy+1].color==3 ) {
			board[nextx/dx][nexty/dy+1].color=5;
			score=score+2;
		}
		if(board[nextx/dx][nexty/dy].color==2 &&board[nextx/dx+1][nexty/dy].color==3 ) {
			board[nextx/dx+1][nexty/dy].color=5;
			score=score+2;
		}
		if(board[nextx/dx][nexty/dy].color==2 &&board[nextx/dx][nexty/dy-1].color==3 ) {
			board[nextx/dx][nexty/dy-1].color=5;
			score=score+2;
		}

		if(board[nextx/dx][nexty/dy].color==3 &&board[nextx/dx-1][nexty/dy].color==4 ) {
			board[nextx/dx-1][nexty/dy].color=5;
			score=score+2;
		}
		if(board[nextx/dx][nexty/dy].color==3 &&board[nextx/dx][nexty/dy+1].color==4 ){

			board[nextx/dx][nexty/dy+1].color=5;
			score=score+2;
		}
		if(board[nextx/dx][nexty/dy].color==3 &&board[nextx/dx+1][nexty/dy].color==4 ) {
			board[nextx/dx+1][nexty/dy].color=5;
			score=score+2;
		}
		if(board[nextx/dx][nexty/dy].color==3 &&board[nextx/dx][nexty/dy-1].color==4 ) {
			board[i][j-1].color=5;
			score=score+2;
		}
	}
	
	if (count==30)
	{
		printf("\n\n=================\n");
		printf("GAME OVER!!!\n");
		printf("=================\n");
		printf("YOUR SCORE:%d\n",score);
		printf("=================\n");
		exit(0);
	}
}
void idle(void)
{
	int temp;
	if(swapthetwo)
	{	
		swapthetwo=0;
		temp=board[pastx/dx][pasty/dy].color;
		board[pastx/dx][pasty/dy].color=board[nextx/dx][nexty/dy].color;
		board[nextx/dx][nexty/dy].color=temp;
		//printf("Swapped\n");
		
	}
	glutPostRedisplay();
}
//function to load the RAW file
const char* filename = "";

void loadTextureFromFile(const char *filename)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_FLAT);
	//glEnable(GL_DEPTH_TEST);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("scissors.bmp", &width, &height, &nrChannels, 0);
	if (data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}
void create_game_grid(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for(i=0;i<15;i++)
	{
		for(j=0;j<15;j++)
		{	
			glColor3fv(color[board[i][j].color]);
			glBegin(GL_POLYGON);
         	glVertex2f(board[i][j].xzero,board[i][j].yzero);
         	glVertex2f(board[i][j].xzero,board[i][j].y1);
         	glVertex2f(board[i][j].x1,board[i][j].y1);
         	glVertex2f(board[i][j].x1,board[i][j].yzero);
         	glEnd();	
	    }
	}
	glFlush();
	glutSwapBuffers();
}

void Menu (GLint selectedOption)
{
	
	switch (selectedOption) 
	{
		case 1: 
			glutDestroyWindow(firstWindow);
			glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
			glutInitWindowPosition (0,0);
			glutInitWindowSize (winWidth, winHeight);
			secondWindow=glutCreateWindow ("VraXaPsa III:MainGame");
			init();
			glutDisplayFunc (create_game_grid);
			glutIdleFunc(idle);
			glutMouseFunc(mouse);
			glutKeyboardFunc(esc);
			loadTextureFromFile(filename);
			break;
		case 2:  
			exit(0);  
	}	
}





void create_grid(){
	glClear(GL_COLOR_BUFFER_BIT);
	for(i=0;i<15;i++){
		for(j=0;j<15;j++){
            glBegin(GL_POLYGON);
				glColor3f(0.94,0.87,0.80);
				glTexCoord2f(0.0, 0.0);
         		glVertex2f(board[i][j].xzero,board[i][j].yzero);
				glTexCoord2f(1.0, 0.0);
         		glVertex2f(board[i][j].xzero,board[i][j].y1);
				glTexCoord2f(1.0, 1.0);
         		glVertex2f(board[i][j].x1,board[i][j].y1);
				glTexCoord2f(0.0, 1.0);
         		glVertex2f(board[i][j].x1,board[i][j].yzero);
         	glEnd();
	    }
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
		glColor3f(0.94,0.87,0.80);
		glTexCoord2f(0.0, 0.0);
        glVertex2f(board[0][0].xzero,board[0][0].yzero);
		glTexCoord2f(1.0, 0.0);
        glVertex2f(board[0][0].xzero,board[0][0].y1);
		glTexCoord2f(1.0, 1.0);
        glVertex2f(board[0][0].x1,board[0][0].y1);
		glTexCoord2f(0.0, 1.0);
        glVertex2f(board[0][0].x1,board[0][0].yzero);
    glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0.94,0.87,0.80);
		glTexCoord2f(0.0, 0.0);
        glVertex2f(board[14][14].xzero,board[14][14].yzero);
		glTexCoord2f(1.0, 0.0);
        glVertex2f(board[14][14].xzero,board[14][14].y1);
		glTexCoord2f(1.0, 1.0);
    	glVertex2f(board[14][14].x1,board[14][14].y1);
		glTexCoord2f(0.0, 1.0);
        glVertex2f(board[14][14].x1,board[14][14].yzero);
    glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);
	glutSwapBuffers();
}
/////////////////////////////////////////////////////////////////////////////////////////////
void esc (unsigned char key, int x, int y) 
{
	if (key==27) exit(0);			// Escape button exits the program
}
//////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
	printf("=================\n");
	printf("Rock==CYAN\n");
	printf("Paper==GREEN\n");
	printf("Pink==SCISSORS\n");
	printf("=================\n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE| GLUT_MULTISAMPLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0,0);
	firstWindow=glutCreateWindow("VraXaPsaIII");
	loadTextureFromFile(filename);

	glutDisplayFunc (create_grid);
	init();
	glutCreateMenu (Menu);// Create pop-up menu.
		glutAddMenuEntry ("Start GAME", 1);
		glutAddMenuEntry ("Exit", 2);
/*  Select a menu option using the right mouse button.  */
	glutAttachMenu (GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(esc);
	glutMainLoop();
	return 0;
}
