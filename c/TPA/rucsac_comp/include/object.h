#ifndef __OBJECT_H__
#define __OBJECT_H__

#define MAX_OBJECTS 15

struct Object
{
    int weight;
    int profit;
    float ratio; //  profit / weight unit
};

#endif