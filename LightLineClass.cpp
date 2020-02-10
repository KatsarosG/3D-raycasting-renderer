#include "LightLineClass.h"
#include <iostream>
#include <math.h>
#define PI 3.14159265

LightLineClass::LightLineClass(int sX, int sY, int rayID, float numberOfRays, float offset) {
    startX = sX;
    startY = sY;
    float u = rayID*(90/numberOfRays)*(PI/180)+offset*0.005;
    finishX = sin(u)*(10000) + startX;
    finishY = cos(u)*(10000) + startY;
    
    length = sqrt((finishX-startX)*(finishX-startX)+(finishY-startY)*(finishY-startY));
}

int LightLineClass::getFinishX(void) {
    return finishX;
}
int LightLineClass::getFinishY(void) {
    return finishY;
}
float LightLineClass::getLength(void) {
    length = sqrt((finishX-startX)*(finishX-startX)+(finishY-startY)*(finishY-startY));
    return length;
}

void LightLineClass::setFinishX(float fX) {
    finishX = fX;
}
void LightLineClass::setFinishY(float fY) {
    finishY = fY;
}
