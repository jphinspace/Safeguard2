//Using SDL and standard io
#include <SDL.h>
#include <stdio.h>

//starts SDL, creates window
bool init();

//loads media
bool loadMedia();

//frees media, shut down SDL
void close();//FPS thread and its spinlock (for fps counter variable)int fpsworker(void* data);
SDL_SpinLock gDataLock = 0;
//Event handlerSDL_Event e;
//window we're rendering to
SDL_Window* gWindow = NULL;

//surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load/show on the screen
SDL_Surface* gYWing = NULL;

//screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;//main loop end flagbool quit;//for fps counterint framesThisSecond; //this is displayed by main functionint countedFrames; //constantly increments, set to 0 by fpsworker once per second

//Keeps track of time between steps
LTimer stepTimer;bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //get window surface
            gScreenSurface = SDL_GetWindowSurface(gWindow);
        }
    }
    return success;
}

bool loadMedia()
{
    //loading success flag
    bool success = true;

    //load image
    gYWing = SDL_LoadBMP()
}
void close()
{
	//Free loaded images
	gSplashTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}int fpsworker( void* data )
{
    //Work continuously	SDL_AtomicLock( &gDataLock );	bool fpsquit = quit;	SDL_AtomicUnlock( &gDataLock );	while(!fpsquit)
	{

		SDL_AtomicLock( &gDataLock );		framesThisSecond = countedFrames;		countedFrames = 0;		SDL_AtomicUnlock( &gDataLock );

		//Wait one second
		SDL_Delay(1000);
	}

	return 0;
}
void processInput(SDL_Event e)
{    while(SDL_PollEvent(&e) != 0)    {        if(e.type == SDL_QUIT)        {            SDL_AtomicLock( &gDataLock );            quit = true;            SDL_AtomicUnlock( &gDataLock );        }    }    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);    if(currentKeyStates[SDL_SCANCODE_UP])    {        //do something    }
}

void update()
{
    //Calculate time step
    float timeStep = stepTimer.getTicks()/1000.f;

    //pseudo:
    //update any world stuff (background objects, etc)

    //NPC AI
    //for each npc
        //npc.strategize

    //for each object in the world
        //object.framenumber++
        //object.move (x += xv, y += yv)

    //handle collisions
    //Move for time step
    stepTimer.start();    //Calculate FPS    timeText.str("");    SDL_AtomicLock( &gDataLock );    timeText << "FPS: " << framesThisSecond;    SDL_AtomicUnlock( &gDataLock );    if(!gFPSTextTexture.loadFromRenderedText(timeText.str().c_str(), fpsColor))    {        printf("Unable to render FPS texture.\n");    }
}

void render()
{    //Clear screen    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);    SDL_RenderClear(gRenderer);
    //draw background
    //draw background objects
    //draw bullets
    //draw npcs
    //draw player
    //draw asteroids/explosions/effects    //draw FPS number (framesThisSecond)    gFPSTextTexture.render((SCREEN_WIDTH - gFPSTextTexture.getWidth())/2, (SCREEN_HEIGHT - gFPSTextTexture.getHeight())/2);
    //flip    SDL_RenderPresent(gRenderer);    //Increment frame counter    SDL_AtomicLock( &gDataLock );    countedFrames++;    SDL_AtomicUnlock( &gDataLock );
}

void delay()
{
    //delay such that game runs at 60fps
}

int main( int argc, char* args[] )
{
    //The window being rendered to
    SDL_Window* window = NULL;

    //THe surface contained by the window
    SDL_Surface* screenSurface = NULL;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL)
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get window surface
            screenSurface= SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

            //Update the surface
            SDL_UpdateWindowSurface( window );

            //Wait 2 seconds
            SDL_Delay(2000);
        }
    }    quit = false;    countedFrames = 0;    framesThisSecond = 0;    //Start fps counting thread    SDL_Thread* fpsThread = SDL_CreateThread(fpsworker, "FPSThread", NULL);    //FPS text    std::stringstream timeText;    SDL_Color fpsColor = {0,0,0,255};

    #MAIN GAME LOOP    SDL_AtomicLock( &gDataLock );    bool mainquit = quit;    SDL_AtomicUnlock( &gDataLock );
    while(!mainquit)
    {
        //Get/process input from user
        processInput();

        //Make all input-independent updates (game world, physics, AI, etc)
        update();

        //Draw world + objects
        render();

        //Delay (goal: 120 fps with vsync)
        delay();    }
    SDL_WaitThread(fpsThread, NULL);
    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
