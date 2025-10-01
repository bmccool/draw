/// object.h

#ifndef OBJECT_H
#define OBJECT_H

#include <stdint.h>


typedef struct Object {
    uint8_t uuid;
} Object;

uint8_t Object_init(Object *self);
uint8_t Object_get_uuid(Object *self);
uint8_t Object_clean(Object *self);

#endif // OBJECT_H