#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdlib.h>
#include "engine.h"
#include "device.h"

/*SDL_Window *o;
SDL_Renderer *r;*/
int32_t quit = 1;

int32_t main()
{
    /*circle_t circle = 
    {
        {
            CENTER_X,
            CENTER_Y,
        },
      DEFAULT_RADIUS
    };*/
    
    nunchuk_t readings;
    
    int32_t fd = open_device(NUNCHUK_DEVICE);
    
    if (fd == RET_ERR)
    {
        return RET_ERR;
    }

    /*SDL_Init(SDL_INIT_VIDEO);

    o = SDL_CreateWindow("Nunchuk",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            WIDTH_RESOLUTION,
                            HEIGHT_RESOLUTION,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    r = SDL_CreateRenderer(o, -1, SDL_RENDERER_ACCELERATED);*/

    while(quit)
    {
        if (read_device(fd, &readings) == RET_ERR)
        {
            break;
        }
        
        printf("%u %u %u %u\n", (unsigned int)readings.x_axis,
               (unsigned int)readings.y_axis,
               (unsigned int)readings.c_pressed,
               (unsigned int)readings.z_pressed);
        
        usleep(500000);
        /*SDL_SetRenderDrawColor(r,0,0,255,255);
        SDL_RenderClear(r);
        SDL_SetRenderDrawColor(r,0,0,0,255);
        draw_circle(r, &circle);
        SDL_RenderPresent(r);*/
    }
    
    if (close_device(fd) == RET_ERR)
    {
        return RET_ERR;
    }

    /*SDL_DestroyWindow(o);
    SDL_DestroyRenderer(r);
    SDL_Quit();*/

    return 0;
}
