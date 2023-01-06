/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#include <iostream>
#include <sstream>
#include "cs225/PNG.h"
#pragma once


class Image: public cs225::PNG{
    public:
        void darken();
        void darken(double);
        void desaturate();
        void desaturate(double);
        void grayscale();
        void illinify();
        void lighten();
        void lighten(double);
        void rotateColor(double degrees);
        void saturate();
        void saturate(double);
        void scale(double factor);
        void scale(unsigned w, unsigned h);



};

