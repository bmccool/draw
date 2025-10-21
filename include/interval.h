#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"

typedef struct Interval {
    float min;
    float max;
} Interval;

static struct Interval interval_new(float min, float max) {
    struct Interval interval = {min, max};
    return interval;
}

static bool interval_contains(Interval* this_interval,float value) {
    return (value >= this_interval->min) && (value <= this_interval->max);
}

static bool interval_surrounds(Interval* this_interval, float value) {
    return (value > this_interval->min) && (value < this_interval->max);
}

static float interval_clamp(Interval* this_interval, float value) {
    if (value < this_interval->min) {
        return this_interval->min;
    }
    else if (value > this_interval->max) {
        return this_interval->max;
    }
    else {
        return value;
    }
}

static float random_float() {
    if (rand_init == 0) {
        srand((unsigned int)time(NULL));
        rand_init = 1;
    }
    // Returns a random real in [0,1).
    float r = rand() / (RAND_MAX + 1.0);
    //printf("Random float [0, 1) %f\n", r);
    return r;
}

static float random_bounded_float(float min_bound, float max_bound) {
    // Returns a random real in [min,max).
    float random_result = random_float();
    float ret_val = min_bound + (max_bound - min_bound) * random_result;
    return ret_val;
}

#define INTERVAL_EMPTY Interval{ draw_infinity, -draw_infinity }
#define INTERVAL_UNIVERSE Interval{ -draw_infinity, draw_infinity }


#endif // INTERVAL_H