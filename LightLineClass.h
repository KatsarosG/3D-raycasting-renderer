#include <iostream>
using namespace std;

#ifndef LIGHTLINECLASS_H
#define LIGHTLINECLASS_H

class LightLineClass {
    public:
        LightLineClass(int sX, int sY, int rayID, float numberOfRays, float offset);

        int getFinishX(void);
        int getFinishY(void);
        float getLength(void);

        void setFinishX(float fx);
        void setFinishY(float fy);
    private:
        int startX;
        int startY;
        int rayID;
        float length;

        float finishX;
        float finishY;
};

#endif