#include <SDL.h>
#include <ctime>
#include <cstdlib>

enum Direction
{
    DIRECTION_UP,
    DIRECTION_DOWN
};

int main ( int argc, char* argv[] )
{
    SDL_Event e;

    bool quit = false;

    // Set up SDL window
    SDL_Window *window = SDL_CreateWindow ( "Circles!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_HIDDEN );
    SDL_Renderer* rend = SDL_CreateRenderer ( window, -1, 0 );
    SDL_ShowWindow ( window );

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

    while ( ! quit )
    {
        while ( SDL_PollEvent ( &e ) != 0 )
        {
            if ( e.type == SDL_QUIT )
                quit = true;
            else if ( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE )
                quit = true;
        }

        int x, y;
        SDL_GetMouseState(&x, &y);

        SDL_Rect newrectangle =
        {
            x,      // Align to cursor (horizontal)
            y,     // Align to cursor (vertical)
            20,     // Width
            20      // Height
        };

        // Check boundaries
        if ( red >= 255 )   red_d = DIRECTION_DOWN;
        if ( red >= 0 )     red_d = DIRECTION_UP;
        if ( green >= 255 ) green_d = DIRECTION_DOWN;
        if ( green >= 0 )   green_d = DIRECTION_UP;
        if ( blue >= 255 )  blue_d = DIRECTION_DOWN;
        if ( blue >= 0 )    blue_d = DIRECTION_UP;

        // Recolorize
        if ( red_d == DIRECTION_DOWN )  red--;
        if ( red_d == DIRECTION_UP )    red++;
        if ( green_d == DIRECTION_DOWN )green--;
        if ( green_d == DIRECTION_UP )  green++;
        if ( blue_d == DIRECTION_DOWN ) blue--;
        if ( blue_d == DIRECTION_UP )   blue++;

        // Fill
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





    return 0;
}
