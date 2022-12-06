#include <tice.h>
#include <math.h>
#include <graphx.h>
#include <keypadc.h>

/* Sprite header file */
#include "gfx/car/CARSPR.h"

/* Makes sure to include the library */
#include "gfx3/gfx3.h"

/* Create a sprite array and fill it with layers (make sure array is defined) */
gfx_sprite_t *car_layers[6] = {temp_layers1, temp_layers2, temp_layers3, temp_layers4, temp_layers5, temp_layers6};

/* Create a array to hold your object */
struct gfx3_object_t car_object;
uint8_t rotate = 1;

void draw_object(void);
void draw_object_update(void);

void main(void)
{
	
	gfx_Begin();
	
	/* Allows for smooth drawing. */
	gfx_SetDraw(1); // Very important!!
	
	/* Set Palette if there is any */
	gfx_SetPalette(palette, sizeof_palette, 0);
	
	/* Use the to set the sprites/layers to object array */
	gfx3_SetObjectSprites(&car_object, car_layers, 6);
	gfx3_ObjectInit(&car_object);
	gfx3_SetObjectScale(&car_object, 2, 2);
	
	while (kb_Data[6] != kb_Clear){
		kb_Scan();
		gfx_FillScreen(0xFF);
		
		draw_object_update();
		draw_object();
		
		gfx_Blit(1); // Very Important!! (Used for buffering)
		rotate++;
		free(&car_object);
	}

	gfx_End();
	return;
}

void draw_object(void)
{
	/* Display a transparent object */
	gfx3_TransparentObject_NoClip(&car_object, (320/2), (240/2));
	return;
}

void draw_object_update(void)
{
	if (rotate < 254){
		gfx3_SetObjectSprites(&car_object, car_layers, 6);
		gfx3_RotateObject(&car_object, rotate);
	}else rotate = 1;
	return;
}


