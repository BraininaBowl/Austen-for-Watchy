n#include <Watchy.h> //include the Watchy library
#include "PTSerif_Bold10pt7b.h"
#include "PTSerif_Regular10pt7b.h"
#include "pride.h"        

class WatchFace : public Watchy { //inherit and extend Watchy class
  public:

    // Global vars
    int16_t lineheight = 24;
    int16_t curx = 68;
    int16_t cury = 12 + lineheight;

    // Text drawing
    void drawText(String text){
      int16_t  x1, y1, testx, counter;
      uint16_t w, h;

      display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
      testx = curx + w;
      if (testx > 194){
        cury += lineheight; 
        if (cury < 64) {
          curx = 68;
        } else {
          curx = 6;
        }
      }
      display.setCursor(curx,cury);
      curx += w + 5;
      display.print(text);
    }
  
    void drawWatchFace() { //override this method to customize how the watch face looks

      int16_t hoffset;
      int16_t arraylength[] = {11,0,20};
      String nmbrs[] = {"midnight", "one", "two", "three", "four", "five", "six", "seven", "eight","nine","ten","eleven","twelve","thirteen","fourteen","quarter","sixteen","seventeen","eighteen","nineteen","twenty","twenty-one","twenty-two", "twenty-three", "twenty-four", "twenty-five", "twenty-six", "twenty-seven", "twenty-eight", "twenty-nine", "half" };
      String pretext[] = {"t", "is", "a", "truth", "universally", "acknowledged,", "that", "a", "single", "man", "at"};
      String text[10] = {};
      if (currentTime.Hour == 12 && currentTime.Minute == 0){
        text[arraylength[1]] = "noon";
        arraylength[1] += 1; 
      } else {
        if (currentTime.Minute == 0){
        } else if (currentTime.Minute < 31) {
          text[arraylength[1]] = nmbrs[currentTime.Minute];
          arraylength[1] += 1; 
          text[arraylength[1]] = "past";
          arraylength[1] += 1;
          hoffset = currentTime.Hour;
        } else {
          text[arraylength[1]] = nmbrs[60-currentTime.Minute];
          arraylength[1] += 1; 
          text[arraylength[1]] = "to";
          arraylength[1] += 1;           
          hoffset = currentTime.Hour + 1;
        }
        if (hoffset < 13){
          text[arraylength[1]] = nmbrs[hoffset];
          arraylength[1] += 1; 
        } else if (currentTime.Hour == 13) {
          text[arraylength[1]] = "one";
          arraylength[1] += 1; 
        } else {
          text[arraylength[1]] = nmbrs[hoffset-12];
          arraylength[1] += 1; 
        }
        if (currentTime.Minute==0 && currentTime.Hour != 0 && currentTime.Hour != 12) {
          text[arraylength[1]] = "o'clock";
          arraylength[1] += 1;
        }
      }
      
      String posttext[] = {"must", "be", "in", "want", "of", "a", "wife.", "However", "little", "known", "the", "feelings", "or", "views", "of", "such", "a", "man", "may", "be."};
      
      //drawbg
      display.fillScreen(GxEPD_WHITE);
      display.drawBitmap(4, 4, Pride, 60, 60, GxEPD_BLACK);

      //draw time
      display.setTextColor(GxEPD_BLACK);
      display.setTextWrap(false);

      display.setFont(&PTSerif_Regular10pt7b);
      for (int i=0; i<arraylength[0]; i++) {
        drawText(pretext[i]);
      }

      display.setFont(&PTSerif_Bold10pt7b);
      for (int i=0; i<arraylength[1]; i++) {
        drawText(text[i]);
      }

      display.setFont(&PTSerif_Regular10pt7b);
      for (int i=0; i<arraylength[2]; i++) {
        drawText(posttext[i]);
      }

    
    }
};

WatchFace m; //instantiate your watchface

void setup() {
  m.init(); //call init in setup
}

void loop() {
  // this should never run, Watchy deep sleeps after init();
}
