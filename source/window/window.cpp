#include "window.h"

Window * Window::instance = NULL;
Mouse Window::mouse;
Keyboard Window::keyboard;

Window * Window::CreateWindow(const char * title, const int width, const int height)
{
    if (Window::instance == NULL)
    {
        Window::instance = new Window(title, width, height);
    }
    return Window::instance;
}

Window * Window::GetWindow()
{
    return Window::instance;
}

bool Window::CheckInput()
{
    SDL_Event e;
    keyboard.Update();
    while( SDL_PollEvent( &e ) != 0 )
    {
        if (e.type == SDL_KEYDOWN)
        {
            keyboard.KeyDown(e.key.keysym.sym);
        } 
        else if (e.type == SDL_KEYUP)
        {
            keyboard.KeyUp(e.key.keysym.sym);
        }
        else if( e.type == SDL_QUIT )
        {
            return false;
        }
    }
    mouse.Update();
    return true;
}
void Window::DestroyWindow()
{
    if (Window::instance != NULL)
    {
        delete Window::instance;
        Window::instance = NULL;
    }
}

Window::~Window()
{
    SDL_DestroyWindow( sdlWindow );
    sdlWindow = NULL;
    SDL_Quit();
}

Window::Window(const char * title, const int w, const int h)
{
    width = w;
    height = h;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        windowIsWorking = false;
        return;
    }

    //Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        printf( "Warning: Linear texture filtering not enabled!" );
    }

    //Create window
    sdlWindow = SDL_CreateWindow( title, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                SDL_WINDOWPOS_UNDEFINED, 
                                width, 
                                height, 
                                SDL_WINDOW_SHOWN );
    if( sdlWindow == NULL )
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        windowIsWorking = false;
        return;
    }

    windowIsWorking = true;
}
