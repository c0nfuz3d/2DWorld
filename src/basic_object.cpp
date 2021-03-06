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

#include "basic_object.h"
#include "window.h"
#include "utilities.h"
#include "graphics.h"
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
#include <sstream>
#include <fstream>
#include <math.h>

//initialize static variables
int basic_object::total_objects=0;
point2i basic_object::default_position = point2i(window::center.x,window::center.y);

int basic_object::get_number()
{
    return number;
}

std::string basic_object::get_type()
{
    return "basic object";
}

point2f basic_object::get_position()
{
    return position;
}

point2f* basic_object::get_positionptr()
{
    return &position;
}

float basic_object::get_x()
{
    return position.x;
}

float basic_object::get_y()
{
    return position.y;
}

float basic_object::get_rotation()
{
    return rotation;
}

int basic_object::get_width()
{
    return width;
}

int basic_object::get_height()
{
    return height;
}

float basic_object::get_radius()
{
    return utilities::distance(xmin,ymin,xmax,ymax)/2;;
}

std::string basic_object::get_texture()
{
    return texture;
}

void basic_object::set_position(int x, int y)
{
    position.set((float)x,(float)y);
    calc_boundaries();
}

void basic_object::set_rotation(float angle)
{
    rotation=angle;
}

void basic_object::set_dimensions(int w, int h)
{
    width=w;
    height=h;
    calc_boundaries();
}

void basic_object::set_texture(std::string filename)
{
    if(graphics::images.find(filename)!=graphics::images.end())
        texture=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void basic_object::set_mask(std::string filename)
{
    if(graphics::images.find(filename)!=graphics::images.end())
        mask=filename;
    else
        std::cerr<<filename<<" not found.\n";
}

void basic_object::calc_boundaries()//calculates the limits of the object
{
    //these two variables store reused data in order to save calculations
    int half_width=width/2;
    int half_height=height/2;
    xmin=position.x-half_width;
    xmax=position.x+half_width;
    ymin=position.y-half_height;
    ymax=position.y+half_height;
}

void basic_object::rotate(float angle)
{
    rotation+=angle;
}

void basic_object::mark_selected()
{
    if(selected)
    {
        glColor3f(marker_color.r,marker_color.g,marker_color.b);
        glBegin(GL_LINES);//draws lines (in this case, a rectangle)
        glVertex2f(xmin-marker_width, ymax+marker_height);//top left corner
        glVertex2f(xmax+marker_width, ymax+marker_height);//top right corner
        glVertex2f(xmax+marker_width, ymax+marker_height);//top right corner
        glVertex2f(xmax+marker_width, ymin-marker_height);//bottom right corner
        glVertex2f(xmax+marker_width, ymin-marker_height);//bottom right corner
        glVertex2f(xmin-marker_width, ymin-marker_height);//bottom left corner
        glVertex2f(xmin-marker_width, ymin-marker_height);//bottom left corner
        glVertex2f(xmin-marker_width, ymax+marker_height);//top left corner
        glEnd();
    }
}

void basic_object::hide()
{
    visible=false;
}

void basic_object::show()
{
    visible=true;
}

void basic_object::mute()
{
    muted=true;
}

void basic_object::unmute()
{
    muted=false;
}

void basic_object::render_shape()
{
    if(filled)
    {
        glColor3f(fill_color.r,fill_color.g,fill_color.b);//color the square with object.fill_color
        glBegin(GL_POLYGON);//draws a filled in rectangle
        glVertex2f(xmin, ymin); // The bottom left corner
        glVertex2f(xmin, ymax); // The top left corner
        glVertex2f(xmax, ymax); // The top right corner
        glVertex2f(xmax, ymin); // The bottom right corner
        glEnd();//finish drawing
    }
}

void basic_object::render_border()
{
    if(bordered)
    {
        glColor3f(border_color.r,border_color.g,border_color.b);
        glBegin(GL_LINES);//draws lines (in this case, a rectangle)
        glVertex2f(xmin, ymax);//top left corner
        glVertex2f(xmax, ymax);//top right corner
        glVertex2f(xmax, ymax);//top right corner
        glVertex2f(xmax, ymin);//bottom right corner
        glVertex2f(xmax, ymin);//bottom right corner
        glVertex2f(xmin, ymin);//bottom left corner
        glVertex2f(xmin, ymin);//bottom left corner
        glVertex2f(xmin, ymax);//top left corner
        glEnd();
    }
}

void basic_object::render_texture()
{
    if(textured)
    {
        glEnable(GL_TEXTURE_2D);
        if(masked)
        {
            glEnable(GL_BLEND);
            glBlendFunc(GL_DST_COLOR,GL_ZERO);
            glBindTexture(GL_TEXTURE_2D, graphics::images[mask]);
            glBegin(GL_QUADS);
            glTexCoord2i(0, 0); glVertex2f(xmin, ymin);
            glTexCoord2i(0, 1); glVertex2f(xmin, ymax);
            glTexCoord2i(1, 1); glVertex2f(xmax, ymax);
            glTexCoord2i(1, 0); glVertex2f(xmax, ymin);
            glEnd();
            glBlendFunc(GL_ONE,GL_ONE);
        }
        glBindTexture(GL_TEXTURE_2D, graphics::images[texture]);
        glBegin(GL_QUADS);
        glTexCoord2i(0, 0); glVertex2f(xmin, ymin);
        glTexCoord2i(0, 1); glVertex2f(xmin, ymax);
        glTexCoord2i(1, 1); glVertex2f(xmax, ymax);
        glTexCoord2i(1, 0); glVertex2f(xmax, ymin);
        glEnd();
        if(masked)
            glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }
}

void basic_object::render()//draws the object
{
    if(visible)
    {
        glPushMatrix();//need push and pop so that entire scene isn't rotated
        glTranslatef(position.x,position.y,0.0);//translate object according to coordinates
        glRotatef(rotation,0,0,1);//rotates object with object.rotation
        glTranslatef(-position.x,-position.y,0.0);//translate object according to coordinates
        render_shape();
        render_border();
        render_texture();
        mark_selected();
        glPopMatrix();//reset transformation matrix
    }
}

void basic_object::update(){}

void basic_object::sync(){}

void basic_object::load()
{
    std::clog<<file_name;
    std::ifstream object_file(file_name);//access file by name
    if(object_file.bad())//make sure the file is there
    {
        std::cerr<<"bad file name\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //load basic object properties
    object_file>>position.x>>position.y;
    object_file>>rotation;
    object_file>>width>>height;
    object_file>>fill_color.r>>fill_color.g>>fill_color.b;
    object_file>>marker_color.r>>marker_color.g>>marker_color.b;
    object_file>>border_color.r>>border_color.g>>border_color.b;
    object_file>>filled;
    object_file>>bordered;
    object_file>>textured;
    object_file>>masked;
    object_file>>visible;
    object_file>>selected;
    object_file>>muted;
    object_file>>texture;
    object_file>>mask;
    object_file.close();
    std::clog<<"object#"<<number<<"(basic object)"<<" loaded.\n";
}

void basic_object::save()
{
    std::stringstream filename;
    filename<<"./data/objects/object#"<<number<<".bso";
    std::ofstream object_file(filename.str());
    if(object_file.bad())
    {
        std::cerr<<"bad file name.\n";
        return;
    }
    object_file.precision(3);
    object_file.setf(std::ios::fixed);
    //save basic object properties
    object_file<<position.x<<' '<<position.y<<std::endl;
    object_file<<rotation<<std::endl;
    object_file<<width<<' '<<height<<std::endl;
    object_file<<fill_color.str()<<std::endl;
    object_file<<marker_color.str()<<std::endl;
    object_file<<border_color.str()<<std::endl;
    object_file<<filled<<std::endl;
    object_file<<bordered<<std::endl;
    object_file<<textured<<std::endl;
    object_file<<masked<<std::endl;
    object_file<<visible<<std::endl;
    object_file<<selected<<std::endl;
    object_file<<muted<<std::endl;
    object_file<<texture<<std::endl;
    object_file<<mask<<std::endl;
    object_file.close();
    std::clog<<"object#"<<number<<"(basic object)"<<" saved.\n";
}

void basic_object::set_property(std::string name, int value)
{
    if(properties.find(name)!=properties.end())
        properties[name]=value;
    else
        std::cerr<<"property not found.\n";
}

void basic_object::add_property(std::string name, int value)
{
    if(name.find(" ")==std::string::npos)//no spaces found
        properties[name]=value;
    else
        std::cerr<<"cannot include spaces in property name\n";
}

basic_object::basic_object()
{
    number=++total_objects;
    position.set((float)default_position.x,(float)default_position.y);
    rotation=0.0f;
    set_dimensions(64,64);
    marker_width=5;
    marker_height=5;
    marker_color=BLACK;
    border_color=BLACK;
    fill_color.randomize();
    fill_color.changed=false;
    filled=true;
    bordered=false;
    textured=false;
    masked=false;
    selected=false;
    muted=false;
    show();
}

basic_object::basic_object(int x, int y, int w, int h)
{
    number=++total_objects;
    position.set(x,y);
    rotation=0.0f;
    set_dimensions(w,h);
    marker_width=5;
    marker_height=5;
    marker_color=BLACK;
    border_color=BLACK;
    fill_color.randomize();
    fill_color.changed=false;
    filled=true;
    bordered=false;
    textured=false;
    masked=false;
    selected=false;
    muted=false;
    show();
}

basic_object::basic_object(int x, int y, int w, int h, color c)
{
    number=++total_objects;
    position.set(x,y);
    rotation=0.0f;
    set_dimensions(w,h);
    marker_width=5;
    marker_height=5;
    marker_color=BLACK;
    border_color=BLACK;
    fill_color.set(c);
    fill_color.changed=false;
    filled=true;
    bordered=false;
    textured=false;
    masked=false;
    selected=false;
    muted=false;
    show();
}

basic_object::~basic_object(){}
