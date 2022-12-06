#include <tice.h>
#include <graphx.h>
#include <string.h>
#include <debug.h>

#include "gfx3.h"

/* Setting Layers */
void gfx3_SetObjectSprites(gfx3_object_t *gfx3_object, gfx_sprite_t **sprites)
{
	if (gfx3_object != NULL && sprites != NULL){
		gfx3_object->layers = sprites;	
		gfx3_SetObjectScale(gfx3_object, 1, 1);
		gfx3_SetObjectOffset(gfx3_object, 1, 1);
	}
}

/* Display Options */
void gfx3_SetObjectScale(gfx3_object_t *gfx3_object, uint8_t x_scale, uint8_t y_scale)
{
	if (gfx3_object != NULL) {
		gfx3_object->x_scale = x_scale;
		gfx3_object->y_scale = y_scale;
	}
}

void gfx3_SetObjectOffset(gfx3_object_t *gfx3_object, int x_offset, int y_offset)
{
	if (gfx3_object != NULL) {
		gfx3_object->x_offset = x_offset;
		gfx3_object->y_offset = y_offset;
	}
}

/* Object Rotation */
void gfx3_RotateObjectLayer(gfx3_object_t *gfx3_object, uint8_t angle, uint8_t z_index)
{
	gfx_sprite_t *temp;
	if (gfx3_object != NULL) {
		if (gfx3_object->layers[z_index] != NULL) {
			temp = gfx_MallocSprite(gfx3_object->layers[z_index]->width, gfx3_object->layers[z_index]->height);
			gfx3_object->layers[z_index] = gfx_RotateScaleSprite(gfx3_object->layers[z_index], temp, angle, 126);	
			free(temp);
		}
	}
}

void gfx3_RotateObject(gfx3_object_t *gfx3_object, uint8_t angle)
{
	for (uint8_t i = 0; ; i++) {
		if (gfx3_object->layers[i] != NULL) {
			gfx3_RotateObjectLayer(gfx3_object, angle, i);
		}else return;
	}
}

/* Object Display */
void gfx3_Object_NoClip(const gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{	
	if (gfx3_object == NULL || gfx3_object->layers == NULL) return;
	
	int scale[2] = {gfx3_object->x_scale, gfx3_object->y_scale};
	int offset[2] = {gfx3_object->x_offset, gfx3_object->y_offset};
	
	for (int i = 0; ; i++) {
		if (gfx3_object->layers[i] != NULL) {
			gfx_ScaledSprite_NoClip(gfx3_object->layers[i], 
									x - (i * offset[0]), 
									y - (i * offset[1]), 
									scale[0], 
									scale[1]);
		}else break;
	}
}

void gfx3_TransparentObject_NoClip(const gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{	
	if (gfx3_object == NULL || gfx3_object->layers == NULL) return;
	
	int scale[2] = {gfx3_object->x_scale, gfx3_object->y_scale};
	int offset[2] = {gfx3_object->x_offset, gfx3_object->y_offset};
	
	for (int i = 0; ; i++) {
		if (gfx3_object->layers[i] != NULL) {
			gfx_ScaledTransparentSprite_NoClip(gfx3_object->layers[i],
												x - (i * offset[0]), 
												y - (i * offset[1]), 
												scale[0], 
												scale[1]);
		}else break;
	}
}