#include "wall.h"


void changeColorIntensity(color_t* color, float factor)
{
	color_t a = (*color & 0xFF000000);
	color_t r = (*color & 0x00FF0000) * factor;
	color_t g = (*color & 0x0000FF00) * factor;
	color_t b = (*color & 0x000000FF) * factor;
	
	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

void renderWallProjection(void) {

	bool topwallhit = false;
	for (int x = 0; x < NUM_RAYS; x++) {
		float prepDistance = rays[x].distance * cos(rays[x].rayAngle - player.rotationAngle);
		
		float WallHeight = (TILE_SIZE / prepDistance * Dist_PROJ_PLANE);

		int wallStripHeight = (int)WallHeight;

		int wallTopY,wallBottomY;
		
		wallTopY = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
		
		wallBottomY = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
		//multilevel attempt
		for (int i = 0; i < rays[x].wallHeight[i]; i++)
		{
			if (i > rays[x].wallHeight[i])
				break;
			float newprepDist = rays[x].WallDistances[i] * cos(rays[x].rayAngle - player.rotationAngle);
			float newWallHeight = (TILE_SIZE / newprepDist * Dist_PROJ_PLANE);
			int newwallTopY = (WINDOW_HEIGHT / 2) - (newWallHeight / 2) - (rays[x].wallHeight[i] - 1) * newWallHeight;

			int newwallBottomY = (WINDOW_HEIGHT / 2) + (newWallHeight / 2);

			if (wallTopY < newwallTopY)
			{
				wallTopY = newwallTopY;
				wallBottomY = newwallBottomY;
				topwallhit = true;
			}
			else {
				topwallhit = false;
			}
		}
		//end
		wallTopY = wallTopY < 0 ? 0 : wallTopY;
		wallBottomY = wallBottomY > WINDOW_HEIGHT ? WINDOW_HEIGHT : wallBottomY;
		int nHalfWindowHeight = WINDOW_HEIGHT / 2;
		float fPlayerH = TILE_SIZE / 2.0f;
		float fFoV = 60.0f;
		float fAngleStep = fFoV / (float)NUM_RAYS;
		float fViewAngle = (float)(x - (NUM_RAYS / 2)) * fAngleStep;
		float fCurAngle = (player.rotationAngle * 180.0f / PI) + fViewAngle;
		float fPlayerX = player.x;
		float fPlayerY = player.y;
		float fCosCurAngle = cos(fCurAngle * PI / 180.0f);
		float fSinCurAngle = sin(fCurAngle * PI / 180.0f);
		float fCosViewAngle = cos(fViewAngle * PI / 180.0f);

		int textureOffSetX;
		if (rays[x].wasHitVertical) {
			textureOffSetX = (int)rays[x].wallHitY % TILE_SIZE;

		}
		else {

			textureOffSetX = (int)rays[x].wallHitX % TILE_SIZE;
		}

		//get correct texture id for map content
		int texNum = rays[x].texture - 1;
		
		int texture_width = upng_get_width(textures[texNum]);
		int texture_height = upng_get_height(textures[texNum]);

		

		for (int y = 0; y < WINDOW_HEIGHT; y++)
		{
			if (y < wallTopY)
			{ 
				

				//multilevel attempt
					if (topwallhit)
					{
						int distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
						int textureOffSetY = distanceFromTop * ((float)texture_height / wallStripHeight);

						color_t* wallTextureBuffer = (color_t*)upng_get_buffer(textures[texNum]);
						color_t texelColor = wallTextureBuffer[(texture_width * textureOffSetY) + textureOffSetX];
						drawPixel(x, y, texelColor);
					} //end
					else
					{
						float fFloorProjDistance = ((fPlayerH / (float)(nHalfWindowHeight - y)) * Dist_PROJ_PLANE) / fCosViewAngle;
						float fFloorProjX = fPlayerX + fFloorProjDistance * fCosCurAngle;
						float fFloorProjY = fPlayerY + fFloorProjDistance * fSinCurAngle;
						int nSampleX = (int)(fFloorProjX) % TILE_SIZE;
						int nSampleY = (int)(fFloorProjY) % TILE_SIZE;
						color_t* wallTextureBuffer = (color_t*)upng_get_buffer(textures[4]);
						color_t texelColor = wallTextureBuffer[(texture_width * nSampleY) + nSampleX];

						//drawPixel(x, y, texelColor);
						drawPixel(x, y, 0xff444444);
					}
				
			}
			else if (y > wallBottomY)
			{
				
				float fFloorProjDistance = ((fPlayerH / (float)(y - nHalfWindowHeight)) * Dist_PROJ_PLANE) / fCosViewAngle;
				float fFloorProjX = fPlayerX + fFloorProjDistance * fCosCurAngle;
				float fFloorProjY = fPlayerY + fFloorProjDistance * fSinCurAngle;
				int nSampleX = (int)(fFloorProjX) % TILE_SIZE;
				int nSampleY = (int)(fFloorProjY) % TILE_SIZE;
				color_t* wallTextureBuffer = (color_t*)upng_get_buffer(textures[5]);
				color_t texelColor = wallTextureBuffer[(nSampleY * texture_width) + nSampleX];

				drawPixel(x, y, texelColor);
				//drawPixel(x, y, 0xff777777);
			}
			else
			{
				int distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
				int textureOffSetY = distanceFromTop * ((float)texture_height / wallStripHeight);

				color_t* wallTextureBuffer = (color_t*)upng_get_buffer(textures[texNum]);
				color_t texelColor = wallTextureBuffer[(texture_width * textureOffSetY) + textureOffSetX];
				drawPixel(x, y, texelColor);

				if (rays[x].wasHitVertical)
				{
					changeColorIntensity(&texelColor, 0.7);
				}

				drawPixel(x, y, texelColor);
			}
		}
	}


}

void calculateBottomAndTop(float wallDistance, int wallHight, int* wallCeil, int* wallFloor)
{
	int nsliceHeight = (int)((1.0f / wallDistance) * Dist_PROJ_PLANE);
	*(wallCeil) = (WINDOW_HEIGHT / 2) - (wallHight / 2.0f) - (wallHight - 1) * wallHight;
	*(wallFloor) = (WINDOW_HEIGHT / 2) + (wallHight / 2.0f);
}

void walltest(void)
{
	for (int i = 0; i < NUM_RAYS; i++) {
		
	}
}
