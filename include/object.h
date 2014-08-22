#ifndef OBJECT_H
#define OBJECT_H
#include "color.h"
#include "point2f.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class object
{
    public:
    static int object_no;
    char* name;
    int number;
    point2f current;
    point2f rest;//resting point
    float rotation;
    float width, height;
    color current_color;//RGB values
    color prev_color;
    bool visible;
    float xmax,xmin,ymax,ymin;
    void set_boundaries();//calculates the max's and mins
    void render();//draws the object
    void undo_color();//sets the current color to the previous
    void rotate(float angle);
    int get_radius();//calculates a radius from the width and height
    object();//constructs an object
    object(float x, float y, float w, float h, color c);
};
#endif // OBJECT_H
