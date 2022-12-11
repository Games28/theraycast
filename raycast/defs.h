#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <math.h>
#include <stdint.h>

#define PI 3.14159265
#define TWO_PI 6.28318530

#define TILE_SIZE 64

#define NUM_TEXTURES 14
#define MINIMAP_SCALE_FACTOR 0.2

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 800

#define TEXTURE_WIDTH 64
#define TEXUTRE_HEIGHT 64

#define FOV_ANGLE (60 * (PI / 180))

#define NUM_RAYS WINDOW_WIDTH
                             //640               .5775
#define Dist_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2)) //1108.51

#define FPS 60
#define FRAME_TIME_LENGTH (1000 / FPS)

typedef uint32_t color_t;

#endif