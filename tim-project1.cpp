#include "timShader.h"

using namespace std;

GLuint abuffer;
GLuint buffer[2];

GLfloat vertices[] = {	0.0f,0.0f,0.0f,		//0
				-0.0125f,0.0f,0.0f,
				-0.025f,0.0125f,0.0f,
				-0.025f,0.0375f,0.0f,
				-0.0125f,0.05f,0.0f,
				0.0125f,0.05f,0.0f,	//5
				0.025f,0.0375f,0.0f,
				0.025f,0.0125f,0.0f,
				0.0125f,0.0f,0.0f,
				0.0f,0.0f,0.0f,
				0.0f,-0.0125f,0.0f,	//10
				-0.025f,-0.0125f,0.0f,
				0.025f,-0.0125f,0.0f,
				0.0f,-0.0125f,0.0f,
				0.0f,-0.025f,0.0f,
				-0.025f,-0.05f,0.0f,	//15
				0.0f,-0.025f,0.0f,
				0.025f,-0.05f,0.0f,
				0.0f,-0.025f,0.0f,
				
				0.5f,0.5f,0.0f,
				0.525f,0.525f,0.0f,		//20
				0.55f,0.5f,0.0f,
				0.525f,0.475f,0.0f,
				0.5f,0.5f,0.0f
					};



				//R, G, B, A (transparency)
GLfloat colors[] = {	0.0f,1.0f,0.0f,1.0f,	//0
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,	//5
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,	//10
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,	//15
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				
				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,	//20
				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f	}; 

float xLocation = 0.0f;
float yLocation = 0.0f;
float xDLocation = 0.5f;
float yDLocation = 0.5f;

int score = 0;

//Declare functions
void display();
void keyPressed(unsigned char key, int x, int y);
void checkLocations();
void moveShape();


int main(int argc, char **argv)
{
	//Main method stuff
	glutInit(&argc, argv);		//Initializes glut
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
	if(key == 'a')		//Left
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
	else if(key == 'd')	//Right
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
	else if(key == 'w')	//Up
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
	else if(key == 's')	//Down
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
	
	glDrawArrays(GL_POLYGON, 19, 22);
	glDrawArrays(GL_POLYGON, 0, 19);	//Renders
	glFlush();					//Makes sure all data is rendered as soon as possible
}

void checkLocations()
{
	if(	xLocation - xDLocation <= 0.1f && 
		xLocation - xDLocation >= 0.0f &&
		yLocation - yDLocation <= 0.1f && 
		yLocation -yDLocation >= -0.05f)
	{
		score++;
		cout << score << endl;
		moveShape();
	}
	
}

void moveShape()
{
	int x = (rand() % 40) - 20;
	int y = (rand() % 40) - 20;
	
	xDLocation = (0.05f * x);
	yDLocation = (0.05f * y);
	
	vertices[57] = xDLocation;
	vertices[58] = yDLocation;
	
	vertices[60] = xDLocation + 0.025f;
	vertices[61] = yDLocation + 0.025f;
	
	vertices[63] = xDLocation + 0.05f;
	vertices[64] = yDLocation;
	
	vertices[66] = xDLocation + 0.025f;
	vertices[67] = yDLocation - 0.025f;
	
	vertices[69] = xDLocation;
	vertices[70] = yDLocation;
	
	
	cout << "XD: " << xDLocation << "  YD: " << yDLocation << endl;
	for(int i = 57; i < 71; i+=3)
	{
		cout << vertices[i] << "\t" << vertices[i+1] << endl;
	}
	
}











