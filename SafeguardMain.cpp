//Using SDL and standard io
#include <SDL.h>
#include <stdio.h>


//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//starts SDL, creates window
bool init();

//loads media
bool loadMedia();

//frees media, shut down SDL
void close();

//window we're rendering to
SDL_Window* gWindow = NULL;

//surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load/show on the screen
SDL_Surface* gYWing = NULL;

//screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Keeps track of time between steps
LTimer stepTimer;

bool init()
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

void processInput()
{
    //Check for various keycodes/mouse input

    //2 options:
        //Events: make event handler for each key corresponding with player action
        //Polling: every frame check keyboard which keys are down

    //Best advice: abstract away the polling/event stuff so can change it if we want to
    //Then to start with, just pick easiest option (maybe polling, look into SDL events though in tutorials)
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
    stepTimer.start();
}

void render()
{
    //draw background
    //draw background objects
    //draw bullets
    //draw npcs
    //draw player
    //draw asteroids/explosions/effects
    //flip
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
    }

    #MAIN GAME LOOP
    while(true)
    {
        //Get/process input from user
        processInput();

        //Make all input-independent updates (game world, physics, AI, etc)
        update();

        //Draw world + objects
        render();

        //Delay (goal: 60 fps)
        delay();
    }

    //Destroy window
    SDL_DestroyWindow( window );

    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}
