#include "player.h"

player_t player = {

	.x = WINDOW_WIDTH / 2,
	.y = WINDOW_HEIGHT / 2,
	.width = 1,
	.height = 1,
	.turnDirection = 0,
	.walkDirection = 0,
	.rotationAngle = PI/ 2,
	.walkSpeed = 100,
	.turnSpeed = 45 * (PI / 180),
	.lookUpDown = 0,
	.playerLookAngle = 45 * (PI / 180),
	.lookUpDown = 0
};

void movePlayer(float deltaTime) {
	player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;
	normalizeAngle(&player.rotationAngle);

	float moveStep = player.walkDirection * player.walkSpeed * deltaTime;

	float newPlayerX = player.x + cos(player.rotationAngle) * moveStep;
	float newPlayerY = player.y + sin(player.rotationAngle) * moveStep;

	//wall collision
	if (!mapHasWallAt(newPlayerX, newPlayerY)) {
		player.x = newPlayerX;
		player.y = newPlayerY;
	}
}

void renderMapPlayer(void) {
	
	drawRect(
		player.x * MINIMAP_SCALE_FACTOR,
		player.y * MINIMAP_SCALE_FACTOR, 
		player.width * MINIMAP_SCALE_FACTOR,
		player.height * MINIMAP_SCALE_FACTOR,
		0x0000ffff
	);
	

	
}
