#include "WallLineClass.h"
#include <iostream>


WallLineClass::WallLineClass(int sX, int sY, int fX, int fY) {
    startX = sX;
    startY = sY;
    finishX = fX;
    finishY = fY;
}
void WallLineClass::setStartX(float sX) {
    startX = sX;
}
void WallLineClass::setStartY(float sY) {
    startX = sY;
}
void WallLineClass::setFinishX(float fX) {
    finishX = fX;
}
void WallLineClass::setFinishY(float fY) {
    finishY = fY;
}

int WallLineClass::getStartX(void) {
    return startX;
}
int WallLineClass::getStartY(void) {
    return startY;
}
int WallLineClass::getFinishX(void) {
    return finishX;
}
int WallLineClass::getFinishY(void) {
    return finishY;
}