#include "timShader.h"

using namespace std;

GLuint abuffer;
GLuint buffer[2];

GLfloat vertices[] = {	0.0f,0.0f,0.0f,
				-0.0125f,0.0f,0.0f,
				-0.025f,0.0125f,0.0f,
				-0.025f,0.0375f,0.0f,
				-0.0125f,0.05f,0.0f,	//5
				0.0125f,0.05f,0.0f,
				0.025f,0.0375f,0.0f,
				0.025f,0.0125f,0.0f,
				0.0125f,0.0f,0.0f,
				0.0f,0.0f,0.0f,		//10
				0.0f,-0.0125f,0.0f,
				-0.025f,-0.0125f,0.0f,
				0.025f,-0.0125f,0.0f,
				0.0f,-0.0125f,0.0f,
				0.0f,-0.025f,0.0f,	//15
				-0.025f,-0.05f,0.0f,
				0.0f,-0.025f,0.0f,
				0.025f,-0.05f,0.0f,
				0.0f,-0.025f,0.0f,
				
				0.5f,0.5f,0.0f,		//20
				0.525f,0.525f,0.0f,
				0.55f,0.5f,0.0f,
				0.525f,0.475f,0.0f,
				
				-1.0f,-1.0f,0.0f,
				-1.0f,-0.9f,0.0f,		//25
				-0.98f,-0.88f,0.0f,
				-0.92f,-0.88f,0.0f,
				-0.9f,-0.9f,0.0f,
				-0.9f,-1.0f,0.0f,
				-0.915f,-0.98f,0.0f,	//30
				-0.93f,-1.0f,0.0f,
				-0.95f,-0.98f,0.0f,
				-0.97f,-1.0f,0.0f,
				-0.985,-0.98f,0.0f,
				-1.0f,-1.0f,0.0f
					};



				//R, G, B, A (transparency)
GLfloat colors[] = {	0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,	//5
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,	//10
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,	//15
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				
				1.0f,0.84f,0.0f,1.0f,	//20
				1.0f,0.84f,0.0f,1.0f,
				1.0f,0.84f,0.0f,1.0f,
				1.0f,0.84f,0.0f,1.0f,
				
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,	//25
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,
				.0f,.0f,.0f,1.0f,	//30
				.0f,.0f,.0f,1.0f,
				.0f,.0f,.0f,1.0f,
				.0f,.0f,.0f,1.0f,
				.0f,.0f,.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f
					}; 

float xLocation = 0.0f;
float yLocation = 0.0f;
float xGLocation = 0.5f;
float yGLocation = 0.5f;
float xHLocation = -1.0f;
float yHLocation = -1.0f;

int score = 0;

//Declare functions
void display();
void keyPressed(unsigned char key, int x, int y);
void checkLocations();
void moveGold();
void moveGhost();


int main(int argc, char **argv)
{
	//Main method stuff
	glutInit(&argc, argv);	//Initializes glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//Glut display mode
	glutInitWindowSize(500, 500);		//Sets size of window
	glutInitWindowPosition(0, 0);		//Sets position of window
	glutCreateWindow("CS452 Project 1");	//Creates the window
	glutInitContextVersion(4, 3);		//Tells OpenGL what version you are using
	glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_COMPATIBILITY_PROFILE);
	glewInit();		//Initializes glew
	initShaders();	//Calls the initialize shader function in the header file
	glutDisplayFunc(display);
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the function "keyPressed" for key presses
	
	glutMainLoop();	//Tells OpenGL to keep rendering (never ending loop)

	return 0;
}

void keyPressed(unsigned char key, int x, int y)
{
	if(key == 'a')	//Left
	{
		if(xLocation > -0.95f)
		{
			xLocation -= .05f;
			for(int i = 0; i < 57; i++)
			{
				if(i % 3 == 0)
				{
					vertices[i] -= .05f;
				}
			}
		}
	}
	else if(key == 'd')	//Right
	{
		if(xLocation < 0.95f)
		{
			xLocation += .05f;
			for(int i = 0; i < 57; i++)
			{
				if(i % 3 == 0)
				{
					vertices[i] += .05f;
				}
			}
		}
	}
	else if(key == 'w')	//Up
	{
		if(yLocation < 0.95f)
		{
			yLocation += .05f;
			for(int i = 0; i < 57; i++)
			{
				if(i % 3 == 1)
				{
					vertices[i] += .05f;
				}
			}
		}
	}
	else if(key == 's')	//Down
	{
		if(yLocation > -0.95f)
		{
			yLocation -= .05f;
			for(int i = 0; i < 57; i++)
			{
				if(i % 3 == 1)
				{
					vertices[i] -= .05f;
				}
			}
		}
	}
	else if(key == 'q')
	{
		exit(0);
	}
	moveGhost();
	checkLocations();
	glutPostRedisplay();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glGenVertexArrays(1, &abuffer);
	glBindVertexArray(abuffer);
	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glDrawArrays(GL_POLYGON, 19, 4);	//Gold
	glDrawArrays(GL_POLYGON, 23, 12);	//Ghost
	glDrawArrays(GL_POLYGON, 0, 18);	//Stickfigure
	glFlush();					//Makes sure all data is rendered as soon as possible
}

void checkLocations()
{
	//If the ghost captures you
	if(	xLocation - xHLocation <= 0.10f &&
		xLocation - xHLocation >= -0.05f &&
		yLocation - yHLocation <= 0.15f &&
		yLocation - yHLocation >= -0.05f)
	{
		cout << "\nGAME OVER" << endl;
		cout << "The ghost captured you." << endl;
		cout << "\nFinal score: " << score << endl;
		exit(0);
	}
	
	//If you collect a piece of gold
	if(	xLocation - xGLocation <= 0.1f &&
		xLocation - xGLocation >= 0.0f &&
		yLocation - yGLocation <= 0.1f &&
		yLocation - yGLocation >= -0.05f)
	{
		score++;
		cout << "Score: " << score << endl;
		moveGold();
	}

}

void moveGold()
{
	int x = (rand() % 40) - 20;
	int y = (rand() % 40) - 20;

	xGLocation = (0.05f * x);
	yGLocation = (0.05f * y);

	vertices[57] = xGLocation;
	vertices[58] = yGLocation;
	vertices[60] = xGLocation + 0.025f;
	vertices[61] = yGLocation + 0.025f;
	vertices[63] = xGLocation + 0.05f;
	vertices[64] = yGLocation;
	vertices[66] = xGLocation + 0.025f;
	vertices[67] = yGLocation - 0.025f;

}

void moveGhost()
{
	//Move Ghost
	float move = 0.032f;
	if(xHLocation < xLocation)
	{
		xHLocation += move;
		for(int i = 69; i < 104; i+=3)
		{
			vertices[i] += move;
		}
	}
	else if(xHLocation > xLocation)
	{
		xHLocation -= move;
		for(int i = 69; i < 104; i+=3)
		{
			vertices[i] -= move;
		}
	}
	if(yHLocation < yLocation)
	{
		yHLocation += move;
		for(int i = 70; i < 104; i+=3)
		{
			vertices[i] += move;
		}
	}
	else if(yHLocation > yLocation)
	{
		yHLocation -= move;
		for(int i = 70; i < 104; i+=3)
		{
			vertices[i] -= move;
		}
	}
}










