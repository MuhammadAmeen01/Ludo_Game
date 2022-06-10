//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <pthread.h>
//#include "drawGrid.h"
#include <semaphore.h>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
void PrintableKeys(unsigned char key, int x, int y);
void *main_thread(void *ptr);
int check_save_stop(int x, int y);
void blue_collision();
void red_collision();
void yellow_collision();
void green_collision();
int diceroll();
int check_save_stop(int x, int y);
void MoveRed(int which_player, int value);
void MoveBlue(int which_player, int value);
void MoveYellow(int which_player, int value);
void MoveGreen(int which_player, int value);
void *go_green(void *p);
void *go_yellow(void *p);
void *go_blue(void *p);
void *go_red(void *p);
int check_redwin();
int check_greenwin();
int check_bluewin();
int check_yellowwin();
//drawGrid d;
int b_key_check = 0;
int y_key_check = 0;
int r_key_check = 0;
int g_key_check = 0;
bool y_key = false;
bool b_key = false;
bool r_key = false;
bool g_key = false;
pthread_t tid, tid1, tid2, tid3, tid4;
int value = 5;
int blue_px[4] = {100, 200, 100, 200};
int red_px[4] = {600, 600, 700, 700};
int yellow_px[4] = {600, 700, 600, 700};
int green_px[4] = {100, 200, 200, 100};
int blue_py[4] = {600, 600, 700, 700};
int red_py[4] = {600, 700, 700, 600};
int yellow_py[4] = {100, 100, 200, 200};
int green_py[4] = {100, 100, 200, 200};

int temp_blue_px[4] = {100, 200, 100, 200}; //temp array to save coardinates of all token, if the token is hit by another different player token to that it could return back to it's original position..................................
int temp_red_px[4] = {600, 600, 700, 700};
int temp_yellow_px[4] = {600, 700, 600, 700};
int temp_green_px[4] = {100, 200, 200, 100};
int temp_blue_py[4] = {600, 600, 700, 700};
int temp_red_py[4] = {600, 700, 700, 600};
int temp_yellow_py[4] = {100, 100, 200, 200};
int temp_green_py[4] = {100, 100, 200, 200};

int bluepath1 = 0;
int bluepath2 = 0;
int bluepath3 = 0;
int bluepath4 = 0;

int yellowpath1 = 0;
int yellowpath2 = 0;
int yellowpath3 = 0;
int yellowpath4 = 0;

int greenpath1 = 0;
int greenpath2 = 0;
int greenpath3 = 0;
int greenpath4 = 0;

int redpath1 = 0;
int redpath2 = 0;
int redpath3 = 0;
int redpath4 = 0;
int turn = 0;
int stopcheck[4] = {0, 0, 0, 0};
bool gridpass_y = false;
bool gridpass_b = false;
bool gridpass_r = false;
bool gridpass_g = false;

bool home_pass_b[4]={false,false,false,false};
bool home_pass_r[4]={false,false,false,false};
bool home_pass_y[4]={false,false,false,false};
bool home_pass_g[4]={false,false,false,false};

int array_index[57] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56};
int array_bluex[57] = {60, 115, 170, 225, 280, 335, 335, 335, 335, 335, 335, 390, 445, 445, 445, 445, 445, 445, 500, 555, 610, 665, 720, 775, 775, 775, 720, 665, 610, 555, 500, 445, 445, 445, 445, 445, 445, 390, 335, 335, 355, 335, 335, 335, 280, 225, 170, 115, 60, 5, 5, 60, 115, 170, 225, 280, 335};
int array_bluey[57] = {445, 445, 445, 445, 445, 500, 555, 610, 665, 720, 775, 775, 775, 720, 665, 610, 555, 500, 445, 445, 445, 445, 445, 445, 390, 335, 335, 335, 335, 335, 335, 280, 225, 170, 115, 60, 5, 5, 5, 60, 115, 170, 225, 280, 335, 335, 335, 335, 335, 335, 390, 390, 390, 390, 390, 390, 390};

int array_redx[57] = {445, 445, 445, 445, 445, 500, 555, 610, 665, 720, 775, 775, 775, 720, 665, 610, 555, 500, 445, 445, 445, 445, 445, 445, 390, 335, 335, 355, 335, 335, 335, 280, 225, 170, 115, 60, 5, 5, 5, 60, 115, 170, 225, 280, 335, 335, 335, 335, 335, 335, 390, 390, 390, 390, 390, 390, 390};
int array_redy[57] = {720, 665, 610, 555, 500, 445, 445, 445, 445, 445, 445, 390, 335, 335, 335, 335, 335, 335, 280, 225, 170, 115, 60, 5, 5, 5, 60, 115, 170, 225, 280, 335, 335, 335, 335, 335, 335, 390, 445, 445, 445, 445, 445, 445, 500, 555, 610, 665, 720, 775, 775, 720, 665, 610, 555, 500, 445};

int array_yellowx[57] = {720, 665, 610, 555, 500,
						 445, 445, 445, 445, 445, 445,
						 390, 335, 335, 355, 335, 335, 335,
						 280, 225, 170, 115, 60, 5, 5, 5, 60, 115, 170, 225, 280,
						 335, 335, 335, 335, 335, 335,
						 390, 445,
						 445, 445, 445, 445, 445,
						 500, 555, 610, 665, 720, 775,
						 775,
						 720, 665, 610, 555, 500, 445};
int array_yellowy[57] =
	{335, 335, 335, 335, 335,
	 280, 225, 170, 115, 60, 5,
	 5, 5,
	 60, 115, 170, 225, 280,
	 335, 335, 335, 335, 335, 335,
	 390, 445,
	 445, 445, 445, 445, 445,
	 500, 555, 610, 665, 720, 775,
	 775, 755,
	 720, 665, 610, 555, 500,
	 445, 445, 445, 445, 445, 445,
	 390,
	 390, 390, 390, 390, 390, 390};

int array_greenx[57] = {335, 355, 335, 335, 335,
						280, 225, 170, 115, 60, 5, 5, 5, 60, 115, 170, 225, 280,
						335, 335, 335, 335, 335, 335,
						390, 445,
						445, 445, 445, 445, 445,
						500, 555, 610, 665, 720, 775,
						775, 775,
						720, 665, 610, 555, 500,
						445, 445, 445, 445, 445, 445,
						390,
						390, 390, 390, 390, 390, 390};

int array_greeny[57] = {
	60, 115, 170, 225, 280,
	335, 335, 335, 335, 335, 335,
	390, 445,
	445, 445, 445, 445, 445,
	500, 555, 610, 665, 720, 775,
	775, 755,
	720, 665, 610, 555, 500,
	445, 445, 445, 445, 445, 445,
	445, 390,
	335, 335, 335, 335, 335,
	280, 225, 170, 115, 60, 5,
	5,
	5, 5, 5, 5, 5, 5};

float x2 = 100;
int path = 0;
float y2 = 600;
pthread_mutex_t b_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t y_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t r_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;
sem_t sem1, sem2, sem3;
bool space_check = false;
int boolean = 0;

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
 * Main Canvas drawing function.
 * */

void GameDisplay() /**/
{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0 /*Red Component*/, 0,						 //148.0/255/*Green Component*/,
				 0.0 /*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);								 //Update the colors
																 //Fire Gun
																 /*DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Mushroom
	DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	DrawString( 50, 800, "Score=0", colors[MISTY_ROSE]);
	//Spider
	DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)*/
	if (boolean == 0)
	{
		DrawSquare(0, 0, 900, colors[BLACK]);
		DrawString(0, 800, "Press S for Start Game", colors[WHITE]);
		DrawString(0, 700, "Press Q for Quit Game", colors[WHITE]);
		DrawString(0, 600, "Press I for Instructions", colors[WHITE]);
	}
	if (boolean == 2)
	{
		exit(1);
	}

	if (boolean == 3)
	{
		DrawSquare(0, 0, 900, colors[BLACK]);
		DrawString(0, 800, "ALL INSTRUCTIONS.", colors[WHITE]);
		DrawString(0, 700, "=> Please read all instructions carefully.", colors[WHITE]);
		DrawString(0, 600, "=>Enter space bar for dice roll", colors[WHITE]);
		DrawString(0, 500, "=>  Press 1 to move goti 1", colors[WHITE]);
		DrawString(0, 450, "=>  Press 2 to move goti 2", colors[WHITE]);
		DrawString(0, 400, "=>  Press 3 to move goti 3", colors[WHITE]);
		DrawString(0, 350, "=> Press 4 to move goti 4", colors[WHITE]);

		DrawString(0, 250, "=> If you pressed any key from 1 to 4 then you are unable to move any other goti except pressed key.", colors[WHITE]);
		DrawString(0, 200, "=> If you forget to press key from 1 to 4 and you have pressed spacebar then your turn will be skipped.", colors[WHITE]);
		DrawString(0, 150, "=> Please follow all instructions.", colors[WHITE]);

		DrawString(0, 100, "BACK TO MENU", colors[WHITE]);
		DrawString(0, 50, "PRESS B", colors[WHITE]);
	}
	if (boolean == 1)
	{
		///////////////////////////////grid.....................................................................................
		DrawLine(1, 1, 1, 375, 50, colors[DARK_GREEN]);
		DrawLine(1, 375, 1, 750, 50, colors[DARK_BLUE]);
		//right
		DrawLine(830, 1, 830, 375, 50, colors[DARK_KHAKI]);
		DrawLine(830, 375, 830, 750, 50, colors[DARK_RED]);
		//upper
		DrawLine(1, 830, 375, 830, 50, colors[DARK_BLUE]);
		DrawLine(375, 830, 750, 830, 50, colors[DARK_RED]);
		//lower
		DrawLine(1, 1, 375, 1, 50, colors[DARK_GREEN]);
		DrawLine(375, 1, 750, 1, 50, colors[DARK_KHAKI]);

		//GREEN PLAYERS

		//...................................................Path.....................................................................
		//left
		//DrawSquare( 5, 251 ,50,colors[WHITE]);
		//DrawSquare( 5, 302 ,50,colors[WHITE]);
		DrawSquare(5, 335, 55, colors[WHITE]);
		DrawSquare(5, 390, 55, colors[WHITE]);
		DrawSquare(5, 445, 55, colors[WHITE]);

		//right blue

		//DrawSquare( 5, 251 ,50,colors[WHITE]);
		//DrawSquare( 5, 301 ,50,colors[WHITE]);
		//DrawSquare( 5, 351,50,colors[WHITE]);
		//DrawSquare( 5, 401,50,colors[WHITE]);
		//DrawSquare( 6, 451,50,colors[DARK_BLUE]);
		DrawSquare(60, 445, 55, colors[DARK_BLUE]); //stop
		DrawSquare(115, 445, 55, colors[WHITE]);
		DrawSquare(170, 445, 55, colors[WHITE]);
		DrawSquare(225, 445, 55, colors[WHITE]);
		DrawSquare(280, 445, 55, colors[WHITE]); //yeh wala

		DrawSquare(60, 390, 55, colors[DARK_BLUE]);
		DrawSquare(115, 390, 55, colors[DARK_BLUE]);
		DrawSquare(170, 390, 55, colors[DARK_BLUE]);
		DrawSquare(225, 390, 55, colors[DARK_BLUE]);
		DrawSquare(280, 390, 55, colors[DARK_BLUE]);

		DrawSquare(60, 335, 55, colors[WHITE]);
		DrawSquare(115, 335, 55, colors[DARK_BLUE]); //stop
		DrawSquare(170, 335, 55, colors[WHITE]);
		DrawSquare(225, 335, 55, colors[WHITE]);
		DrawSquare(280, 335, 55, colors[WHITE]);

		//green wala side

		//right
		DrawSquare(445, 5, 55, colors[WHITE]);
		DrawSquare(445, 60, 55, colors[WHITE]);
		DrawSquare(445, 115, 55, colors[GREEN]); //stop
		DrawSquare(445, 170, 55, colors[WHITE]);
		DrawSquare(445, 225, 55, colors[WHITE]);
		DrawSquare(445, 280, 55, colors[WHITE]);

		DrawSquare(390, 5, 55, colors[WHITE]);
		DrawSquare(335, 5, 55, colors[WHITE]);

		DrawSquare(390, 60, 55, colors[GREEN]);
		DrawSquare(390, 115, 55, colors[GREEN]);
		DrawSquare(390, 170, 55, colors[GREEN]);
		DrawSquare(390, 225, 55, colors[GREEN]);
		DrawSquare(390, 280, 55, colors[GREEN]);

		//left
		DrawSquare(335, 5, 55, colors[WHITE]);
		DrawSquare(335, 60, 55, colors[GREEN]); //stop
		DrawSquare(335, 115, 55, colors[WHITE]);
		DrawSquare(335, 170, 55, colors[WHITE]);
		DrawSquare(335, 225, 55, colors[WHITE]);
		DrawSquare(335, 280, 55, colors[WHITE]);

		//red wala
		//DrawSquare(335,55,colors[WHITE]);
		DrawSquare(335, 500, 55, colors[WHITE]);
		DrawSquare(335, 555, 55, colors[WHITE]);
		DrawSquare(335, 610, 55, colors[WHITE]);
		DrawSquare(335, 665, 55, colors[RED]); // stop
		DrawSquare(335, 720, 55, colors[WHITE]);
		DrawSquare(335, 775, 55, colors[WHITE]);
		DrawSquare(390, 775, 55, colors[WHITE]);
		DrawSquare(445, 775, 55, colors[WHITE]);

		DrawSquare(390, 500, 55, colors[RED]);
		DrawSquare(390, 555, 55, colors[RED]);
		DrawSquare(390, 610, 55, colors[RED]);
		DrawSquare(390, 665, 55, colors[RED]);
		DrawSquare(390, 720, 55, colors[RED]);

		DrawSquare(445, 500, 55, colors[WHITE]);
		DrawSquare(445, 555, 55, colors[WHITE]);
		DrawSquare(445, 610, 55, colors[WHITE]);
		DrawSquare(445, 665, 55, colors[WHITE]);
		DrawSquare(445, 720, 55, colors[RED]); //stop
		DrawSquare(390, 775, 55, colors[RED]);

		//yellow
		DrawSquare(500, 445, 55, colors[WHITE]);
		DrawSquare(555, 445, 55, colors[WHITE]);
		DrawSquare(610, 445, 55, colors[WHITE]);
		DrawSquare(665, 445, 55, colors[YELLOW]); //stop
		DrawSquare(720, 445, 55, colors[WHITE]);
		DrawSquare(775, 445, 55, colors[WHITE]);
		DrawSquare(775, 390, 55, colors[WHITE]);
		DrawSquare(775, 335, 55, colors[WHITE]);

		DrawSquare(500, 390, 55, colors[YELLOW]);
		DrawSquare(555, 390, 55, colors[YELLOW]);
		DrawSquare(610, 390, 55, colors[YELLOW]);
		DrawSquare(665, 390, 55, colors[YELLOW]);
		DrawSquare(720, 390, 55, colors[YELLOW]);

		DrawSquare(500, 335, 55, colors[WHITE]);
		DrawSquare(555, 335, 55, colors[WHITE]);
		DrawSquare(610, 335, 55, colors[WHITE]);
		DrawSquare(665, 335, 55, colors[WHITE]);
		DrawSquare(720, 335, 55, colors[YELLOW]); //stop

		DrawSquare(850, 300, 150, colors[WHITE]);
		DrawSquare(865, 315, 120, colors[BLACK]);
		if (value == 1)
		{
			DrawCircle(925, 380, 5.0, colors[WHITE]);
		}
		if (value == 2)
		{
			DrawCircle(885, 340, 5.0, colors[WHITE]);
			DrawCircle(965, 420, 5.0, colors[WHITE]);
		}
		if (value == 3)
		{

			DrawCircle(885, 340, 5.0, colors[WHITE]);
			DrawCircle(925, 380, 5.0, colors[WHITE]);
			DrawCircle(965, 420, 5.0, colors[WHITE]);
		}
		if (value == 4)
		{
			DrawCircle(885, 420, 5.0, colors[WHITE]);
			DrawCircle(965, 420, 5.0, colors[WHITE]);
			DrawCircle(885, 340, 5.0, colors[WHITE]);
			DrawCircle(965, 340, 5.0, colors[WHITE]);
		}
		if (value == 5)
		{
                DrawCircle(885, 340, 5.0, colors[WHITE]);
                 DrawCircle(965, 340, 5.0, colors[WHITE]);
                 DrawCircle(925, 380, 5.0, colors[WHITE]);
                 DrawCircle(885, 420, 5.0, colors[WHITE]);
                  DrawCircle(965, 420, 5.0, colors[WHITE]);

		}
		if (value == 6)
		{
               DrawCircle(885, 340, 5.0, colors[WHITE]);
               DrawCircle(885, 380, 5.0, colors[WHITE]);
               DrawCircle(885, 420, 5.0, colors[WHITE]);
               DrawCircle(965, 340, 5.0, colors[WHITE]);
               DrawCircle(965, 380, 5.0, colors[WHITE]);
                DrawCircle(965, 420, 5.0, colors[WHITE]);
		}

		/* DrawSquare( 850,300,150,colors[WHITE]);
       DrawSquare( 865,315,120,colors[BLACK]);
       DrawCircle(885, 340, 5.0, colors[WHITE]);
       DrawCircle(925, 340, 5.0, colors[WHITE]);
       DrawCircle(965, 340, 5.0, colors[WHITE]);
       
       
       DrawCircle(885, 380, 5.0, colors[WHITE]);
       DrawCircle(925, 380, 5.0, colors[WHITE]);
       DrawCircle(965, 380, 5.0, colors[WHITE]);
       
       DrawCircle(885, 420, 5.0, colors[WHITE]);
       DrawCircle(925, 420, 5.0, colors[WHITE]);
       DrawCircle(965, 420, 5.0, colors[WHITE]);*/

		//DrawTriangle( 445, 445 , 445, 500 , 472 , 472, colors[GREEN] );
		//DrawTriangle( 5, 5,5, 50 , 25 , 25, colors[WHITE] );
		DrawTriangle(335, 335, 335, 500, 417, 417, colors[BLUE]);
		DrawTriangle(500, 335, 500, 500, 417, 417, colors[YELLOW]);
		DrawTriangle(500, 500, 335, 500, 417, 417, colors[RED]);
		DrawTriangle(335, 335, 500, 335, 417, 417, colors[GREEN]);
		//DrawTriangle( 335, 335,335, 500 , 417, 417, colors[BLUE] );
		//DrawTriangle( 335, 335,335, 500 , 417, 417, colors[BLUE] );
		//draw players///

		DrawString(100, 600, 30, 50, "1", colors[BLACK]);
		DrawSquare(5, 5, 330, colors[GREEN]);
		DrawSquare(55, 55, 200, colors[WHITE]);

		DrawSquare(green_px[0], green_py[0], 30, colors[GREEN]);
		DrawString(green_px[0] + 5, green_py[0] + 2, "1", colors[DARK_RED]);

		DrawSquare(green_px[1], green_py[1], 30, colors[GREEN]);
		DrawString(green_px[1] + 5, green_py[1] + 2, "2", colors[DARK_RED]);

		DrawSquare(green_px[2], green_py[2], 30, colors[GREEN]);
		DrawString(green_px[2] + 5, green_py[2] + 2, "3", colors[DARK_RED]);

		DrawSquare(green_px[3], green_py[3], 30, colors[GREEN]);
		DrawString(green_px[3] + 5, green_py[3] + 2, "4", colors[DARK_RED]);
		//DrawSquare( 80, 80 ,50,colors[GREEN]);
		//DrawSquare( 120,80 ,50,colors[GREEN]);
		//BLUE player
		DrawSquare(5, 500, 330, colors[BLUE]);
		DrawSquare(55, 555, 200, colors[WHITE]);
		DrawSquare(blue_px[0], blue_py[0], 30, colors[BLUE]);
		DrawString(blue_px[0] + 5, blue_py[0], "1", colors[DARK_RED]);

		DrawSquare(blue_px[1], blue_py[1], 30, colors[BLUE]);
		DrawString(blue_px[1] + 5, blue_py[1], "2", colors[DARK_RED]);

		DrawSquare(blue_px[2], blue_py[2], 30, colors[BLUE]);
		DrawString(blue_px[2] + 5, blue_py[2], "3", colors[DARK_RED]);

		DrawSquare(blue_px[3], blue_py[3], 30, colors[BLUE]);
		DrawString(blue_px[3] + 5, blue_py[3] + 2, "4", colors[DARK_RED]);
		//DrawSquare( 5, 500 ,330,colors[BLUE]);
		//DrawSquare( 5, 500 ,330,colors[BLUE]);
		//DrawSquare( 5, 500 ,330,colors[BLUE]);

		//RED PLAYER
		DrawSquare(500, 500, 330, colors[RED]);
		DrawSquare(555, 555, 200, colors[WHITE]);
		//cout<< red_p1_1x<<","<< red_p1_1y<<endl;
		DrawSquare(red_px[0], red_py[0], 30, colors[DARK_RED]);
		DrawString(red_px[0] + 5, red_py[0] + 2, "1", colors[BLACK]);

		DrawSquare(red_px[1], red_py[1], 30, colors[DARK_RED]);
		DrawString(red_px[1] + 5, red_py[1] + 2, "2", colors[BLACK]);

		DrawSquare(red_px[2], red_py[2], 30, colors[DARK_RED]);
		DrawString(red_px[2] + 5, red_py[2] + 2, "3", colors[BLACK]);

		DrawSquare(red_px[3], red_py[3], 30, colors[DARK_RED]);
		DrawString(red_px[3] + 5, red_py[3] + 2, "4", colors[BLACK]);
		//YELLOW PLAYER
		DrawSquare(500, 5, 330, colors[YELLOW]);
		DrawSquare(555, 55, 200, colors[WHITE]);
		DrawSquare(yellow_px[0], yellow_py[0], 30, colors[YELLOW]);
		DrawString(yellow_px[0] + 5, yellow_py[0] + 2, "1", colors[DARK_RED]);

		DrawSquare(yellow_px[1], yellow_py[1], 30, colors[YELLOW]);
		DrawString(yellow_px[1] + 5, yellow_py[1] + 2, "2", colors[DARK_RED]);

		DrawSquare(yellow_px[2], yellow_py[2], 30, colors[YELLOW]);
		DrawString(yellow_px[2] + 5, yellow_py[2] + 2, "3", colors[DARK_RED]);

		DrawSquare(yellow_px[3], yellow_py[3], 30, colors[YELLOW]);
		DrawString(yellow_px[3] + 5, yellow_py[3] + 2, "4", colors[DARK_RED]);
		if (turn == 1)
		{
			DrawString(850, 800, "Turn of player => ", colors[DARK_RED]);
			DrawString(850, 700, "Red Player", colors[DARK_RED]);
		}
		if (turn == 2)
		{
			DrawString(850, 800, "Turn of player => ", colors[DARK_RED]);
			DrawString(850, 700, "Blue Player", colors[DARK_RED]);
		}
		if (turn == 3)
		{
			DrawString(850, 800, "Turn of player => ", colors[DARK_RED]);
			DrawString(850, 700, "Green Player", colors[DARK_RED]);
		}
		if (turn == 4)
		{
			DrawString(850, 800, "Turn of player => ", colors[DARK_RED]);
			DrawString(850, 700, "Yellow Player", colors[DARK_RED]);
		}

		if (space_check == true)
		{
		
                        sem_init(&sem, 0, 1);
	                sem_init(&sem1, 0, 0);
	                sem_init(&sem2, 0, 0);
	                sem_init(&sem3, 0, 0);
			pthread_create(&tid, NULL, main_thread, NULL);
			
			turn = 0;
		}
	}

	//DrawTriangle( 900, 600 , 900, 900 , 750 , 750, colors[RED] );
	//DrawTriangle( 900, 900 , 600, 900 , 750 , 750, colors[BLUE] );
	//DrawTriangle( 600, 600 , 900, 600 , 750 , 750, colors[GREEN] );
	//DrawTriangle( 600, 600 , 600, 900 , 750 , 750, colors[YELLOW] );
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//left

	//DrawLine( 750 , 1 ,  750 , 850 , 50 , colors[MISTY_ROSE] );
	/*DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );
	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );*/

	/*DrawCircle(50,670,10,colors[R ED]);
	DrawCircle(70,670,10,colors[RED]);
	DrawCircle(90,670,10,colors[RED]);
	DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
	DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);	
	DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
	DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
	DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);*/

	glutSwapBuffers(); // do not modify this line..
}
void blue_collision()
{
	for (int i = 0; i < 4; i++)
	{
		if (blue_px[i] == red_px[i] && blue_py[i] == red_py[i])
		{
			red_px[i] = temp_red_px[i];
			red_py[i] = temp_red_py[i];
			gridpass_b = true;
			home_pass_b[i]=false;

			break;
		}
		if (blue_px[i] == yellow_px[i] && blue_py[i] == yellow_py[i])
		{
			yellow_px[i] = temp_yellow_px[i];
			yellow_py[i] = temp_yellow_py[i];
			gridpass_b = true;
			home_pass_b[i]=false;

			break;
		}
		if (blue_px[i] == green_px[i] && blue_py[i] == green_py[i])
		{
			green_px[i] = temp_green_px[i];
			green_py[i] = temp_green_py[i];
			gridpass_b = true;
			home_pass_b[i]=false;

			break;
		}
	}
}

void red_collision()
{
	for (int i = 0; i < 4; i++)
	{
		if (blue_px[i] == red_px[i] && blue_py[i] == red_py[i])
		{
			blue_px[i] = temp_blue_px[i];
			blue_py[i] = temp_blue_py[i];
			gridpass_r = true;
			home_pass_r[i]=false;

			break;
		}
		if (red_px[i] == yellow_px[i] && red_py[i] == yellow_py[i])
		{
			yellow_px[i] = temp_yellow_px[i];
			yellow_py[i] = temp_yellow_py[i];
			gridpass_r = true;
			home_pass_r[i]=false;

			break;
		}
		if (red_px[i] == green_px[i] && red_py[i] == green_py[i])
		{
			green_px[i] = temp_green_px[i];
			green_py[i] = temp_green_py[i];
			gridpass_r = true;
			home_pass_r[i]=false;

			break;
		}
	}
}

void green_collision()
{
	for (int i = 0; i < 4; i++)
	{
		if (blue_px[i] == green_px[i] && blue_py[i] == green_py[i])
		{
			blue_px[i] = temp_blue_px[i];
			blue_py[i] = temp_blue_py[i];
			gridpass_g = true;
			home_pass_g[i]=false;

			break;
		}
		if (green_px[i] == yellow_px[i] && green_py[i] == yellow_py[i])
		{
			yellow_px[i] = temp_yellow_px[i];
			yellow_py[i] = temp_yellow_py[i];
			gridpass_g = true;
			home_pass_g[i]=false;

			break;
		}
		if (green_px[i] == red_px[i] && green_py[i] == red_py[i])
		{
			red_px[i] = temp_red_px[i];
			red_py[i] = temp_red_py[i];
			gridpass_g = true;
			home_pass_g[i]=false;

			break;
		}
	}
}

void yellow_collision()
{
	for (int i = 0; i < 4; i++)
	{
		if (blue_px[i] == yellow_px[i] && blue_py[i] == yellow_py[i])
		{
			blue_px[i] = temp_blue_px[i];
			blue_py[i] = temp_blue_py[i];
			gridpass_g = true;
			home_pass_y[i]=false;

			break;
		}
		if (green_px[i] == yellow_px[i] && green_py[i] == yellow_py[i])
		{
			yellow_px[i] = temp_yellow_px[i];
			yellow_py[i] = temp_yellow_py[i];
			gridpass_g = true;
			home_pass_y[i]=false;

			break;
		}
		if (yellow_px[i] == red_px[i] && yellow_py[i] == red_py[i])
		{
			red_px[i] = temp_red_px[i];
			red_py[i] = temp_red_py[i];
			gridpass_y = true;
			home_pass_y[i]=false;

			break;
		}
	}
}

int diceroll()
{
	return (rand()%6+1);
}

int check_save_stop(int x, int y)
{
	if (x == 60 && y == 445)
	{
		return 1;
	}
	else if (x == 115 && y == 335)
	{
		return 1;
	}
	else if (x == 445 && y == 115)
	{
		return 1;
	}
	else if (x == 335 && y == 60)
	{
		return 1;
	}
	else if (x == 335 && y == 665)
	{
		return 1;
	}
	else if (x == 445 && y == 720)
	{
		return 1;
	}
	else if (x == 665 && y == 445)
	{
		return 1;
	}
	else if (x == 720 && y == 335)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void MoveRed(int which_player, int value)
{

	int y = 0;
	int x = 0;
	
	//  cout<<x<<",s"<<y<<endl;
	if (which_player == 1)
	{
	        if(home_pass_r[0]==false)
	        {
	         if(value==6)
	         {
	           home_pass_r[0]=true;
	           cout<<"R value:"<<value;
	        x = array_redx[array_index[0]];
		y = array_redy[array_index[0]];
		red_px[0] = x + 10;
		red_py[0] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		redpath1 += value;
		x = array_redx[array_index[redpath1]];
		y = array_redy[array_index[redpath1]];
		red_px[0] = x + 10;
		red_py[0] = y + 10;
		}

		// cout<<"Ameen Gandu";
	}
	if (which_player == 2)
	{
	        if(home_pass_r[1]==false)
	        {
	         if(value==6)
	         {
	           home_pass_r[1]=true;
	           cout<<"R value:"<<value;
	        x = array_redx[array_index[0]];
		y = array_redy[array_index[0]];
		red_px[1] = x + 10;
		red_py[1] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		redpath2 += value;
		x = array_redx[array_index[redpath2]];
		y = array_redy[array_index[redpath2]];
		red_px[1] = x + 10;
		red_py[1] = y + 10;
		}

		//glutPostRedisplay();
	}
	if (which_player == 3)
	{
	      // cout<<"3 key pressed for first time";
	        if(home_pass_r[2]==false)
	        {
	         if(value==6)
	         {
	         home_pass_r[2]=true;
	         cout<<"R value:"<<value;
	        x = array_redx[array_index[0]];
		y = array_redy[array_index[0]];
		red_px[2] = x + 10;
		red_py[2] = y + 10;
                
	           
	           
	         }
	        }
	        else
	        {
		redpath3 += value;
		x = array_redx[array_index[redpath3]];
		y = array_redy[array_index[redpath3]];
		red_px[2] = x + 10;
		red_py[2] = y + 10;
		}
		//glutPostRedisplay();
	}
	if (which_player == 4)
	{
	        if(home_pass_r[3]==false)
	        {
	         if(value==6)
	         {
	        home_pass_r[3]=true;
	        cout<<"R value:"<<value;
	        x = array_redx[array_index[0]];
		y = array_redy[array_index[0]];
		red_px[3] = x + 10;
		red_py[3] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		redpath4 += value;
		x = array_redx[array_index[redpath4]];
		y = array_redy[array_index[redpath4]];
		red_px[3] = x + 10;
		red_py[3] = y + 10;
		}
		//glutPostRedisplay();
	}
	int safe_stop = check_save_stop(x, y);
	if (safe_stop == 0)
	{
		red_collision();
	}
}

void MoveBlue(int which_player, int value)
{
	int x = 0;
	int y = 0;
	//cout<<x<<",sqwqe"<<y;
        cout<<"Blue";
	if (which_player == 1)
	{
	        if(home_pass_b[0]==false)
	        {
	         if(value==6)
	         {
	           home_pass_b[0]=true;
	           cout<<"B value:"<<value;
	        x = array_bluex[array_index[0]];
		y = array_bluey[array_index[0]];
		blue_px[0] = x + 10;
		blue_py[0] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		bluepath1 += value;
		x = array_bluex[array_index[bluepath1]];
		y = array_bluey[array_index[bluepath1]];
		blue_px[0] = x + 10;
		blue_py[0] = y + 10;
		}

		// cout<<"Ameen Gandu";
	}
	if (which_player == 2)
	{
	        if(home_pass_b[1]==false)
	        {
	         if(value==6)
	         {
	           home_pass_b[1]=true;
	           cout<<"B value:"<<value;
	        x = array_bluex[array_index[0]];
		y = array_bluey[array_index[0]];
		blue_px[1] = x + 10;
		blue_py[1] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		bluepath2 += value;
		cout<<"B value:"<<value;
		x = array_bluex[array_index[bluepath2]];
		y = array_bluey[array_index[bluepath2]];
		blue_px[1] = x + 10;
		blue_py[1] = y + 10;
		}

		//glutPostRedisplay();
	}
	if (which_player == 3)
	{
	       cout<<"3 key pressed for first time";
	        if(home_pass_b[2]==false)
	        {
	         if(value==6)
	         {
	         home_pass_b[2]=true;
	         cout<<"B value:"<<value;
	        x = array_bluex[array_index[0]];
		y = array_bluey[array_index[0]];
		blue_px[2] = x + 10;
		blue_py[2] = y + 10;
                
	           
	           
	         }
	        }
	        else
	        {
		bluepath3 += value;
		x = array_bluex[array_index[bluepath3]];
		y = array_bluey[array_index[bluepath3]];
		blue_px[2] = x + 10;
		blue_py[2] = y + 10;
		}
		//glutPostRedisplay();
	}
	if (which_player == 4)
	{
	        if(home_pass_b[3]==false)
	        {
	         if(value==6)
	         {
	        home_pass_b[3]=true;
	        x = array_bluex[array_index[0]];
		y = array_bluey[array_index[0]];
		blue_px[3] = x + 10;
		blue_py[3] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		bluepath4 += value;
		x = array_bluex[array_index[bluepath4]];
		y = array_bluey[array_index[bluepath4]];
		blue_px[3] = x + 10;
		blue_py[3] = y + 10;
		}
		//glutPostRedisplay();
	}
	
	int safe_stop = check_save_stop(x, y);
	if (safe_stop == 0)
	{
		blue_collision();
	}
}
void MoveYellow(int which_player, int value)
{
	int x = 0;
	int y = 0;

	// cout<<x<<",s"<<y<<endl;
	if (which_player == 1)
	{
	        if(home_pass_y[0]==false)
	        {
	         if(value==6)
	         {
	           home_pass_y[0]=true;
	           cout<<"Y value:"<<value;
	        x = array_yellowx[array_index[0]];
		y = array_yellowy[array_index[0]];
		yellow_px[0] = x + 10;
		yellow_py[0] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		yellowpath1 += value;
		x = array_yellowx[array_index[yellowpath1]];
		y = array_yellowy[array_index[yellowpath1]];
		yellow_px[0] = x + 10;
		yellow_py[0] = y + 10;
		}

		// cout<<"Ameen Gandu";
	}
	if (which_player == 2)
	{
	        if(home_pass_y[1]==false)
	        {
	         if(value==6)
	         {
	         cout<<"Y value:"<<value;
	           home_pass_y[1]=true;
	        x = array_yellowx[array_index[0]];
		y = array_yellowy[array_index[0]];
		yellow_px[1] = x + 10;
		yellow_py[1] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		yellowpath2 += value;
		x = array_yellowx[array_index[yellowpath2]];
		y = array_yellowy[array_index[yellowpath2]];
		yellow_px[1] = x + 10;
		yellow_py[1] = y + 10;
		}

		//glutPostRedisplay();
	}
	if (which_player == 3)
	{
	      // cout<<"3 key pressed for first time";
	        if(home_pass_y[2]==false)
	        {
	         if(value==6)
	         {
	         home_pass_y[2]=true;
	         cout<<"Y value:"<<value;
	        x = array_yellowx[array_index[0]];
		y = array_yellowy[array_index[0]];
		yellow_px[2] = x + 10;
		yellow_py[2] = y + 10;
                
	           
	           
	         }
	        }
	        else
	        {
		yellowpath3 += value;
		x = array_yellowx[array_index[yellowpath3]];
		y = array_yellowy[array_index[yellowpath3]];
		yellow_px[2] = x + 10;
		yellow_py[2] = y + 10;
		}
		//glutPostRedisplay();
	}
	if (which_player == 4)
	{
	        if(home_pass_y[3]==false)
	        {
	         if(value==6)
	         {
	        home_pass_y[3]=true;
	        cout<<"Y value:"<<value;
	        x = array_yellowx[array_index[0]];
		y = array_yellowy[array_index[0]];
		yellow_px[3] = x + 10;
		yellow_py[3] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		yellowpath4 += value;
		x = array_yellowx[array_index[yellowpath4]];
		y = array_yellowy[array_index[yellowpath4]];
		yellow_px[3] = x + 10;
		yellow_py[3] = y + 10;
		}
		//glutPostRedisplay();
	}
	int safe_stop = check_save_stop(x, y);
	if (safe_stop == 0)
	{
		yellow_collision();
	}
}
void MoveGreen(int which_player, int value)
{

	int x = 0;
	int y = 0;
	if (which_player == 1)
	{
	        if(home_pass_g[0]==false)
	        {
	         if(value==6)
	         {
	           home_pass_g[0]=true;
	           cout<<"G value:"<<value;
	        x = array_greenx[array_index[0]];
		y = array_greeny[array_index[0]];
		green_px[0] = x + 10;
		green_py[0] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		greenpath1 += value;
		x = array_greenx[array_index[greenpath1]];
		y = array_greeny[array_index[greenpath1]];
		green_px[0] = x + 10;
		green_py[0] = y + 10;
		}

		// cout<<"Ameen Gandu";
	}
	if (which_player == 2)
	{
	        if(home_pass_g[1]==false)
	        {
	         if(value==6)
	         {
	           home_pass_g[1]=true;
	           cout<<"G value:"<<value;
	        x = array_greenx[array_index[0]];
		y = array_greeny[array_index[0]];
		green_px[1] = x + 10;
		green_py[1] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		greenpath2 += value;
		x = array_greenx[array_index[greenpath2]];
		y = array_greeny[array_index[greenpath2]];
		green_px[1] = x + 10;
		green_py[1] = y + 10;
		}

		//glutPostRedisplay();
	}
	if (which_player == 3)
	{
	      // cout<<"3 key pressed for first time";
	        if(home_pass_g[2]==false)
	        {
	         if(value==6)
	         {
	         home_pass_g[2]=true;
	         cout<<"G value:"<<value;
	        x = array_greenx[array_index[0]];
		y = array_greeny[array_index[0]];
		green_px[2] = x + 10;
		green_py[2] = y + 10;
                
	           
	           
	         }
	        }
	        else
	        {
		greenpath3 += value;
		x = array_greenx[array_index[greenpath3]];
		y = array_greeny[array_index[greenpath3]];
		green_px[2] = x + 10;
		green_py[2] = y + 10;
		}
		//glutPostRedisplay();
	}
	if (which_player == 4)
	{
	        if(home_pass_g[3]==false)
	        {
	         if(value==6)
	         {
	        home_pass_g[3]=true;
	        cout<<"G value:"<<value;
	        x = array_greenx[array_index[0]];
		y = array_greeny[array_index[0]];
		green_px[3] = x + 10;
		green_py[3] = y + 10;

	           
	           
	         }
	        }
	        else
	        {
		greenpath4 += value;
		x = array_greenx[array_index[greenpath4]];
		y = array_greeny[array_index[greenpath4]];
		green_px[3] = x + 10;
		green_py[3] = y + 10;
		}
		//glutPostRedisplay();
	}
	int safe_stop = check_save_stop(x, y);
	if (safe_stop == 0)
	{
		green_collision();
	}
}

void *go_red(void *p)
{

	sem_wait(&sem);
	turn++;
	if(check_redwin()==1)
	{
	int score[3]={0,0,0};
	value=0;
	r_key = false;
	r_key_check=0;
	value = diceroll();
	if(value==6)
	{
	  score[0]=value;
	  value=diceroll();
	  if(value==6)
	  {
	   score[1]=value;
	   value=diceroll();
	   
	   if(value==6)
	   {
	    cout<<"Red Turn discarded";
	   }
	   else{
	     score[2]=value;
	    for(int i=0; i<3; i++)
	    {
	                     	
	                     	while (r_key == false)
	                        {
		                //pthread_mutex_lock(&b_lock);
		                // sem_wait(&sem);
		                glutKeyboardFunc(PrintableKeys);
		                //sem_post(&sem);
		                // pthread_mutex_unlock(&b_lock);
                        	}
	                                        r_key = false;
	                                        if (r_key_check > 0)
	                                        {
                                                       
                                                       // cout<<"REd ::" <<r_key_check;
		                                        MoveRed(r_key_check, score[i]);
	                                        }
	   // sleep(1);
	    }
	    
	   
	   }
	  }
	  else
	  {
	  score[1]=value;
	   for(int i=0; i<2; i++)
	    {
	                     	
	                     	while (r_key == false)
	                        {
		                //pthread_mutex_lock(&b_lock);
		                // sem_wait(&sem);
		                glutKeyboardFunc(PrintableKeys);
		                //sem_post(&sem);
		                // pthread_mutex_unlock(&b_lock);
                        	}
	                                        r_key = false;
	                                        if (r_key_check > 0)
	                                        {


		                                        MoveRed(r_key_check, score[i]);
	                                        }
	    }
	  
	  
	  }
	}
	else{
	r_key = false;
	while (r_key == false)
	{
		//pthread_mutex_lock(&b_lock);
		// sem_wait(&sem);
		glutKeyboardFunc(PrintableKeys);
		//sem_post(&sem);
		// pthread_mutex_unlock(&b_lock);
	}
	r_key = false;
	if (r_key_check > 0)
	{

		MoveRed(r_key_check, value);
	}
	//sleep(1);
        }
        }
	sem_post(&sem1);
	//cout << "red ends";
	pthread_exit(NULL);
}

void *go_green(void *p)
{
	sem_wait(&sem2);
	if(check_greenwin()==1)
	{
	g_key = false;
	g_key_check=0;
	int score[3]={0,0,0};
	value=0;
	turn++;
	value = diceroll();
	if(value==6)
	{
	   score[0]=value;
	   value=diceroll();
	  if(value==6)
	  {
	   score[1]=value;
	   value=diceroll();
	   
	   if(value==6)
	   {
	    cout<<"Green Turn discarded";
	   }
	   else{
	     score[2]=value;
	    for(int i=0; i<3; i++)
	    {
	                     	
	                     	while (g_key == false)
	                        {
		                //pthread_mutex_lock(&b_lock);
		                // sem_wait(&sem);
		                glutKeyboardFunc(PrintableKeys);
		                //sem_post(&sem);
		                // pthread_mutex_unlock(&b_lock);
                        	}
	                                        g_key = false;
	                                        if (g_key_check > 0)
	                                        {
                                                       
                                                        
		                                        MoveGreen(g_key_check, score[i]);
	                                        }
	   // sleep(1);
	    }
	    
	   
	   }
	  }
	  else
	  {
	   score[1]=value;
	   for(int i=0; i<2; i++)
	    {
	                     	
	                     	while (g_key == false)
	                        {
		                //pthread_mutex_lock(&b_lock);
		                // sem_wait(&sem);
		                glutKeyboardFunc(PrintableKeys);
		                //sem_post(&sem);
		                // pthread_mutex_unlock(&b_lock);
                        	}
	                                        g_key = false;
	                                        if (g_key_check > 0)
	                                        {


		                                       MoveGreen(g_key_check, score[i]);
	                                        }
	    }
	  
	  
	  }
	}
	else{
	g_key = false;
	while (g_key == false)
	{
		//pthread_mutex_lock(&b_lock);
		// sem_wait(&sem);
		glutKeyboardFunc(PrintableKeys);
		//sem_post(&sem);
		// pthread_mutex_unlock(&b_lock);
	}
	g_key = false;
	if (g_key_check > 0)
	{

		MoveGreen(g_key_check, value);
	}
	//sleep(1);
        }
       }
	sem_post(&sem3);
	pthread_exit(NULL);
}

void *go_blue(void *p)
{

	//pthread_mutex_lock(&r_lock);
if(check_bluewin()==1)
{
	sem_wait(&sem1);
	b_key = false;
        int score[3]={0,0,0};
	value=0;
	turn++;
	value = diceroll();
	if(value==6)
	{
	  score[0]=6;
	  value=diceroll();
	  
	  if(value==6)
	  {
           score[1]=value;
	   value=diceroll();
	   
	   if(value==6)
	   {
	    cout<<"Blue Turn discarded";
	   }
	   else{
	     score[2]=value;
	    for(int i=0; i<3; i++)
	    {
	                     	
	                     	while (b_key == false)
	                        {
		                //pthread_mutex_lock(&b_lock);
		                // sem_wait(&sem);
		                glutKeyboardFunc(PrintableKeys);
		                //sem_post(&sem);
		                // pthread_mutex_unlock(&b_lock);
                        	}
	                                        b_key = false;
	                                        if (b_key_check > 0)
	                                        {
                                                       
                                                        cout<<"Blue--"<<b_key_check<<endl;
		                                        MoveBlue(b_key_check, score[i]);
	                                        }
	   // sleep(1);
	    }
	    
	   
	   }
	  }
	  else
	  {
	   score[1]=value;
	   for(int i=0; i<2; i++)
	    {
	                     	
	                     	while (b_key == false)
	                        {
		                //pthread_mutex_lock(&b_lock);
		                // sem_wait(&sem);
		                glutKeyboardFunc(PrintableKeys);
		                //sem_post(&sem);
		                // pthread_mutex_unlock(&b_lock);
                        	}
	                                        b_key = false;
	                                        if (b_key_check > 0)
	                                        {


		                                        MoveBlue(b_key_check, score[i]);
	                                        }
	    }
	  
	  
	  }
	}
	else{
	
	b_key = false;
	while (b_key == false)
	{
		//pthread_mutex_lock(&b_lock);
		// sem_wait(&sem);
		glutKeyboardFunc(PrintableKeys);
		//sem_post(&sem);
		// pthread_mutex_unlock(&b_lock);
	}
	b_key = false;
	if (b_key_check > 0)
	{

		MoveBlue(b_key_check, value);
	}
	//sleep(1);
        }
	//glutPostRedisplay();
	//pthread_mutex_unlock(&b_lock);
	
}
	sem_post(&sem2);
	pthread_exit(NULL);
	//  }
	//else{
	//}      //cout<<"locked";
	// }
}

void *go_yellow(void *p)
{
	sem_wait(&sem3);
if(check_yellowwin()==1)
{
	int score[3]={0,0,0};
	value=0;
        y_key = false;
        y_key_check=0;
	turn++;
	value = diceroll();
	if(value==6)
	{
	  score[0]=value;
	  value=diceroll();
	  if(value==6)
	  {
	   score[1]=value;
	   value=diceroll();
	   //score[2]=value;
	   if(value==6)
	   {
	    cout<<"yellow Turn discarded";
	   }
	   else{
	     score[2]=value;
	    for(int i=0; i<3; i++)
	    {
	                     	
	                     	while (y_key == false)
	                        {
		                //pthread_mutex_lock(&b_lock);
		                // sem_wait(&sem);
		                glutKeyboardFunc(PrintableKeys);
		                //sem_post(&sem);
		                // pthread_mutex_unlock(&b_lock);
                        	}
	                                        y_key = false;
	                                        if (y_key_check > 0)
	                                        {
                                                       
                                                        
		                                        MoveYellow(y_key_check, score[i]);
	                                        }
	   // sleep(1);
	    }
	    
	   
	   }
	  }
	  else
	  {
	   score[1]=value;
	   for(int i=0; i<2; i++)
	    {
	                     	
	                     	while (y_key == false)
	                        {
		                //pthread_mutex_lock(&b_lock);
		                // sem_wait(&sem);
		                glutKeyboardFunc(PrintableKeys);
		                //sem_post(&sem);
		                // pthread_mutex_unlock(&b_lock);
                        	}
	                                        y_key = false;
	                                        if (y_key_check > 0)
	                                        {


		                                        MoveYellow(y_key_check, score[i]);
	                                        }
	    }
	  
	  
	  }
	}
	else{
	y_key = false;
	while (y_key == false)
	{
		//pthread_mutex_lock(&b_lock);
		// sem_wait(&sem);
		glutKeyboardFunc(PrintableKeys);
		//sem_post(&sem);
		// pthread_mutex_unlock(&b_lock);
	}
	y_key = false;
	if (y_key_check > 0)
	{

		MoveYellow(y_key_check, value);
	}
	//sleep(1);
        }
 }
	//glutPostRedisplay();
	sem_post(&sem);
	pthread_exit(NULL);
}
int check_redwin()
{
        if(redpath1<57 && redpath2<57 && redpath3<57 && redpath4<57)
        {
             return 1;
        }
        else
        {
        return 0;
        }

}
int check_bluewin()
{
        if(bluepath1<57 && bluepath2<57 && bluepath3<57 && bluepath4<57)
        {
             return 1;
        }
        else
        {
        return 0;
        }

}
int check_greenwin()
{
        if(greenpath1<57 && greenpath2<57 && greenpath3<57 && greenpath4<57)
        {
             return 1;
        }
        else
        {
        return 0;
        }

}
int check_yellowwin()
{
        if(yellowpath1<57 && yellowpath2<57 && yellowpath3<57 && yellowpath4<57)
        {
             return 1;
        }
        else
        {
        return 0;
        }

}

void *main_thread(void *ptr)
{


	//pthread_mutex_unlock(&lock1);
	//sem_wait(&sem);

	pthread_create(&tid1, NULL, go_red, NULL);

	//pthread_join(tid1,NULL);
	//sem_post(&sem);
	//sem_wait(&sem);
	pthread_create(&tid2, NULL, go_blue, NULL);
	//pthread_join(tid2,NULL);

	pthread_create(&tid3, NULL, go_green, NULL);
	//pthread_join(tid3,NULL);

	pthread_create(&tid4, NULL, go_yellow, NULL);
	//pthread_join(tid4,NULL);
        space_check = false;
	sem_destroy(&sem);

	cout << "loop ends";
	pthread_exit(NULL);
}
/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
	{
		// what to do when left key is pressed...
	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
	{
	}
	else if (key == GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
	{
	}

	else if (key == GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
	{
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();
}


/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m)
{

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(500.0, Timer, 0);
	glutPostRedisplay();
}
/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y)
{
	if (key == 27 /* Escape key ASCII*/)
	{
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
	{
		boolean = 0;
	}

	if (key == '1' && b_key == false)
	{
		b_key_check = 1;
		b_key = true;
	}
	if (key == '2' && b_key == false)
	{
		b_key_check = 2;
		b_key = true;
	}
	if (key == '3' && b_key == false)
	{
		b_key_check = 3;
		b_key = true;
	}
	if (key == '4' && b_key == false)
	{
		b_key_check = 4;
		b_key = true;
	}

	if (key == '1' && r_key == false)
	{
		r_key_check = 1;
		r_key = true;
	}
	if (key == '2' && r_key == false)
	{
		r_key_check = 2;
		r_key = true;
	}
	if (key == '3' && r_key == false)
	{

		r_key_check = 3;
		r_key = true;
	}
	if (key == '4' && r_key == false)
	{

		r_key_check = 4;
		r_key = true;
	}
	if (key == '1' && y_key == false)
	{
		y_key_check = 1;
		y_key = true;
	}
	if (key == '2' && y_key == false)
	{

		y_key_check = 2;
		y_key = true;
	}
	if (key == '3' && y_key == false)
	{
		y_key_check = 3;
		y_key = true;
	}
	if (key == '4' && y_key == false)
	{

		y_key_check = 4;
		y_key = true;
	}
	if (key == '1' && g_key == false)
	{
		cout << "green";
		g_key_check = 1;
		g_key = true;
	}
	if (key == '2' && g_key == false)
	{

		g_key_check = 2;
		g_key = true;
	}
	if (key == '3' && g_key == false)
	{

		g_key_check = 3;
		g_key = true;
	}
	if (key == '4' && g_key == false)
	{

		g_key_check = 4;
		g_key = true;
	}
	if (key == 32)
	{
		space_check = true;
	}
	if (key == 's')
	{
		boolean = 1;
		glutDisplayFunc(GameDisplay);
	}
	if (key == 'q')
	{
		boolean = 2;
		glutDisplayFunc(GameDisplay);
	}
	if (key == 'i')
	{
		boolean = 3;
		glutDisplayFunc(GameDisplay);
	}
	glutDisplayFunc(GameDisplay);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y)
{
	//	cout << x << " " << y << endl;
	//glutPostRedisplay();
}
void MouseMoved(int x, int y)
{
	//cout << x << " " << y << endl;
	//glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		//cout << GLUT_DOWN << " " << GLUT_UP << endl;
	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		//cout<<"Right Button Pressed"<<endl;
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char *argv[])
{

	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	InitRandomizer();							  // seed the random number generator...
	glutInit(&argc, argv);						  // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50);				  // set the initial position of our window
	glutInitWindowSize(width, height);			  // set the size of our window
	glutCreateWindow("OS Project");				  // set the title of our game window
	SetCanvasSize(width, height);				  // set the number of pixels...
        glutDisplayFunc(GameDisplay);
	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutKeyboardFunc(PrintableKeys);
	//glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
									   // tell library which function to call for printable ASCII characters
									   // This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved);	  // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	pthread_exit(NULL);
	return 1;
}
#endif /* AsteroidS_CPP_ */
