#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "functions.hpp"

using namespace std;

Car::Car(int maxSpeed) {
    maxS = maxSpeed;
}

int Car::getMaxSpeed(){
    return maxS;
}