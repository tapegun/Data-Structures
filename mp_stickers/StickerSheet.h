/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#include <iostream>
#include <sstream>
#include "cs225/PNG.h"
#pragma once

class StickerSheet{
    public:
        StickerSheet (const Image &picture, unsigned max);
        ~StickerSheet ();
        StickerSheet (const StickerSheet &other);
        const StickerSheet & operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void removeSticker (unsigned index);
        Image * getSticker (unsigned index);
        Image render () const;
        Image ** arr;
        unsigned * arrx;
        unsigned * arry;
        unsigned maxNum;
        unsigned numStickers;
        Image Base;
        void copy_(const StickerSheet &other);
        //unsigned arrItems;
        void clear();

};


