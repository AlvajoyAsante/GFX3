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

#include "gfx/bus/bus.h"

// Must include to use gfx3
#include "gfx3/gfx3.h"

// Sprite Layers (having the NULL at the end is very important)
// gfx_sprite_t *car_sprites[7] = {layer1, layer2, layer3, layer4, layer5, layer6, NULL};
// unsigned char *sprites[64] = {teapot1_compressed,
//                              teapot2_compressed,
//                              teapot3_compressed,
//                              teapot4_compressed,
//                              teapot5_compressed,
//                              teapot6_compressed,
//                              teapot7_compressed,
//                              teapot8_compressed,
//                              teapot9_compressed,
//                              teapot10_compressed,
//                              teapot11_compressed,
//                              teapot12_compressed,
//                              teapot13_compressed,
//                              teapot14_compressed,
//                              teapot15_compressed,
//                              teapot16_compressed,
//                              teapot17_compressed,
//                              teapot18_compressed,
//                              teapot19_compressed,
//                              teapot20_compressed,
//                              teapot21_compressed,
//                              teapot22_compressed,
//                              teapot23_compressed,
//                              teapot24_compressed,
//                              teapot25_compressed,
//                              teapot26_compressed,
//                              teapot27_compressed,
//                              teapot28_compressed,
//                              teapot29_compressed,
//                              teapot30_compressed,
//                              teapot31_compressed,
//                              teapot32_compressed,
//                              teapot33_compressed,
//                              teapot34_compressed,
//                              teapot35_compressed,
//                              teapot36_compressed,
//                              teapot37_compressed,
//                              teapot38_compressed,
//                              teapot39_compressed,
//                              teapot40_compressed,
//                              teapot41_compressed,
//                              teapot42_compressed,
//                              teapot43_compressed,
//                              teapot44_compressed,
//                              teapot45_compressed,
//                              teapot46_compressed,
//                              teapot47_compressed,
//                              teapot48_compressed,
//                              teapot49_compressed,
//                              teapot50_compressed,
//                              teapot51_compressed,
//                              teapot52_compressed,
//                              teapot53_compressed,
//                              teapot54_compressed,
//                              teapot55_compressed,
//                              teapot56_compressed,
//                              teapot57_compressed,
//                              teapot58_compressed,
//                              teapot59_compressed,
//                              teapot60_compressed,
//                              teapot61_compressed,
//                              NULL};

gfx_sprite_t *sprites[23] = {bus1,
                             bus2,
                             bus3,
                             bus4,
                             bus5,
                             bus6,
                             bus7,
                             bus8,
                             bus9,
                             bus10,
                             bus11,
                             bus12,
                             bus13,
                             bus14,
                             bus15,
                             bus16,
                             bus17,
                             bus18,
                             bus19,
                             bus20,
                             bus21,
                             bus22,
                             NULL};

// Creates a car object
struct gfx3_object_t object;

int main(void)
{
    uint8_t x = 0;

    // Set Sprites
    // gfx3_SetObjectCompressedSprites(&object, sprites, teapot1_width, teapot1_height);
    gfx3_SetObjectSprites(&object, sprites);

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the palette used by the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    /* Draw to buffer to avoid artifacts */
    gfx_SetDrawBuffer();

    // New feature!
    // gfx3_FlipObject(&object);

    // testing offseting 
    gfx3_SetObjectOffset(&object, 0, 1);

    do
    {
        /* Draw a rotated transparent scaled spite */
        gfx3_RotateObject(&object, x);
        gfx3_TransparentObject(&object, (LCD_WIDTH / 2), (LCD_HEIGHT / 2));

        /* Show the buffered screen */
        gfx_BlitBuffer();

        /* Clear the old drawn sprite */
        gfx_FillScreen(1);

        /* Change the rotation amount */
        x += 5;

    } while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
