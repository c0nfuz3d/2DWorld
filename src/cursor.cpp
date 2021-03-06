/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

#include "cursor.h"
#include "window.h"
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include <iostream>
//initialize static variables
color cursor::box_color = GREEN;
point2i cursor::left_up = point2i(0.0,0.0);
point2i cursor::right_up = point2i(0.0,0.0);
point2i cursor::left_drag = point2i(0.0,0.0);
point2i cursor::right_drag = point2i(0.0,0.0);
point2i cursor::passive = point2i(0.0,0.0);
point2i cursor::left_down = point2i(0.0,0.0);
point2i cursor::right_down = point2i(0.0,0.0);
interactive_object* cursor::left_clicked_object = new interactive_object();
interactive_object* cursor::right_clicked_object = new interactive_object();
bool cursor::left_clicking = false;
bool cursor::right_clicking = false;
bool cursor::highlighting = false;
bool cursor::highlighting_enabled = false;
bool cursor::left_dragging = false;
bool cursor::right_dragging = false;
std::map<int,interactive_object*> cursor::selected_objects;
int cursor::xmax = 0;
int cursor::xmin = 0;
int cursor::ymax = 0;
int cursor::ymin = 0;
int cursor::selected_object = 1;

int cursor::objects_selected()
{
    return selected_objects.size();
}

void cursor::calc_boundaries()//boundaries of the selection box
{
    xmin = left_down.x;
    xmax = left_drag.x;
    ymin = left_down.y;
    ymax = left_drag.y;
}

void cursor::render_box()//this is the box that is created when user clicks and drags
{
    if(highlighting_enabled && highlighting)
    {
        bool blending = false;
        if(glIsEnabled(GL_BLEND))
            blending = true;
        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(box_color.r,box_color.g,box_color.b,0.5);
        glBegin(GL_QUADS);
        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner
        glEnd();
        if(!blending)
        glDisable(GL_BLEND);
    }
}

void cursor::reset()
{
    box_color = GREEN;
    passive.set(0,0);
    left_down.set(0,0);
    right_down.set(0,0);
    left_up.set(0,0);
    right_up.set(0,0);
    left_drag.set(0,0);
    right_drag.set(0,0);
    left_clicked_object = new interactive_object();
    right_clicked_object = new interactive_object();
    left_clicking = false;
    right_clicking = false;
    left_dragging = false;
    right_dragging = false;
    highlighting = false;
    highlighting_enabled = false;
    selected_objects.clear();
    selected_object = 1;
    xmax = 0;
    xmin = 0;
    ymax = 0;
    ymin = 0;
}
