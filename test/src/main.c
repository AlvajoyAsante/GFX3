/*
 *--------------------------------------
 * Program Name: Demo
 * Author: Alvajoy 'Alvajoy123' Asante
 * Description: GFX Demo
 *--------------------------------------
 */

#include <tice.h>
#include <graphx.h>
#include <keypadc.h>

#include "gfx/tank/tank.h"
#include "gfx3/gfx3.h"

// Sprite Layers (having the NULL at the end is very important)
// gfx_sprite_t *car_sprites[7] = {layer1, layer2, layer3, layer4, layer5, layer6, NULL};
gfx_sprite_t *sprites[14] = {small_tank_00,
                            small_tank_01,
                            small_tank_02,
                            small_tank_03,
                            small_tank_04,
                            small_tank_05,
                            small_tank_06,
                            small_tank_07,
                            small_tank_08,
                            small_tank_09,
                            small_tank_10,
                            small_tank_11,
                            small_tank_12,
                            NULL};

// Creates a car object
struct gfx3_object_t object;

int main(void)
{
    uint8_t x = 0;

    // Set Sprites
    gfx3_SetObjectSprites(&object, sprites);

    /* Initialize graphics drawing */
    gfx_Begin();

    /* Set the palette used by the sprites */
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);

    /* Draw to buffer to avoid artifacts */
    gfx_SetDrawBuffer();

    do
    {
        /* Draw a rotated transparent scaled spite */
        gfx3_RotateObject(&object, x);
        gfx3_TransparentObject_NoClip(&object, (LCD_WIDTH / 2), (LCD_HEIGHT / 2));

        /* Show the buffered screen */
        gfx_BlitBuffer();

        /* Clear the old drawn sprite */
        gfx_FillScreen(1);

        /* Change the rotation amount */
        x++;

    } while (!os_GetCSC());

    /* End graphics drawing */
    gfx_End();

    return 0;
}
