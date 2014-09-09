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

#ifndef GAME_H
#define GAME_H
#include <time.h>
//The game namespace stores important settings and global variables for the program
namespace game
{
    const int max_objects = 6;//maximum number of objects to be created for collision testing. must be constant so that array can be made using this number
    extern float time;
    extern clock_t time_started;
    extern double time_elapsed;
}
#endif // GAME_H
