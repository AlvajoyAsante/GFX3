#include <tice.h>
#include <graphx.h>
#include <string.h>
#include <compression.h>

#include "gfx3.h"

// Setting Layers
void gfx3_SetObjectSprites(struct gfx3_object_t *gfx3_object, gfx_sprite_t **sprites)
{
	gfx3_object->compressed = false;

	gfx3_object->layers = sprites;
	gfx3_object->compressed_layers = NULL;

	// "A scale factor of 64 represents 100% scaling.""
	gfx3_object->scale = 64;

	gfx3_object->x_offset = 0;
	gfx3_object->y_offset = 0;

	gfx3_object->angle = 255;
}

void gfx3_SetObjectCompressedSprites(struct gfx3_object_t *gfx3_object, unsigned char **sprites, uint16_t width, uint8_t height)
{
	gfx3_object->compressed = true;

	gfx3_object->layers = NULL;
	gfx3_object->compressed_layers = sprites;

	gfx3_object->width = width;
	gfx3_object->height = height;

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

// Flipping Object
static uint8_t gfx3_GetLayersLength(struct gfx3_object_t *gfx3_object)
{
	int i = 0;

	if (!(gfx3_object->compressed))
	{
		gfx_sprite_t ** layers = gfx3_object->layers;

		for (i = 0; layers[i] != NULL; ++i);
	}
	else
	{
		unsigned char **layers = gfx3_object->compressed_layers;

		for (i = 0; layers[i] != NULL; ++i);
	}

	return i;
}

void gfx3_FlipObject(struct gfx3_object_t *gfx3_object)
{
	// if ((gfx3_object->layers == NULL) && (gfx3_object->compressed_layers == NULL)) return; // Nothing in the sprites / compressed sprites

	uint8_t size = gfx3_GetLayersLength(gfx3_object);

	if (!(gfx3_object->compressed))
	{
		gfx_sprite_t **temp = (gfx_sprite_t **)malloc((size + 1) * sizeof(gfx_sprite_t *));

		// not compressed

		for (int i = size - 1; i >= 0; i--)
		{
			temp[(size - i) - 1] = gfx3_object->layers[i];
		}

		temp[size] = NULL;

		gfx3_object->layers = temp;
	}
	else
	{
		// not compressed
		unsigned char **temp = (unsigned char **)malloc((size + 1) * sizeof(unsigned char *));

		for (int i = size - 1; i >= 0; i--)
		{
			temp[(size - i) - 1] = gfx3_object->compressed_layers[i];
		}

		temp[size] = NULL;

		gfx3_object->compressed_layers = temp;
	}
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
void gfx3_Object(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{
	if (gfx3_object->compressed)
		return;

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

void gfx3_TransparentObject(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{
	if (gfx3_object->compressed)
		return;

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

// Compressed Sprite Stacking
void gfx3_CompressedObject(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{
	if (!gfx3_object->compressed)
		return;

	gfx_sprite_t *temp;
	uint8_t width = gfx3_object->width;
	uint8_t height = gfx3_object->height;
	temp = gfx_MallocSprite(width, height);

	uint8_t scale = gfx3_object->scale;
	uint8_t angle = gfx3_object->angle;
	unsigned char **layers = gfx3_object->compressed_layers;

	for (int i = 0; layers[i] != NULL; i++)
	{
		int sprite_x = x - (i << (gfx3_object->x_offset));
		int sprite_y = y - (i << (gfx3_object->y_offset));

		zx0_Decompress(temp, layers[i]);

		gfx_RotatedScaledSprite_NoClip(temp, sprite_x, sprite_y, angle, scale);
	}

	free(temp);
}

void gfx3_CompressedTransparentObject(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{

	if (!gfx3_object->compressed)
		return;

	gfx_sprite_t *temp;
	uint8_t width = gfx3_object->width;
	uint8_t height = gfx3_object->height;
	temp = gfx_MallocSprite(width, height);

	uint8_t scale = gfx3_object->scale;
	uint8_t angle = gfx3_object->angle;
	unsigned char **layers = gfx3_object->compressed_layers;

	for (int i = 0; layers[i] != NULL; i++)
	{
		int sprite_x = x - (i << (gfx3_object->x_offset));
		int sprite_y = y - (i << (gfx3_object->y_offset));

		zx0_Decompress(temp, layers[i]);

		gfx_RotatedScaledTransparentSprite_NoClip(temp, sprite_x, sprite_y, angle, scale);
	}

	free(temp);
}