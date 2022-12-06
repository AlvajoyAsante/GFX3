#ifndef GFX3_H
#define GFX3_H

#include <tice.h>
#include <graphx.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

	struct gfx3_object_t
	{
		gfx_sprite_t **layers;

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
	/** Sets the sprites layer/sprites.
	 * @param gfx3_object gfx3_object_t structure.
	 * @param sprite_buffer a array of sprites
	 * @param sizeofarray size of the array of sprites
	 */
	void gfx3_SetObjectSprites(struct gfx3_object_t *gfx3_object, gfx_sprite_t **sprite_buffer);

	// other setting
	/** Sets the scales of the sprites layers.
	 * @param gfx3_object gfx3_object_t structure.
	 * @param x_scale X scale of object.
	 * @param y_scale Y scale of object.
	 */
	void gfx3_SetObjectScale(struct gfx3_object_t *gfx3_object, uint8_t x_scale, uint8_t y_scale);

	/** Sets the layering offset.
	 * @param gfx3_object gfx3_object_t structure.
	 * @param x_offset X offset of layering object.
	 * @param y_offset Y offset of layering object.
	 */
	void gfx3_SetObjectOffset(struct gfx3_object_t *gfx3_object, uint8_t x_offset, uint8_t y_offset);

	// Rotating Index

	/** Rotates a sprite in a object.
	 * @param gfx3_object gfx3_object_t structure.
	 * @param angle angle of rotation.
	 * @param z_index the index/layer you want rotate.
	 */
	void gfx3_RotateObjectLayer(struct gfx3_object_t *gfx3_object, uint8_t angle, uint8_t z_index);

	/** rotates a full object.
	 * @param gfx3_object gfx3_object_t structure.
	 * @param angle angle of rotation.
	 */
	void gfx3_RotateObject(struct gfx3_object_t *gfx3_object, uint8_t angle);

	// Displaying Objects
	/** Prints a noclip object.
	 * @param gfx3_object gfx3_object_t structure.
	 * @param X x position of object.
	 * @param Y y position of object.
	 */
	void gfx3_Object_NoClip(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y);

	/** Prints a noclip transparent object.
	 * @param gfx3_object gfx3_object_t structure.
	 * @param X x position of object.
	 * @param Y y position of object.
	 */
	void gfx3_TransparentObject_NoClip(struct gfx3_object_t *gfx3_object, uint24_t x, uint8_t y);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif