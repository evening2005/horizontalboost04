#include <pebble.h>
#include "gamelight.h"

static AppTimer *lightTimer;

void light_off(void *data) {
    light_enable(false);
}

void switch_on_light(int howLong) {
    light_enable(true);
    // Can't be less than 20 seconds or more than 100 seconds!
    if(howLong < 20000) howLong = 20000;
    if(howLong > 100000) howLong = 100000; 
    if(!app_timer_reschedule(lightTimer, howLong)) {
        lightTimer = app_timer_register(howLong,light_off,NULL);
    }
}

