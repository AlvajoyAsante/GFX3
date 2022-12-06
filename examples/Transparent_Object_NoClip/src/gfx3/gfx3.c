#include <string.h>
// #include <graphx.h>
#include "gfx3.h"

// Setting Layers
void gfx3_SetObjectSprites(struct gfx3_object_t *gfx3_object, gfx_sprite_t *sprite_buffer[], int sizeofarray)
{
	for (int i = 0; i < sizeofarray; i++){
		gfx3_object->layers[i] = sprite_buffer[i];
	}
	
	gfx3_object->max_index = sizeofarray;
}


// Display Options
void gfx3_ObjectInit(struct gfx3_object_t *gfx3_object)
{
	gfx3_object->x_scale = 1;
	gfx3_object->y_scale = 1;
	gfx3_object->x_offset = 0;
	gfx3_object->y_offset = 1;
}

void gfx3_SetObjectScale(struct gfx3_object_t *gfx3_object, uint8_t x_scale, uint8_t y_scale)
{
	gfx3_object->x_scale = x_scale;
	gfx3_object->y_scale = y_scale;
}

void gfx3_SetObjectOffset(struct gfx3_object_t *gfx3_object, uint8_t x_offset, uint8_t y_offset)
{
	gfx3_object->x_offset = x_offset;
	gfx3_object->y_offset = y_offset;
}

// Object Rotation
void gfx3_RotateObjectLayer(struct gfx3_object_t *gfx3_object, uint8_t angle, uint8_t z_index)
{
	gfx_sprite_t *temp_layer;
	
	gfx3_object->layers[z_index] = gfx_RotateSprite(gfx3_object->layers[z_index], temp_layer, angle);
}

void gfx3_RotateObject(struct gfx3_object_t *gfx3_object, uint8_t angle)
{
	for (uint8_t i = 0; i < gfx3_object->max_index; i++){ // rotates every layer.
		gfx3_RotateObjectLayer(gfx3_object, angle, i);
	}
}

// Object Display
void gfx3_Object_NoClip(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{	
	gfx_sprite_t *temp_layer;
	int scale[2] = {gfx3_object->x_scale, gfx3_object->y_scale};
	int offset[2] = {gfx3_object->x_offset, gfx3_object->y_offset};
	int max_index = gfx3_object->max_index;
	
	for (int i = 0; i < max_index; i++) {
		temp_layer = gfx3_object->layers[i];
		gfx_ScaledSprite_NoClip(temp_layer, x - (i * offset[0]), y - (i * offset[1]), scale[0], scale[1]);
	}
}

void gfx3_TransparentObject_NoClip(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{	
	gfx_sprite_t *temp_layer;
	int scale[2] = {gfx3_object->x_scale, gfx3_object->y_scale};
	int offset[2] = {gfx3_object->x_offset, gfx3_object->y_offset};
	int max_index = gfx3_object->max_index;
	
	for (int i = 0; i < max_index; i++) {
		temp_layer = gfx3_object->layers[i];
		gfx_ScaledTransparentSprite_NoClip(temp_layer, x - (i * offset[0]), y - (i * offset[1]), scale[0], scale[1]);
	}
}