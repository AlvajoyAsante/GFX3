# GFX3
![](https://i.imgur.com/h5pquef.gif)

![](https://img.shields.io/github/commits-since/Overload02/GFX3/v1.0.0-beta.1?style=plastic) ![](https://img.shields.io/github/issues/Overload02/GFX3?style=plastic)

> *GFX3 is a Sprite Stacking library for the [CE C Toolchain](https://github.com/CE-Programming/toolchain). GFX3 allows you to effortlessly manage stacked sprites without the haste of over-coding.*

## Getting Started
*GFX3*  is designed to make it easy to create and manipulate stacked sprites in your application. With the library, you can stack multiple sprites on top of each other, adjust their position, scale, and rotation, and even make them transparent. This can help you create more complex and dynamic graphics in your application, without having to manually manipulate each sprite individually.

### How to use GFX3
* Copy the `/gfx3` folder into your project's `/src` directory.
* In your project's `main.c` file, include the GFX3 header file:
	* `#include "gfx3/gfx3.h"`
	* This will allow you to use GFX3 functions in your code.
* To create a stacked sprite, start by defining a `gfx3_object_t` struct:
  * Replace the `layers` array with your own array of `gfx_sprite_t*` pointers. You can add as many layers as you need to create the desired effect.
    * **NOTE**: Rendering will take longer the more sprites there are per layer.
```
gfx_sprite_t *layers[/*size + 1*/] = {/* Sprites */, NULL}; // make sure to include NULL at the end of the array
struct gfx3_object_t my_object;
gfx3_SetObjectSprites(my_object, layers);
```
	
* To render the sprite to the screen, use the `gfx3_Object` function:
	* `gfx3_Object(&my_object, x, y);`
	* Replace `x` and `y` with the desired screen coordinates to position the sprite.
 
*For more detailed examples and tutorials, see the `/examples` directory in the GFX3 repository.*

## Features
- ***Easy to use API*** for creating and manipulating stacked sprites.

- Support for ***stacking multiple sprites on top*** of each other, with adjustable z-ordering.

- Ability to ***adjust the position, scale, and rotation*** of individual sprites.

- ***Transparency support for individual sprites***, allowing for more complex graphics.

- ***Simple syntax*** for rendering stacked sprites to the screen.

## Demos
![](https://i.imgur.com/KYWDLLY.png) ![](https://i.imgur.com/deI4jat.png) 

![](https://i.imgur.com/airPGS3.png) ![](https://i.imgur.com/NREdUIK.png)


> *Keep up to date on the recent development by checking out the [Discord Server](https://discord.gg/xyUZgnD4UJ "New Discord Server") or [Cemetech Forums](https://www.cemetech.net/ "Cemetech Forums").*

---
 Copyright &copy; 2020 - 2023, ***Alvajoy Asante***
