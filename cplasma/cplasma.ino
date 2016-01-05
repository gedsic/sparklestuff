/* "cplasma" Sparkle Shield animation
 * 
 * displays a circle-shaped plasma-like animation
 *
 * Based on example code from Lode's Computer Graphics Tutorial
 * http://lodev.org/cgtutor/plasma.html
 *
 * created by gedsic, Jan 2015
 *
 */

#include <FastLED.h>
#include <SparkleShield.h>
#include <math.h>

#define BRIGHTNESS 32 // Sparkle Shield brightness
#define DIVISOR 8 // divisor that determines "how much color" we have on the screen
#define ANIMDELAY 1 // ms delay between frames

SparkleShield sparkle;

void loop()
{
  while(1==1)
  {
    for (byte centerc = 0; centerc < 255; centerc++)
    {
      for (byte x = 0; x < kMatrixWidth; x++)
      {
        for (byte y = 0; y < kMatrixHeight; y++)
        {
          int color = int(centerc + (128 * sin(sqrt((x - kMatrixWidth / 2) * (x - kMatrixWidth / 2) + (y - kMatrixHeight / 2) * (y - kMatrixHeight / 2))/DIVISOR)));
          sparkle.set(x, y, CHSV(color,255,255));
        }
      }
      sparkle.show();
      delay(ANIMDELAY);
    }
  }

}

void setup()
{
  sparkle.setBrightness(BRIGHTNESS);  
}





