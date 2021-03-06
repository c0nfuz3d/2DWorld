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

#ifndef COLOR_H
#define COLOR_H
#include <string>

//A color has red, green, blue, and alpha values.
class color
    {
        private:
        float prev_r;//previous red value
        float prev_g;//previous green value
        float prev_b;//previous blue value
        float prev_a;//previous alpha value
        bool values_set;
        public:
        std::string str();//returns the color values in a string
        float r;//red value
        float g;//green value
        float b;//blue value
        float a;//alpha value
        bool changed;//whether the color values have been modified
        bool matches(color c);//whether this color has the same values as the other color
        void randomize();//generate a random color
        void brighten();//increase the brightness of the color
        void brighten(float brightness);//increase brightness by given value
        void darken();//decrease brightness of the color
        void darken(float brightness);//decrease the brightness by given value
        void set(float red, float green, float blue);//set the RGB values
        void set(float red, float green, float blue, float alpha);//set the RGBA values
        void set(std::string c);//set the color according to name
        void set(color c);//set the color to match the given color
        void undo();//changes the color back to its previous setting
        color();
        color(float red, float green, float blue);
        color(float red, float green, float blue, float alpha);

    };
//below are a bunch of color presets
const color RED(1.0f,0.0f,0.0f);
const color ORANGE(1.0f,0.5f,0.0f);
const color YELLOW(1.0f,1.0f,0.0f);
const color GREEN(0.0f,1.0f,0.0f);
const color BLUE(0.0f,0.0f,1.0f);
const color PURPLE(1.0f,0.0f,1.0f);
const color BLACK(0.0f,0.0f,0.0f);
const color WHITE(1.0f,1.0f,1.0f);
const color GRAY(0.5f,0.5f,0.5f);

#endif // COLOR_H
