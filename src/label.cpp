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

#include "label.h"
#include "ui.h"
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

void label::add_line(std::string str)
{
    text.push_back(str);
    set_dimensions(font_width*str.length(),font_height);
}

void label::set_font(std::string style, int size)
{
    font_size=size;
    font_width=font_size*0.6;
    font_height=font_size;
    if(style=="helvetica")
    {
        if(size==10)
            font=GLUT_BITMAP_HELVETICA_10;
        if(size==12)
            font=GLUT_BITMAP_HELVETICA_12;
        if(size==18)
            font=GLUT_BITMAP_HELVETICA_18;
    }
    if(style=="times new roman")
    {
        if(size==10)
            font=GLUT_BITMAP_TIMES_ROMAN_10;
        if(size==24)
            font=GLUT_BITMAP_TIMES_ROMAN_24;
    }
}

void label::render()
{
    if(visible)
    {
        glColor3f(fill_color.r,fill_color.g,fill_color.b);
        for(unsigned l=0; l<text.size(); l++)//iterate through each line
        {
            glRasterPos2f(position.x,position.y-((spacing+font_height)*l));//update the character position
            for(unsigned c=0; c<text[l].length(); c++)//iterate through each character
                glutBitmapCharacter(font, text[l][c]);//print the character to the screen
        }
    }
}

void label::clear()
{
    text.clear();
}

label::label()
{
    type="text object";
    fill_color=BLACK;
    set_font("helvetica",12);
    spacing=1;
    std::clog<<"object#"<<number<<'('<<type<<')'<<" created. "<<sizeof(*this)<<" bytes"<<std::endl;
}