#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  // Image alma;
  // Image alma1;
  // Image alma2;
  // Image alma3;
  // alma.readFromFile("alma.png");
  // alma1.readFromFile("alma.png");
  // alma2.readFromFile("alma.png");
  // alma3.readFromFile("alma.png");
  // alma2.grayscale();
  // alma3.illinify();
  // alma1.darken();
  // StickerSheet * sheet = new StickerSheet(alma, 4); //remember to change max to being one less because it should only hold the number of stickers not including the base;
  // //sheet->addSticker(alma, 50, 50);
  // sheet->addSticker(alma1, 100, 50);
  // sheet->addSticker(alma2, 50, 100);
  // sheet->addSticker(alma3, 150, 150);

  // Image thing = sheet->render(); 
  // thing.writeToFile("myImage.png");
  // delete sheet;
  // return 0;

  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");
  Image b;    b.readFromFile("tests/i.png");
  Image c;    c.readFromFile("tests/i.png");
  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 50, 100);
  sheet.addSticker(i, 200, 20);

  Image thing = sheet.render();
  thing.writeToFile("myImage.png");
}
