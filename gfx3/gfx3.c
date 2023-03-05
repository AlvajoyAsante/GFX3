#include <tice.h>
#include <graphx.h>
#include <string.h>
#include <compression.h>
#include <debug.h>

#include "gfx3.h"

// Setting Layers
void gfx3_SetObjectSprites(struct gfx3_object_t *gfx3_object, gfx_sprite_t **sprites)
{
	gfx3_object->compressed = false;

	gfx3_object->layers = sprites;
	gfx3_object->compressed_layers = NULL;

	gfx3_object->padding = 0;

	gfx3_SetObjectScale(gfx3_object, 64);

	gfx3_SetObjectOffset(gfx3_object, 1, 1);

	gfx3_SetObjectAngle(gfx3_object, 255);

	gfx3_GetObjectSize(gfx3_object);
}

void gfx3_SetObjectCompressedSprites(struct gfx3_object_t *gfx3_object, unsigned char **sprites, uint16_t width, uint8_t height)
{
	gfx3_object->compressed = true;

	gfx3_object->layers = NULL;
	gfx3_object->compressed_layers = sprites;

	gfx3_object->padding = 0;

	gfx3_SetObjectCompressedSize(gfx3_object, width, height);

	gfx3_SetObjectScale(gfx3_object, 64);

	gfx3_SetObjectOffset(gfx3_object, 1, 1);

	gfx3_SetObjectAngle(gfx3_object, 255);

	gfx3_GetObjectSize(gfx3_object);
}

// Display Options
void gfx3_SetPadding(struct gfx3_object_t *gfx3_object, uint8_t padding)
{
	gfx3_object->padding = padding;
}

static void gfx3_FillSprite(gfx_sprite_t *sprite, uint8_t color)
{

	uint16_t width = sprite->width;
	uint8_t height = sprite->height;

	uint16_t size = width * height;

	for (int i = 0; i < size; i++)
	{
		sprite->data[i] = color;
	}
}

void gfx3_AddPadding(struct gfx3_object_t *gfx3_object, uint8_t amount, uint8_t color)
{
	// Nothing in the sprites or compressed sprites.
	if ((gfx3_object->layers == NULL) && (gfx3_object->compressed_layers == NULL))
		return;

	gfx_sprite_t **layers = gfx3_object->layers;
	uint8_t size = gfx3_GetLength(gfx3_object);

	uint16_t width = layers[0]->width;
	uint8_t height = layers[0]->height;

	uint16_t padded_width = width + (amount * 2);
	uint16_t padded_height = height + (amount * 2);

	// Checks if the sprite would go over limit
	if (width + amount > 255 || height + amount > 255 || amount == 0)
		return;

	gfx3_object->padding = amount;

	gfx_sprite_t **temp = (gfx_sprite_t **)malloc((size + 1) * sizeof(gfx_sprite_t *));

	for (int i = 0; i < size; i++)
	{
		/* Allocate new sprite */
		gfx_sprite_t *new_sprite = gfx_MallocSprite(padded_width, padded_height);

		gfx3_FillSprite(new_sprite, color);

		/* Center the old sprite to the new sprite */
		uint16_t x_offset = (padded_width - width) / 2;
		uint16_t y_offset = (padded_height - height) / 2;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				new_sprite->data[(y + y_offset) * padded_width + (x + x_offset)] = layers[i]->data[y * width + x];
			}
		}

		/* Store the sprite in double pointer */
		temp[i] = new_sprite;
	}

	/* Set temp to new position */
	gfx3_object->layers = temp;

	/* Get new size of object */
	gfx3_GetObjectSize(gfx3_object);
}

void gfx3_GetObjectSize(struct gfx3_object_t *gfx3_object)
{
	gfx_sprite_t **layers = gfx3_object->layers;
	uint8_t size = gfx3_GetLength(gfx3_object);
	uint8_t padding = gfx3_object->padding;

	gfx3_object->width = (layers[0]->width - padding) + (size * gfx3_object->x_offset);
	gfx3_object->height = (layers[0]->height - padding) + (size * gfx3_object->y_offset);
}

void gfx3_SetObjectScale(struct gfx3_object_t *gfx3_object, uint8_t scale)
{
	gfx3_object->scale = scale;
}

void gfx3_SetObjectOffset(struct gfx3_object_t *gfx3_object, uint8_t x_offset, uint8_t y_offset)
{
	gfx3_object->x_offset = x_offset;
	gfx3_object->y_offset = y_offset;
}

void gfx3_SetObjectAngle(struct gfx3_object_t *gfx3_object, uint8_t angle)
{
	gfx3_object->angle = angle;
}

void gfx3_SetObjectCompressedSize(struct gfx3_object_t *gfx3_object, uint16_t width, uint8_t height)
{
	gfx3_object->compressed_width = width;
	gfx3_object->compressed_height = height;
}

// Flipping Object
uint8_t gfx3_GetLength(struct gfx3_object_t *gfx3_object)
{
	int i = 0;

	if (!(gfx3_object->compressed))
	{
		gfx_sprite_t **layers = gfx3_object->layers;

		while (layers[i] != NULL)
		{
			++i;
		}
	}
	else
	{
		unsigned char **layers = gfx3_object->compressed_layers;

		while (layers[i] != NULL)
		{
			++i;
		}
	}

	return i;
}

void gfx3_FlipObject(struct gfx3_object_t *gfx3_object)
{
	// Nothing in the sprites or compressed sprites.
	if ((gfx3_object->layers == NULL) && (gfx3_object->compressed_layers == NULL))
		return;

	uint8_t size = gfx3_GetLength(gfx3_object);

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
	gfx3_object->angle += angle;
}

// Object Display
void gfx3_Object(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{
	if (gfx3_object->compressed)
		return;

	uint8_t size = gfx3_GetLength(gfx3_object);
	// places the object in the top left corner.
	uint8_t padding = gfx3_object->padding;
	x += (size * gfx3_object->x_offset) - padding;
	y += (size * gfx3_object->y_offset) - padding;

	uint8_t scale = gfx3_object->scale;
	uint8_t angle = gfx3_object->angle;
	gfx_sprite_t **layers = gfx3_object->layers;

	for (int i = 0; layers[i] != NULL; i++)
	{
		int sprite_x = x - (i * gfx3_object->x_offset);
		int sprite_y = y - (i * gfx3_object->y_offset);

		gfx_RotatedScaledSprite_NoClip(layers[i], sprite_x, sprite_y, angle, scale);
	}
}

void gfx3_TransparentObject(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{
	if (gfx3_object->compressed)
		return;

	uint8_t size = gfx3_GetLength(gfx3_object);

	// places the object in the top left corner.
	uint8_t padding = gfx3_object->padding;
	x += (size * gfx3_object->x_offset) - padding;
	y += (size * gfx3_object->y_offset) - padding;

	uint8_t scale = gfx3_object->scale;
	uint8_t angle = gfx3_object->angle;
	gfx_sprite_t **layers = gfx3_object->layers;

	for (int i = 0; layers[i] != NULL; i++)
	{
		int sprite_x = x - (i * (gfx3_object->x_offset));
		int sprite_y = y - (i * (gfx3_object->y_offset));

		gfx_RotatedScaledTransparentSprite_NoClip(layers[i], sprite_x, sprite_y, angle, scale);
	}
}

// Compressed Sprite Stacking
void gfx3_CompressedObject(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{
	if (!gfx3_object->compressed || gfx3_object->compressed_layers == NULL)
		return;

	uint8_t size = gfx3_GetLength(gfx3_object);
	// places the object in the top left corner.
	uint8_t padding = gfx3_object->padding;
	x += (size * gfx3_object->x_offset) - padding;
	y += (size * gfx3_object->y_offset) - padding;

	gfx_sprite_t *temp;
	uint8_t width = gfx3_object->compressed_width;
	uint8_t height = gfx3_object->compressed_height;
	temp = gfx_MallocSprite(width, height);

	uint8_t scale = gfx3_object->scale;
	uint8_t angle = gfx3_object->angle;
	unsigned char **layers = gfx3_object->compressed_layers;

	for (int i = 0; layers[i] != NULL; i++)
	{
		int sprite_x = x - (i * (gfx3_object->x_offset));
		int sprite_y = y - (i * (gfx3_object->y_offset));

		zx0_Decompress(temp, layers[i]);

		gfx_RotatedScaledSprite_NoClip(temp, sprite_x, sprite_y, angle, scale);
	}

	free(temp);
}

void gfx3_CompressedTransparentObject(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y)
{
	if (!gfx3_object->compressed || gfx3_object->compressed_layers == NULL)
		return;

	uint8_t size = gfx3_GetLength(gfx3_object);
	// places the object in the top left corner.
	uint8_t padding = gfx3_object->padding;
	x += (size * gfx3_object->x_offset) - padding;
	y += (size * gfx3_object->y_offset) - padding;

	gfx_sprite_t *temp;
	uint8_t width = gfx3_object->compressed_width;
	uint8_t height = gfx3_object->compressed_height;
	temp = gfx_MallocSprite(width, height);

	uint8_t scale = gfx3_object->scale;
	uint8_t angle = gfx3_object->angle;
	unsigned char **layers = gfx3_object->compressed_layers;

	for (int i = 0; layers[i] != NULL; i++)
	{
		int sprite_x = x - (i * (gfx3_object->x_offset));
		int sprite_y = y - (i * (gfx3_object->y_offset));

		zx0_Decompress(temp, layers[i]);

		gfx_RotatedScaledTransparentSprite_NoClip(temp, sprite_x, sprite_y, angle, scale);
	}

	free(temp);
}