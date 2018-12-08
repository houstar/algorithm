#ifndef CONTAINER_OF_H
#define CONTAINER_OF_H

#include <stddef.h>

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})


#define WRITE_ONCE(var, val) \
    (*((volatile typeof(val) *)(&(var))) = (val))

#define READ_ONCE(var) (*((volatile typeof(var) *)(&(var))))

#endif //CONTAINER_OF_H
