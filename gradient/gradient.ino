/* Sparkle Shield animation
* 
* displays a slowly shifting color gradient
*
* created by gedsic, Jan 2015
*
*/

#include <FastLED.h>
#include <SparkleShield.h>
#include <math.h>

#define BRIGHTNESS 32
#define GRADIENTSTEP 8  // color increment per column for gradient
#define BASECSTEP 1  // increment value for gradient base color, "shift speed"
#define ANIMDELAY 30 // animation delay in ms

SparkleShield sparkle;

void loop()
{
  // basec is the leftmost color
  for (byte basec = 0; basec < 255; basec+= BASECSTEP)
  {
    byte targetc = basec + 100;
    DrawGradient(basec,GRADIENTSTEP);
    sparkle.show();
    delay(ANIMDELAY);

  }
}

void DrawGradient(byte startc, byte stepsize)
{
  byte color = startc;
  for (byte x = 0; x < kMatrixWidth; x++)
  {
    for (byte y = 0; y < kMatrixHeight; y++)
    {
      sparkle.set(x,y,CHSV(color,255,255));
    }
    color+= stepsize;
  }
}

void setup()
{
  sparkle.setBrightness(BRIGHTNESS);  
}

