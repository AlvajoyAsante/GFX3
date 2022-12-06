/*
** GFX3 LIBRARY BY ALVAJOY123.
** LICENSE : MIT
**
** Copyright 2020 - 2021 Alvajoy (Alvajoy123) A.
**
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
** (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, 
** publish, distribute, sub-license, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do 
** so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
** FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
** WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef GFX3_H
#define GFX3_H

#include <tice.h>
#include <graphx.h>

struct gfx3_object_t{
	// Sprite layers allocated based on sprite max_index
	gfx_sprite_t *layers[35];
	// Amount of sprite layers.
	uint8_t max_index;
	
	// x and y offset of stacking
	int x_offset;
	int y_offset;
	
	// x and y scale of sprite.
	uint8_t x_scale;
	uint8_t y_scale;
	
	// rotation angle.
	uint8_t angle;
};

// Active Objects
/* Sets the sprites layer/sprites.
** @param gfx3_object gfx3_object_t structure.
** @param sprite_buffer a array of sprites
** @param sizeofarray size of the array of sprites
*/
void gfx3_SetObjectSprites(struct gfx3_object_t *gfx3_object, gfx_sprite_t *sprite_buffer[], int sizeofarray);

// other settings 
/* Sets up variables in gfx3_object (Do this before rendering an object!).
** @param gfx3_object gfx3_object_t structure.
*/
void gfx3_ObjectInit(struct gfx3_object_t *gfx3_object);

/* Sets the scales of the sprites layers.
** @param gfx3_object gfx3_object_t structure.
** @param x_scale X scale of object.
** @param y_scale Y scale of object.
*/
void gfx3_SetObjectScale(struct gfx3_object_t *gfx3_object, uint8_t x_scale, uint8_t y_scale);

/* Sets the layering offset.
** @param gfx3_object gfx3_object_t structure.
** @param x_offset X offset of layering object.
** @param y_offset Y offset of layering object.
*/
void gfx3_SetObjectOffset(struct gfx3_object_t *gfx3_object, uint8_t x_offset, uint8_t y_offset);


// Rotating Index
/* Rotates a sprite in a object.
** @param gfx3_object gfx3_object_t structure.
** @param angle angle of rotation.
** @param z_index the index/layer you want rotate.
*/
void gfx3_RotateObjectLayer(struct gfx3_object_t *gfx3_object, uint8_t angle, uint8_t z_index);
/* rotates a full object.
** @param gfx3_object gfx3_object_t structure.
** @param angle angle of rotation.
*/
void gfx3_RotateObject(struct gfx3_object_t *gfx3_object, uint8_t angle);

// Displaying Objects
/* Prints a noclip object.
** @param gfx3_object gfx3_object_t structure.
** @param X x position of object.
** @param Y y position of object.
*/
void gfx3_Object_NoClip(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y);
/* Prints a noclip transparent object.
** @param gfx3_object gfx3_object_t structure.
** @param X x position of object.
** @param Y y position of object.
*/
void gfx3_TransparentObject_NoClip(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y);

#endif