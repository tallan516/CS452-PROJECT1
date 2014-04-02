#include "timShader.h"

using namespace std;

GLuint abuffer;
GLuint buffer[2];

GLfloat vertices[] = {	0.0f,0.0f,0.0f,
				-0.0125f,0.0f,0.0f,
				-0.025f,0.0125f,0.0f,
				-0.025f,0.0375f,0.0f,
				-0.0125f,0.05f,0.0f,
				0.0125f,0.05f,0.0f,
				0.025f,0.0375f,0.0f,
				0.025f,0.0125f,0.0f,
				0.0125f,0.0f,0.0f,
				0.0f,0.0f,0.0f,
				0.0f,-0.0125f,0.0f,
				-0.025f,-0.0125f,0.0f,
				0.025f,-0.0125f,0.0f,
				0.0f,-0.0125f,0.0f,
				0.0f,-0.025f,0.0f,
				-0.025f,-0.05f,0.0f,
				0.0f,-0.025f,0.0f,
				0.025f,-0.05f,0.0f,
				0.0f,-0.025f,0.0f	};

				//R, G, B, A (transparency)
GLfloat colors[] = {	0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f	}; 

float xLocation = 0.0f;
float yLocation = 0.0f;

int score = 0;

//Declare functions
void init();
void display();
void keyPressed(unsigned char key, int x, int y);


int main(int argc, char **argv)
{
	//Main method stuff
	glutInit(&argc, argv);		//Initializes glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//Glut display mode
	glutInitWindowSize(500, 500);		//Sets size of window
	glutInitWindowPosition(0, 0);		//Sets position of window
	glutCreateWindow("CS452 Project 1");	//Creates the window
	glutInitContextVersion(4, 3);		//Tells OpenGL what version you are using
	glutInitContextProfile(GLUT_CORE_PROFILE | GLUT_COMPATIBILITY_PROFILE);		//Tells OpenGL what profile you are using
	glewInit();		//Initializes glew
	glutDisplayFunc(display);	//Displays the shapes
	glutKeyboardFunc(keyPressed); // Tell GLUT to use the function "keyPressed" for key presses  
	
	init();	//Calls function to initialize the shaders and set up buffers
	
	glutMainLoop();	//Tells OpenGL to keep rendering (never ending loop)
	return 0;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);		//Clears the frame buffer
	
	glLoadIdentity();
	glTranslatef(xLocation, yLocation, 0.0f);
	
	glDrawArrays(GL_LINE_LOOP, 0, 19);	//Renders the polygon
	glFlush();					//Makes sure all data is rendered as soon as possible
}

void keyPressed(unsigned char key, int x, int y)
{
	if(key == 'a')		//Left
	{
		xLocation -= .01f;
	}
	else if(key == 'd')	//Right
	{
		xLocation += .1f;
	}
	else if(key == 'w')	//Up
	{
		yLocation += .1f;
	}
	else if(key == 's')	//Down
	{
		yLocation -= .1f;
	}
}

void init()
{
	initShaders();	//Calls the initialize shader function in the header file
	
	glGenVertexArrays(1, &abuffer);
	glBindVertexArray(abuffer);
	
	glGenBuffers(2, buffer);
	
	//Sets up pointers and stuff
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	//Enables vertex arrays to draw stuff
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);	
}



