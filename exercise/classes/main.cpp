#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "functions.hpp"
using namespace std;

int main(){
    Car c (250);
    cout<<"Max speed: ";
    cout<< c.getMaxSpeed();
}
