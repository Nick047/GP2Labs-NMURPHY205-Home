//header files

#include <iostream>	//this allows information to be output which is useful for debugging
//Header for SDL2 functionality
#include <SDL.h>

//Global variables
//pointers to out sdl windows
SDL_Window * window;

//Constants to coontrol window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
bool running = true;	//set to false when you want teh game to stop runinng

//Global Functions
void InitWindow(int width, int height, bool fullscreen)	//function takes in 2 integers and a boolean fullscreen or not
		{
	//Create a window
	window = SDL_CreateWindow("LAB 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
//^Hover over SDL_CreateWindow the variable should be obvious from there except the last one which is a SDL_WindowFLag (look it up) https://wiki.libsdl.org/SDL_WindowFlags
}

//Used to cleanup once we exit

void CleanUp()	//clears the meemory when exiting the game loop
{
	SDL_DestroyWindow(window);
	SDL_Quit();
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

	SDL_Event event;
	while(running)
	{
		while(SDL_PollEvent(&event))
		{
			//Get event type
			if(event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				//set our boolean which controls game loop to false
				running = false;
			}
		}
	}


	CleanUp();

	return 0;
}