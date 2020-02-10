#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include "WallLineClass.h"
#include "WallLineClass.cpp"
#include "LightLineClass.h"
#include "LightLineClass.cpp"

class MouseClass {
    public:
        int x;
        int y;
        int lastX;
        int lastY;
};
MouseClass mouse;

class playerClass {
    public:
        float x;
        float y;
        float forward;
        float side;
};
playerClass player;

//start render window
int height = 1080;
int width = 1920;
sf::RenderWindow window(sf::VideoMode(width, height), "Ray Casting");

sf::Color brightness(100,100,100);
void drawLine(int sX, int sY, int fX, int fY) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(sX, sY), brightness),
        sf::Vertex(sf::Vector2f(fX, fY), brightness)
    };

    window.draw(line, 2, sf::Lines);
}

//has to be summultiple of 360:
int numberOfRays = width;
float look;

int numberOfWalls;
bool drawingMode = false;
bool light = true;
bool lockMouse = true;
int main() {
    window.setFramerateLimit(60);
    std::vector<WallLineClass> wallClass;
    std::vector<LightLineClass> lightClass;

    player.x = width/2;    player.y = height/2;
    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        //get mouse pos
        sf::Vector2i tempxy = sf::Mouse::getPosition(window);
        mouse.x = tempxy.x;    mouse.y = tempxy.y;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            while (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            }
            if (lockMouse == true) {
                lockMouse = false;
            } else
            {
                lockMouse = true;
            }
            
        }
        if (lockMouse == true && abs(mouse.x - width/2) > 0) {
            sf::Mouse::setPosition(sf::Vector2i(width/2,height/2), window);
        }
        float tempLook = 0;
        if (lockMouse == true) {
            tempLook = mouse.x - width/2;
        }
        float look = look - tempLook;

        //set player pos
        float u = (((360*look)/1259)+45)*(PI/180);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.forward = 1;
            player.x += sin(u)*player.forward;
            player.y += cos(u)*player.forward;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player.forward = -1;
            player.x += sin(u)*player.forward;
            player.y += cos(u)*player.forward;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.side = +1;
            player.x += sin(u+PI/2)*player.side;
            player.y += cos(u+PI/2)*player.side;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.side = -1;
            player.x += sin(u+PI/2)*player.side;
            player.y += cos(u+PI/2)*player.side;
        }

        //if (mouse.x > 0 && mouse.x < width && mouse.y > 0 && mouse.y < height) {
        if (1 == 1) {
            //clear screen
            window.clear(sf::Color::Black);


            //toggle drawing mode on/of
            if (mouse.x > 0 && mouse.x < width && mouse.y > 0 && mouse.y < height) {
                if (sf:: Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (mouse.x >= 0 && mouse.x <= width && mouse.y >= 0 && mouse.y <= height) {
                        if (drawingMode == false) {
                            while (sf:: Mouse::isButtonPressed(sf::Mouse::Left)) {
                            }
                            mouse.lastX = mouse.x;
                            mouse.lastY = mouse.y;
                            drawingMode = true;
                        } else if (drawingMode == true) {
                            while (sf:: Mouse::isButtonPressed(sf::Mouse::Left)) {
                            }
                            //when done creating line save line
                            drawingMode = false;
                            WallLineClass newWall(mouse.lastX, mouse.lastY, mouse.x, mouse.y);
                            wallClass.push_back(newWall);
                        }
                    }
                }
                if (sf:: Mouse::isButtonPressed(sf::Mouse::Right)) {
                    if (mouse.x >= 0 && mouse.x <= width && mouse.y >= 0 && mouse.y <= height) {
                        if (light == false) {
                            while (sf:: Mouse::isButtonPressed(sf::Mouse::Right)) {
                            }
                            light = true;
                        } else if (light == true) {
                            while (sf:: Mouse::isButtonPressed(sf::Mouse::Right)) {
                            }
                            light = false;
                        }
                    }
                }
            }
            //draw walls
            if (lockMouse == false) {
                numberOfWalls = wallClass.size();
                for (int i = 0; i < numberOfWalls; i++) {
                    drawLine(wallClass[i].getStartX(), wallClass[i].getStartY(), wallClass[i].getFinishX(), wallClass[i].getFinishY());
                }
            }
            //draw now drawn wall
            if (drawingMode == true) {
                drawLine(mouse.x, mouse.y, mouse.lastX, mouse.lastY);
            }

            //make rays
            for (int i = 0; i < numberOfRays; i++) {
                LightLineClass newRay(player.x, player.y, i, numberOfRays, look);
                lightClass.push_back(newRay);
            }
            //////////////////////////////////////////////////////
            //find intersections
            for (int i = 0; i < numberOfRays; i++) {
                for (int n = 0; n < numberOfWalls; n++) {
                    float p0x, p0y,   p1x, p1y;
                    float p2x, p2y,   p3x, p3y;
                    p0x = player.x;                      p0y = player.y;
                    p1x = lightClass[i].getFinishX();   p1y = lightClass[i].getFinishY();
                    p2x = wallClass[n].getStartX();     p2y = wallClass[n].getStartY();
                    p3x = wallClass[n].getFinishX();    p3y = wallClass[n].getFinishY();

                    float s1_x, s1_y, s2_x, s2_y;
                    s1_x = p1x - p0x;     s1_y = p1y - p0y;
                    s2_x = p3x - p2x;     s2_y = p3y - p2y;

                    float s, t;
                
                    s = (-s1_y * (p0x - p2x) + s1_x * (p0y - p2y)) / (s1_x * s2_y - s2_x * s1_y);
                    t = ( s2_x * (p0y - p2y) - s2_y * (p0x - p2x)) / (s1_x * s2_y -s2_x * s1_y);
                    
                    if (s > 0 && s < 1 && t > 0 && t < 1) {
                        //collision detected
                        float ix = p0x + (t * s1_x);
                        float iy = p0y + (t * s1_y);
                            
                        lightClass[i].setFinishX(ix);
                        lightClass[i].setFinishY(iy);
                    }
                    
                }

            }
            
            //draw rays
            if (lockMouse == false) {
                if (light == true) {
                    //brightness.r = 255;
                    //brightness.g = 255;
                    //brightness.b = 255;
                    for (int i = 0; i < numberOfRays; i++) {
                        drawLine(player.x, player.y, lightClass[i].getFinishX(), lightClass[i].getFinishY());
                    }
                }
            }
            //render
            if (lockMouse == true){
                for (int i = numberOfRays-1; i > 0; i--) {
                    if (lightClass[i].getLength() < height/2.3) {
                        brightness.r = 255 - (255*lightClass[i].getLength()) / (height/2.3);
                        brightness.g = brightness.r;
                        brightness.b = brightness.r;

                        drawLine(width - i, height - lightClass[i].getLength(), width - i, lightClass[i].getLength());
                    }
                }
            }
            
            
            lightClass.clear();
        
            window.display();
        }

    }
}