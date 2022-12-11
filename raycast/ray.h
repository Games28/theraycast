#ifndef RAY_H
#define RAY_H
#include <stdbool.h>
#include <limits.h>
#include "defs.h"
#include "player.h"
#include <float.h>
#include "utils.h"




typedef struct {
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;

	// multilevel attempt
	float vertX[30];
	float vertY[30];
	float hertX[30];
	float hertY[30];
	int WallDistances[30];
	int wallHeight[30];
	//end
	bool wasHitVertical;
	bool firstwall;
	int texture;

	
}ray_t;



extern ray_t rays[NUM_RAYS];
//extern IntersectInfo wallHitInfo[NUM_RAYS * 2];


void castRay(float rayAngle, int stripId);
void castAllRays(void);
void renderMapRays(void);


#endif
