#include "Image.h"
#include <cmath>
#include <iostream>
#include <cstdlib>
#include "StickerSheet.h"
using namespace cs225;




StickerSheet::StickerSheet(const Image & picture, unsigned max){
    maxNum = max;
    arr = new Image* [max];
    for(unsigned i = 0; i < max; i++){
        arr[i] = NULL;
    }
    Base = picture; // decided not to make element 0 the base.. this is more intuitive
    arrx = new unsigned[max];
    arry = new unsigned[max];
    numStickers = 0;    //how many are in the array at this point. 

}	
StickerSheet::~StickerSheet(){
     clear();
}
StickerSheet::StickerSheet (const StickerSheet &other){
    this->copy_(other);
}
void StickerSheet::copy_(const StickerSheet &other){

    maxNum = other.maxNum;
    Base = other.Base;
    numStickers = other.numStickers;
    arrx = new unsigned[maxNum];
    arry = new unsigned[maxNum];
    arr = new Image* [maxNum];
    for (unsigned i = 0; i < maxNum; i++){
        arr[i] = NULL;
    }

    for (unsigned i = 0; i < numStickers; i++){
        arr[i] = new Image();
        *arr[i] = *other.arr[i];
        arrx[i] = other.arrx[i];
        arry[i] = other.arry[i];
    }
}
const StickerSheet & StickerSheet::operator= (const StickerSheet &other){
    clear();
    copy_(other);
    return *this;
}
void StickerSheet::changeMaxStickers (unsigned max){

    if(max == numStickers){
        return;
    }
    Image** newArray = new Image*[max];
    for(unsigned i = 0; i < max; i++){
        newArray[i] = NULL;
    }
    unsigned* newx = new unsigned[max];
    unsigned* newy = new unsigned[max];

    if(numStickers < max){
        for (unsigned i = 0; i < numStickers; i++){ 
            newArray[i] = arr[i];
            newx[i] = arrx[i];
            newy[i] = arry[i];
        }
    }
    else{
        for (unsigned i = 0; i < max; i++){
        newArray[i] = arr[i];
        newx[i] = arrx[i];
        newy[i] = arry[i];
        }
        numStickers = max;
    }

    for(unsigned i = 0; i < numStickers; i++){
            arr[i] = nullptr; //point the old arr pointer to null so we can set arr to newArray
    }
    // delete arr[];
    delete[] arrx;
    delete[] arry;
    arrx = nullptr;
    arry = nullptr;
    arr = newArray;
    newArray = NULL;
    arrx = newx;
    newx = NULL;
    arry = newy;
    newy = NULL;

    maxNum = max;
}


int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
    
     if(numStickers < maxNum){
        if(arr[numStickers] == NULL){
            arr[numStickers] = new Image();
            *arr[numStickers] = sticker;
            arry[numStickers] = y;
            arrx[numStickers] = x;
            numStickers ++;
            return (numStickers - 1);
        }
    }
    return -1;
}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y){
    if(index >= numStickers){
        return false;
    }
    else{
        arrx[index] = x;
        arry[index] = y;
        return true;
    }
}
void StickerSheet::removeSticker (unsigned index){
    if(index < numStickers){
        delete arr[index];
        arr[index] = new Image();
        for(unsigned i = index; i < (numStickers - 1); i++){
            *arr[i] =  *arr[i + 1];      //shift all the values down so we can delete empty thing at the top.
            arrx[i] = arrx[i + 1];
            arry[i] = arry[i + 1];
        }
        delete arr[numStickers - 1];  
        arr[numStickers] = NULL;
        numStickers --;
    }


}
Image * StickerSheet::getSticker (unsigned index){
    if (index < numStickers){
        return arr[index];
    }
    return NULL;
}
Image StickerSheet::render () const{
    Image img;
    img = Base;
    for(unsigned i = 0; i < numStickers; i++){
        if(arr[i] != NULL){
            for(unsigned w = arrx[i]; w < (arrx[i] + arr[i]->width()); w++){
                for(unsigned h = arry[i]; h < (arry[i] + arr[i]->height()); h++){
                    if(arr[i]->getPixel((w - arrx[i]), (h - arry[i])).a != 0 && w < img.width() && h < img.height()){
                        img.getPixel(w, h) = arr[i]->getPixel((w - arrx[i]), (h - arry[i]));
                    }
                }
            }
        }
    }
    return img;
}

void StickerSheet::clear(){
    for(unsigned i = 0; i < numStickers; i++){
        if(arr[i] != nullptr){
            delete arr[i];
            arr[i] = nullptr;
        }

    }
    delete[] arr;
    delete[] arrx;
    delete[] arry;
    arr = nullptr;
    arrx = nullptr;
    arry = nullptr;
}