#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include "device.h"

#define WIDTH_RESOLUTION    (640)
#define HEIGHT_RESOLUTION   (480)
#define CENTER_X            (WIDTH_RESOLUTION/2)
#define CENTER_Y            (HEIGHT_RESOLUTION/2)
#define DEFAULT_RADIUS      (20)
#define MAX_RADIUS          (50)
#define MIN_RADIUS          (5)

typedef struct circle_t
{
    SDL_Point center;
    int32_t radius;
} circle_t;

void draw_circle(SDL_Renderer* r, circle_t* circle);
void edit_circle(circle_t* circle, nunchuk_t* values);

#endif