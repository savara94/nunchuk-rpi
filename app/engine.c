#include "engine.h"

#define X_AXIS_LEFT     (100)
#define X_AXIS_RIGHT    (150)

#define Y_AXIS_UP       (150)
#define Y_AXIS_DOWN     (100)

#define OFFSET		(30)

void draw_circle(SDL_Renderer* r, circle_t* circle)
{
    int32_t radius = circle->radius;
    SDL_Point center = circle->center;

    for (int32_t w = 0; w < radius * 2; w++)
    {
        for (int32_t h = 0; h < radius * 2; h++)
        {
            int32_t dx = radius - w;
            int32_t dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(r, center.x + dx, center.y + dy);
            }
        }
    }
}

void edit_circle(circle_t* circle, nunchuk_t* values)
{
    uint8_t x_axis = values->x_axis;
    uint8_t y_axis = values->y_axis;
    uint8_t c_pressed = values->c_pressed;
    uint8_t z_pressed = values->z_pressed;

    if (x_axis < X_AXIS_LEFT)
    {
        if (circle->center.x - circle->radius >= 0)
        {
            circle->center.x -= circle->radius/2;
        }
    }

    if (x_axis > X_AXIS_RIGHT)
    {
        if (circle->center.x + circle->radius < WIDTH_RESOLUTION)
        {
            circle->center.x += circle->radius/2;
        }
    }

    if (y_axis > Y_AXIS_UP)
    {
        if (circle->center.y - circle->radius >= 0)
        {
            circle->center.y -= circle->radius/2;
        }
    }

    if (y_axis < Y_AXIS_DOWN)
    {
        if (circle->center.y + circle->radius < HEIGHT_RESOLUTION)
        {
            circle->center.y += circle->radius/2;
        }
    }

    if (c_pressed)
    {
        if (circle->radius < MAX_RADIUS)
        {
            circle->radius++;
        }
    }

    if (z_pressed)
    {
        if (circle->radius > MIN_RADIUS)
        {
            circle->radius--;
        }
    }
}
