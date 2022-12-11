#ifndef WALL_H
#define WALL_H
#include "defs.h"
#include "player.h"
#include "ray.h"
#include "graphics.h"
#include "textures.h"


void changeColorIntensity(color_t* color, float factor);
void renderWallProjection(void);
void calculateBottomAndTop(float wallDistance, int wallHight, int* wallCeil, int* wallFloor);
void walltest(void);

#endif // !WALL_H
