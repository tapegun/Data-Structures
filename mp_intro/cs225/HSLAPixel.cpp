/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225 {
    HSLAPixel::HSLAPixel(){
        this->h = 0.0;
        this->s = 0.0;
        this->l = 1.0;
        this->a = 1.0;
    }
    HSLAPixel::HSLAPixel(double hue, double sat, double lum){
        this->h = hue;
        this->s = sat;
        this->l = lum;
        this->a = 1.0;
    }
    HSLAPixel::HSLAPixel(double hue, double sat, double lum, double alph){
        this->h = hue;
        this->s = sat;
        this->l = lum;
        this->a = alph;
    }
}

