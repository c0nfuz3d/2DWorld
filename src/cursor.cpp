/*  This file is a part of 2DWorld - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    2DWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    2DWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of 2DWorld.  If not, see <http://www.gnu.org/licenses/>.*/

#include "cursor.h"
#include "point2f.h"
#include "object.h"
#include "game.h"

//initialize static variables
bool cursor::left_click = false;
point2f cursor::left_down =  point2f(0.0,0.0);
bool cursor::right_click = false;
point2f cursor::right_down = point2f(0.0,0.0);
bool cursor::highlighting = false;
float cursor::xmax = 0.0;
float cursor::xmin = 0.0;
float cursor::ymax = 0.0;
float cursor::ymin = 0.0;
object* cursor::left_clicked_object = new object;
int cursor::selected_object = 0;
bool cursor::left_clicked_an_object = false;
bool cursor::highlighted_objects[game::max_objects] = {false};
bool cursor::right_dragging = false;
object* cursor::right_clicked_object = new object;
bool cursor::right_clicked_an_object = false;
bool cursor::left_dragging = false;
bool cursor::grabbed_an_object=false;
point2f cursor::left_drag = point2f(0.0,0.0);
color cursor::box_color = GREEN;
point2f cursor::left_up = point2f(0.0,0.0);
point2f cursor::right_up = point2f(0.0,0.0);
point2f cursor::right_drag = point2f(0.0,0.0);

int cursor::objects_selected()
{
    int selected = 0;
    for(int i=0; i<game::max_objects; i++)
    {
        if(highlighted_objects[i])
            selected++;
    }
    return selected;
}

void cursor::set_boundaries()//boundaries of the selection box
{
    xmin= left_down.x;
    xmax= left_drag.x;
    ymin= left_down.y;
    ymax= left_drag.y;
}

void cursor::selection_box()//this is the box that is created when user clicks and drags
{
    if(highlighting)
    {
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(box_color.r,box_color.g,box_color.b,0.5);
        glBegin(GL_QUADS);

        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner

        glEnd();
    }
}
