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
gfx_sprite_t *sprites[23] = {house1,
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
struct gfx3_object_t objectB;

int main(void)
{
    uint8_t x = 0;

    // Set Sprites
    // gfx3_SetObjectCompressedSprites(&object, sprites, teapot1_width, teapot1_height);
    gfx3_SetObjectSprites(&objectA, sprites);
    gfx3_SetObjectSprites(&objectB, sprites);

    /* Initialize graphics drawing */
    gfx_Begin();
    gfx_FillScreen(0);

    /* Set the palette used by the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    gfx_SetTransparentColor(2);

    /* Draw to buffer to avoid artifacts */
    gfx_SetDrawBuffer();

    // New feature!
    gfx3_FlipObject(&objectA);

    // testing offsetting
    // gfx3_SetObjectOffset(&object, 1, 1);

    while (!os_GetCSC())
    {
        /* Draw a rotated transparent scaled spite */
        gfx3_SetObjectAngle(&objectA, x);
        gfx3_SetObjectAngle(&objectB, x);
        gfx3_TransparentObject(&objectA, ((LCD_WIDTH - (house1_width * 2)) / 2), ((LCD_HEIGHT - (house1_height * 2)) / 2));
        gfx3_TransparentObject(&objectB, ((LCD_WIDTH + (house1_width * 2)) / 2), ((LCD_HEIGHT + (house1_height * 2)) / 2));

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
