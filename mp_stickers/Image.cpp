
//#include "HSLAPixel.h"
#include "Image.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
using namespace cs225;


    void Image::illinify(){
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel & pixel = getPixel(x, y);
                if (std::abs(11 - pixel.h) < std::abs(216 - pixel.h) || std::abs(371 - pixel.h) < std::abs(216 - pixel.h)){
                pixel.h = 11;
                }
                else{
                pixel.h = 216;
                }
            }
        }
    }


    void Image::darken(){
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel & pixel = getPixel(x, y);
                pixel.l = pixel.l - .1;
                if (pixel.l < 0){pixel.l = 0;}
                if (pixel.l > 1){pixel.l = 1;}
            }
        }
    }

    void Image::darken(double amt){
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel & pixel = getPixel(x, y);
                pixel.l = pixel.l - amt;
                if (pixel.l < 0){pixel.l = 0;}
                if (pixel.l > 1){pixel.l = 1;}
            }
        }
    }
    
    void Image::desaturate(){
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel & pixel = getPixel(x, y);
                pixel.s = pixel.s - .1;
                if (pixel.s < 0){pixel.s = 0;}
                if (pixel.s > 1){pixel.s = 1;}
            }
        }
    }
    void Image::desaturate(double amt){
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel & pixel = getPixel(x, y);
                pixel.s = pixel.s - amt;
                if (pixel.s < 0){pixel.s = 0;}
                if (pixel.s > 1){pixel.s = 1;}
            }
        }
    }

    void Image::grayscale(){
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
            HSLAPixel & pixel = getPixel(x, y);
            pixel.s = 0;
            }
        }
    }
    void Image::lighten(){
        this->darken(-.1);
    }
    void Image::lighten(double amt){
        this->darken(-1.0 * amt);
    }
    void Image::rotateColor(double deg){
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                HSLAPixel & pixel = getPixel(x, y);

                pixel.h += deg;
                if(pixel.h > 360){
                    pixel.h -= 360;
                }
                if(pixel.h < 0){
                    pixel.h += 360;
                }
            }
        }
    }
    void Image::saturate(){
        desaturate(-.1);
    }

    void Image::saturate(double amt){
        desaturate(-1.0 * amt);
    }
    void Image::scale(double fact){
        double scalerY = 0.0;
        double scalerX = 0.0;

        PNG * image = new PNG(width()*fact, height()*fact);
        for (unsigned x = 0; x < image->width(); x++) {
            for (unsigned y = 0; y < image->height(); y++) {
                HSLAPixel & pixel = image->getPixel(x, y);
                //std::cout<< "scaler: " << scalerY << " index: " << x << " " << y <<std::endl;
                //std::cout<< height()<<std::endl;
                

                //don't even try to understand this your brain will explode
                HSLAPixel & pixelUp = getPixel(unsigned(double(x)/fact), unsigned(floor(scalerY)));
                if(unsigned(ceil(scalerY))>=height()){
                    pixel = pixelUp;
                }
                else{
                    HSLAPixel & pixelDown = getPixel(unsigned(double(x)/fact), unsigned(ceil(scalerY)));
                    pixel.h = (pixelUp.h + pixelDown.h)/2.0;
                    pixel.s = (pixelUp.s + pixelDown.s)/2.0;
                    pixel.l = (pixelUp.l + pixelDown.l)/2.0; 
                    pixel.a = (pixelUp.a + pixelDown.a)/2.0;
                }
                scalerY += (1.0/fact);
                
            }
            scalerY = 0;
        }
        for (unsigned y = 0; y < image->height(); y++) {
            for (unsigned x = 0; x < image->width(); x++) {
                HSLAPixel & pixel = image->getPixel(x, y);
                HSLAPixel & pixelUp = getPixel(unsigned(floor(scalerX)), unsigned(double(y)/fact));
                if(unsigned(ceil(scalerX))>=width()){
                    pixel = pixelUp;
                }
                else{
                    HSLAPixel & pixelDown = getPixel(unsigned(ceil(scalerX)), unsigned(double(y)/fact));
                    pixel.h = (pixelUp.h + pixelDown.h)/2.0;
                    pixel.s = (pixelUp.s + pixelDown.s)/2.0;
                    pixel.l = (pixelUp.l + pixelDown.l)/2.0; 
                    pixel.a = (pixelUp.a + pixelDown.a)/2.0;
                    scalerX += (1.0/fact);
                }

            }
            scalerX = 0;
        }
        // int iter = 0;
        resize(image->width(), image->height());
        for (unsigned x = 0; x < width(); x++) {
            for (unsigned y = 0; y < height(); y++) {
                // std::cout << "iter " << x << std::endl;
                HSLAPixel & pixel = getPixel(x, y);
                pixel = image->getPixel(x, y);
                // iter++;
            }
        }
        delete image;
    }

    void Image::scale(unsigned w, unsigned h){
        double hFac = (double(h))/height();
        double wFac = (double(w))/width();
        if(hFac < wFac){
            scale(hFac);
        }
        else{
            scale(wFac);
        }
    }



