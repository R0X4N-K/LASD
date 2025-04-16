#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Car {
    public:
        Car(int maxSpeed);
        int getMaxSpeed();
    private:
        int maxS;
}; 

#endif