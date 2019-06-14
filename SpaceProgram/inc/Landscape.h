#ifndef LANDSCAPE_H
#define LANDSCAPE_H

# include <stdio.h>
# include "ansi.h"
#include "SpaceShip.h"

# define SCREEN_WIDTH 157
# define SCREEN_HEIGHT 45
# define GROUND_HEIGHT 20

void drawLandscape();
int8_t inBounds(SpaceShip_t * p);

#endif
