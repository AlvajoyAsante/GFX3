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

/* Must include in order to use gfx3 */
#include "gfx3/gfx3.h"

/* Must include sprite layers */
#include "gfx/sprites.h"

/* Array filled layers in order */
gfx_sprite_t *sprites[10] = {star,
							star,
							star,
							star,
							star,
							star,
							star,
							star,
							star,
							NULL}; // Must always include NULL at the end

/* Create a gfx3 object (Make sure it isn't ) */
struct gfx3_object_t object;

int main(void)
{
	uint8_t x = 0;

	/* Set Sprites */
	gfx3_SetObjectSprites(&object, sprites);

	/* Initialize graphics drawing */
	gfx_Begin();

	/* Set the palette used by the sprites */
	gfx_SetPalette(global_palette, sizeof_global_palette, 0);
	gfx_SetTransparentColor(2);

	/* Set scale */
	gfx3_SetObjectScale(&object, 70);

	/* Draw to buffer to avoid artifacts */
	gfx_SetDrawBuffer();

	do
	{
		/* Draw a rotated transparent scaled spite */
		gfx3_SetObjectAngle(&object, x);
		gfx3_TransparentObject(&object, (LCD_WIDTH / 2), (LCD_HEIGHT / 2));

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
