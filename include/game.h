#ifndef GAME_H
#define GAME_H

#include <time.h>
namespace game
{
    const int max_objects = 6;//maximum number of objects to be created for collision testing. must be constant so that array can be made using this number
    extern double time;
    extern float time_started;
    extern double time_elapsed;
    float get_time();
}
#endif // GAME_H