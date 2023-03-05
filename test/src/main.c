/*
 *--------------------------------------
 * Program Name: Demo
 * Author: Alvajoy 'Alvajoy123' Asante
 * Description: GFX3 Demo
 *--------------------------------------
 */

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

#include "gfx/house/house.h"

// Must include in order to use gfx3
#include "gfx3/gfx3.h"

// Sprites
gfx_sprite_t *sprites[15] = {house1,
                             house2,
                             house3,
                             house4,
                             house5,
                             house6,
                             house7,
                             house8,
                             house9,
                             house10,
                             house11,
                             house12,
                             house13,
                             house14,
                             NULL};

// Creates a car object
struct gfx3_object_t objectA;

int main(void)
{
    uint8_t x = 0;

    // Set Sprites
    gfx3_SetObjectSprites(&objectA, sprites);

    /* Initialize graphics drawing */
    gfx_Begin();
    gfx_FillScreen(0);

    /* Set the palette used by the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(2);

    /* Draw to buffer to avoid artifacts */
    gfx_SetDrawBuffer();


    // testing offsetting
    gfx3_SetObjectOffset(&objectA, 1, 1);
    
    // gfx3_AddPadding(&objectA, 5, 2);

    while (!os_GetCSC())
    {
        for (int i = 0; i < 14; i++)
        {
            gfx_Sprite(sprites[i], (i+1) * sprites[i]->width, 0);
            gfx_Sprite(objectA.layers[i], i * objectA.layers[i]->width, 25);
        }

        /* Draw a rotated transparent scaled spite */
        gfx_SetColor(7); // Green
        gfx_FillRectangle((LCD_WIDTH - objectA.width) / 2, (LCD_HEIGHT - objectA.height) / 2, objectA.width, objectA.height);

        gfx3_SetObjectAngle(&objectA, x);
        gfx3_TransparentObject(&objectA, (LCD_WIDTH - objectA.width) / 2, (LCD_HEIGHT - objectA.height) / 2);

        /* Show the buffered screen */
        gfx_BlitBuffer();

        /* Clear the old drawn sprite */
        gfx_FillScreen(0);

        /* Change the rotation amount */
        x++;
    }

    /* End graphics drawing */
    gfx_End();

    return 0;
}
