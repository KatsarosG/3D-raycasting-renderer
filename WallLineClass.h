#include <iostream>
using namespace std;

#ifndef WALLLINECLASS_H
#define WALLLINECLASS_H


class WallLineClass {
    public:
        void setStartX(float sX);
        void setStartY(float sY);
        void setFinishX(float fX);
        void setFinishY(float fY);

        int getStartX(void);
        int getStartY(void);
        int getFinishX(void);
        int getFinishY(void);

        WallLineClass(int sX, int sY, int fX, int fY);
    private:
        float startX;
        float startY;
        float finishX;
        float finishY;
};

#endif