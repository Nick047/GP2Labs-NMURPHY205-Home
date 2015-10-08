//header files

#include <iostream>	//this allows information to be output which is useful for debugging
//Header for SDL2 functionality
#include <SDL.h>
//opengl header files
#include <SDL_opengl.h>
#include <gl\GLU.h>


//Global variables
//pointers to out sdl windows
SDL_Window * window;

//Constants to coontrol window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
bool running = true;	//set to false when you want teh game to stop runinng
//SDL GL Context
SDL_GLContext glcontext = NULL;


//Global Functions
void InitWindow(int width, int height, bool fullscreen)	//function takes in 2 integers and a boolean fullscreen or not
		{
	//Create a window
	window = SDL_CreateWindow("LAB 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
//^Hover over SDL_CreateWindow the variable should be obvious from there except the last one which is a SDL_WindowFLag (look it up) https://wiki.libsdl.org/SDL_WindowFlags
}

//Function to draw
void render()
{
	//set the clear color(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clears the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	/*
	float triangle1_pos_x = 1.0f;
	float triangle1_pos_y = 1.0f;
	float triangle1_pos_z = 1.0f;
	
	float triangle2_pos_x = 1.0f;
	float triangle2_pos_y = 1.0f;
	float triangle2_pos_z = 1.0f;	
	*/
	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);
	//reset using the identity matrix
	glLoadIdentity();
	//Translate to -5.0f on z axis
	glTranslatef(0.0f, 0.0f, -5.0f);
	//begin drawing triangles
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); //Color of the vertices
	glVertex3f(1.0f, 1.0f, 0.0f); //Top

	
	glColor3f(0.0f, 1.0f, 0.0f); //Color of the vertices
	glVertex3f(-1.0f, -1.0f, 0.0f); //Bottom Left

	glColor3f(0.0f, 0.0f, 1.0f); //Color of the vertices
	glVertex3f(1.0f, -1.0f, 0.0f); //Bottom Right
	glEnd();
	//tringle 2
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); //Color of the vertices
	glVertex3f(0.0f, 0.50f, 0.0f); //Top

	glColor3f(1.0f, 0.0f, 0.0f); //Color of the vertices
	glVertex3f(-0.50f, -0.50f, 0.0f); //Bottom Left

	glColor3f(1.0f, 0.0f, 0.0f); //Color of the vertices
	glVertex3f(0.50f, -0.50f, 0.0f); //Bottom Right
	glEnd();
	//require to swap the back and front buffer

	SDL_GL_SwapWindow(window);
}

//Function to update game state
void update()
{

}

//Used to cleanup once we exit

void CleanUp()	//clears the meemory when exiting the game loop
{
	SDL_GL_DeleteContext(glcontext);

	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL()
{
	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);
	//Something is wrong in creating the context, if it is still NULL
	if(!glcontext)
	{
		std::cout << "Error creating OpenGL Context" << SDL_GetError() <<
			std:: endl;
	}

	//Smooth Shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the depth buffer to 1.0
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//The depth to use
	glDepthFunc(GL_LEQUAL);

	//Turn on perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//Function to set/reset viewport
void setViewport( int width, int height)
{
	//screen ratio
	GLfloat ratio;

	//make sure height is always above 0
	if (height == 0)
	{
		height =1;
	}

	//calculate screen ratio
	ratio = (GLfloat)width / (GLfloat)height;

	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//this code is supposed to be after the call to glViewport but all I can see is the setup might be me being stupid but i'll put the code here

	//Change to project matrix mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Calculate perspective matrix, using glu library functions
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);

	//Reset using the identity matrix
	glLoadIdentity();

}

//Main method - entry point
int main(int argc, char* args[])	//integer trcks cmdline arguments and a pointer to an array of character strings containing the argumants //the returned integer detern=mines whether it has been run successfully 0 == success or a negative if not
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
{
	std::cout<< "ERROR SDL_Init" << SDL_GetError() <<std::endl;

	return -1;
}

//init everything - SDL, if it is nonzero we hve a problem
//Last year I had this problem it is a result of compatability with your mouse of monitor changing these should solve the problem though changing monitors is signficantly more annoying
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	//Call out InitOpenGL Function
	initOpenGL();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_Event event;
	while(running)
	{
		update();
		render();

		while(SDL_PollEvent(&event))
		{
			//Get event type
			if(event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				//set our boolean which controls game loop to false
				running = false;		//can't use two == because 
			}
		}
	}


	CleanUp();

	return 0;
}