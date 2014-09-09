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

#ifndef TANGIBLE_H
#define TANGIBLE_H
#include "movable_object.h"

//A tangible object can move and detect collision with another object
class tangible_object: public movable_object
{
    public:
    int touching[4];/*The number of the touching object is stored in each index. "0" is no object
    Each index corresponds to a side: [1] is left, [2] is right, [3] is front, [4] is back*/
    void repel(object B);//object moves away from object B
    void attract(object B);//object moves toward object B
    void simon_says(object B);//object changes color according to side touched
    void identify(object B);//variable touching[] is updated with the number of the touched object
    bool is_close(object B);//check if object B is close to the center of this object
    bool near_front(object B);
    bool near_back(object B);
    bool near_left(object B);
    bool near_right(object B);
    tangible_object();
};
#endif // TANGIBLE_H
