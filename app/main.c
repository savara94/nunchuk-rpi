#include <SDL2/SDL.h>
#include <stdlib.h>

SDL_Window *o;
SDL_Renderer *r;

void draw_circle(SDL_Point center, int radius)
{
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(r, center.x + dx, center.y + dy);
            }
        }
    }
}

int main()
{
    SDL_Event e;
    SDL_Point q = { 320, 240};
    int i =1;

    SDL_Init(SDL_INIT_VIDEO);

    o = SDL_CreateWindow("Game test",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            640,
                            480,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    r = SDL_CreateRenderer(o, -1,SDL_RENDERER_ACCELERATED);

    while(i)
    {
        while(SDL_PollEvent(&e) !=0)
        {
            if(e.type == SDL_QUIT)
                i=0;
            else if(e.type == SDL_KEYDOWN)
            {
                switch(e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    i=0;
                break;
                case SDLK_UP:
                    q.y -=10;
                break;
                case SDLK_DOWN:
                    q.y +=10;
                break;
                case SDLK_RIGHT:
                    q.x +=10;
                break;
                case SDLK_LEFT:
                    q.x -=10;
                break;
                }
            }
        }
        SDL_SetRenderDrawColor(r,0,0,255,255);
        SDL_RenderClear(r);
        SDL_SetRenderDrawColor(r,0,0,0,255);
        draw_circle(q, 20);
        /*SDL_RenderFillRect(r,&q);*/
        SDL_RenderPresent(r);
    }

    SDL_DestroyWindow(o);
    SDL_DestroyRenderer(r);
    SDL_Quit();

    return 0;
}
