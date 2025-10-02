/// object.h

#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>


typedef struct Object Object;
struct Object {
    // Variables
    uint8_t uuid;
    // Functions

};

uint8_t Object_get_uuid(Object *self);
uint8_t Object_clean(Object *self);
uint8_t Object_init(Object *self);

#include "object.h"
uint8_t Object_init(Object *self)
{
    self->uuid = 27;

    return 0;
}

uint8_t Object_get_uuid(Object *self)
{ // Don't actually create getters in C...
    return self->uuid;
}
uint8_t Object_clean(Object *self)
{
    // No dynamic memory to free in this simple example
    // BAM: Is this true?

    return 0;
}

#endif // OBJECT_H