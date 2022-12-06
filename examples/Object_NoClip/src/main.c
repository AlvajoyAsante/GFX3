#include <tice.h>
#include <graphx.h>

/* Include the converted graphics file */
#include "gfx/gfx.h"

/* Include the gfx3 library file */
#include "gfx3/gfx3.h"

/* Make a sprite array for the layers */
unsigned char *spr_data[] = 
{
	small_tank_00_data,
	small_tank_01_data,
	small_tank_02_data,
	small_tank_03_data,
	small_tank_04_data,
	small_tank_05_data,
	small_tank_06_data,
	small_tank_07_data,
	small_tank_08_data,
	small_tank_09_data,
	small_tank_10_data,
	small_tank_11_data,
	small_tank_12_data
};

#define spr ((gfx_sprite_t**)spr_data)

/* Make Sure to define a gfx3_object_t */
gfx3_object_t tank;

int main(void)
{	
	/* Initialize graphics drawing */
	gfx_Begin();
	
	/* Set the palette for sprites */
	gfx_SetPalette(global_palette, sizeof_global_palette, 0);
	gfx_SetTransparentColor(0);
	gfx_FillScreen(255);
	
	/* Setup the gfx3_object */
	gfx3_SetObjectSprites(&tank, spr);
	
	/* Draw a transparent gfx3_object */
	gfx3_TransparentObject_NoClip(&tank, 190, 110); // Draws layered sprite.

	/* Waits for a key */
    while (!os_GetCSC());
	
	/* End graphics drawing */
	gfx_End();
}