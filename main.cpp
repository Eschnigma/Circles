#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
using std::stringstream;
using std::cout;
using std::endl;

enum Direction
{
    DIRECTION_UP,
    DIRECTION_DOWN
};

enum Mode
{
    MODE_MOUSE,
    MODE_RANDOM
};

int main ( int argc, char* argv[] )
{
    SDL_Event e;

    bool quit = false;

    // Set up SDL window
    SDL_Window *window = SDL_CreateWindow ( "Circles!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_HIDDEN );
    SDL_Renderer* rend = SDL_CreateRenderer ( window, -1, 0 );
    SDL_ShowWindow ( window );

    // Explain user how this works.
    stringstream instructions;
    instructions << "Welcome to Circles!" << endl;
    instructions << "You won't see any circles here." << endl << endl;

    instructions << "There are two modes to play with:" << endl;
    instructions << "\t1. Mouse mode (default)" << endl;
    instructions << "\t2. Random mode" << endl;
    instructions << "To switch between modes, press m" << endl << endl;

    instructions << "Other options:" << endl;
    instructions << "\t * Randomize color with r" << endl;
    instructions << "\t * Change box size with numpad + and - " << endl;
    instructions << "\t * Wonder why this exist - scratch back of head with hand" << endl << endl;

    instructions  << "Have fun!";

    SDL_ShowSimpleMessageBox(
                SDL_MESSAGEBOX_INFORMATION,
                "Instructions",
                instructions.str().c_str(),
                window
                );

    //Initial black screen
    SDL_SetRenderDrawColor ( rend, 0, 0, 0, 255);
    SDL_RenderClear ( rend );
    SDL_RenderPresent ( rend );

    // Set starting values
    srand ( time ( nullptr ) );
    int red =   rand() % 256;   Direction red_d =   DIRECTION_UP;
    int green = rand() % 256;   Direction green_d = DIRECTION_UP;
    int blue =  rand() % 256;   Direction blue_d =  DIRECTION_UP;
    int alpha = 255;
    SDL_SetRenderDrawColor(
                rend,
                red,
                green,
                blue,
                alpha
                );
    int size = 20;
    bool render = false;
    Mode mode = MODE_MOUSE;

    while ( ! quit )
    {
        while ( SDL_PollEvent ( &e ) != 0 )
        {
            if ( e.type == SDL_QUIT )
                quit = true;
            else if ( e.type == SDL_KEYDOWN )
            {
                switch ( e.key.keysym.sym )
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;

                case SDLK_KP_PLUS:
                    size+=5;
                    break;

                case SDLK_KP_MINUS:
                    size-=5;
                    break;

                case SDLK_r:
                    red =   rand() % 256;
                    green = rand() % 256;
                    blue =  rand() % 256;
                    alpha = 255;
                    break;

                case SDLK_m:
                    {
                        if ( mode == MODE_RANDOM ) mode = MODE_MOUSE;
                        else mode = MODE_RANDOM;
                    }
                    break;

                case SDLK_p:
                    cout << "Current color makeup:\n";
                    cout << "Red: " << red << endl;
                    cout << "Green: " << green << endl;
                    cout << "Blue: " << blue << endl;
                    cout << endl;
                    break;
                }
            }
            else if ( e.type == SDL_MOUSEBUTTONDOWN )
            {
                if ( e.button.button == SDL_BUTTON_LEFT )
                    render = true;
            }
            else if ( e.type == SDL_MOUSEBUTTONUP )
            {
                if ( e.button.button == SDL_BUTTON_LEFT )
                    render = false;
            }
        }

        int x, y;
        SDL_GetMouseState(&x, &y);

        SDL_Rect newrectangle;

        if ( mode == MODE_MOUSE )
        {
            newrectangle.x = x;
            newrectangle.y = y;
        }
        else
        {
            newrectangle.x = rand() % ( 800 + size ) - size;
            newrectangle.y = rand() % ( 800 + size ) - size;
        }

            newrectangle.w = size;
            newrectangle.h = size;

        // Check boundaries
        if ( red >= 255 )   red_d = DIRECTION_DOWN;
        if ( red <= 0 )     red_d = DIRECTION_UP;
        if ( green >= 255 ) green_d = DIRECTION_DOWN;
        if ( green <= 0 )   green_d = DIRECTION_UP;
        if ( blue >= 255 )  blue_d = DIRECTION_DOWN;
        if ( blue <= 0 )    blue_d = DIRECTION_UP;

        // Recolorize
        if ( red_d == DIRECTION_DOWN )  red--;
        if ( red_d == DIRECTION_UP )    red++;
        if ( green_d == DIRECTION_DOWN )green--;
        if ( green_d == DIRECTION_UP )  green++;
        if ( blue_d == DIRECTION_DOWN ) blue--;
        if ( blue_d == DIRECTION_UP )   blue++;

        // Fill
        if ( render || mode == MODE_RANDOM )
        {
            SDL_SetRenderDrawColor(
                        rend,
                        red,
                        green,
                        blue,
                        alpha
                        );
            SDL_RenderFillRect ( rend, &newrectangle );

            // Outline
            SDL_SetRenderDrawColor(
                        rend,
                        0,
                        0,
                        0,
                        255
                        );
            SDL_RenderDrawRect ( rend, &newrectangle );

            SDL_RenderPresent( rend );
        }
    }

    return 0;
}
