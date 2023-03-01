#include <tice.h>
#include <graphx.h>
#include <string.h>

#include "gfx3.h"

// Setting Layers
void gfx3_SetObjectSprites(struct gfx3_object_t *gfx3_object, gfx_sprite_t **sprite_buffer)
{
	gfx3_object->layers = sprite_buffer;

	// "A scale factor of 64 represents 100% scaling.""
	gfx3_object->scale = 64;

	gfx3_object->x_offset = 0;
	gfx3_object->y_offset = 0;

	gfx3_object->angle = 255;
}

// Display Options
void gfx3_SetObjectScale(struct gfx3_object_t *gfx3_object, uint8_t scale)
{
	gfx3_object->scale = scale;
}

void gfx3_SetObjectOffset(struct gfx3_object_t *gfx3_object, uint8_t x_offset, uint8_t y_offset)
{
	gfx3_object->x_offset = x_offset;
	gfx3_object->y_offset = y_offset;
}

// Object Rotation
void gfx3_RotateObjectLayer(struct gfx3_object_t *gfx3_object, uint8_t angle, uint8_t z_index)
{
	gfx_sprite_t *temp;

	if (gfx3_object->layers[z_index] != NULL)
	{
		temp = gfx_MallocSprite(gfx3_object->layers[z_index]->width + 2, gfx3_object->layers[z_index]->height + 2);

		gfx_RotateSprite(gfx3_object->layers[z_index], temp, angle);
		free(gfx3_object->layers[z_index]);

		gfx3_object->layers[z_index] = temp;
		free(temp);
	}
}

void gfx3_RotateObject(struct gfx3_object_t *gfx3_object, uint8_t angle)
{
	gfx3_object->angle = angle;
}

// Object Display
void gfx3_Object_NoClip(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{
	uint8_t scale = gfx3_object->scale;
	uint8_t angle = gfx3_object->angle;
	gfx_sprite_t **layers = gfx3_object->layers;

	for (int i = 0; layers[i] != NULL; i++)
	{
		int sprite_x = x - (i << gfx3_object->x_offset);
		int sprite_y = y - (i << gfx3_object->y_offset);

		gfx_RotatedScaledSprite_NoClip(layers[i], sprite_x, sprite_y, angle, scale);
	}
}

void gfx3_TransparentObject_NoClip(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{
	uint8_t scale = gfx3_object->scale;
	uint8_t angle = gfx3_object->angle;
	gfx_sprite_t **layers = gfx3_object->layers;

	for (int i = 0; layers[i] != NULL; i++)
	{
		int sprite_x = x - (i << (gfx3_object->x_offset));
		int sprite_y = y - (i << (gfx3_object->y_offset));

		gfx_RotatedScaledTransparentSprite_NoClip(layers[i], sprite_x, sprite_y, angle, scale);
	}
}