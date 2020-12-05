#ifndef _INPUT_H_
#define _INPUT_H_

struct input_event{
    struct timeval time;
    __u16 type;
    __u16 code;
    __s32 value;
};

#endif
