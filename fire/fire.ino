/* "fire" Sparkle Shield animation
 * 
 * displays a classical fire animation
 *
 * created by gedsic, Jan 2015
 *
 */

#include <FastLED.h>
#include <SparkleShield.h>
#include <math.h>

#define BRIGHTNESS 32 // Sparkle Shield brightness
#define FIRECOLORMIN 40// lower bound for fire color
#define FIRECOLORMAX 60 // upper bound for fire color
#define FIREMINVALUE 75 // lower HSV value bound for randomization of ground line
#define DIVISOR 5 // divisor that controls fire's brightness decrease with height
#define ANIMDELAY 50 // ms delay between frames

SparkleShield sparkle;

void loop()
{
  // "screen" buffer in which fire calculations are performed
  CHSV buf1[70];

  // initialize empty buffer
  ClearBuffer(&buf1[0],CHSV(255,255,0));

  while(1==1)
  {
    // draw ground line
    for (byte x = 0; x < kMatrixWidth; x++)
    {
      SetBuffer(x,0,&buf1[0],CHSV(random(FIRECOLORMIN,FIRECOLORMAX),255,random(FIREMINVALUE,255)));
    }

    for (byte x = 0; x < kMatrixWidth; x++)
    {
      for (byte y = 1; y < kMatrixHeight; y++)
      {
        CHSV newpixel = GetBuffer(x,y-1,&buf1[0]);
        // calculate new h and v for pixel based on surrounding ones
        // TODO: maybe use 4 vars instead of doing this twice?
        int newvalue = floor((GetBuffer((x - 1 + kMatrixWidth) % kMatrixWidth,(y - 1 + kMatrixHeight) % kMatrixHeight, &buf1[0]).val
          +GetBuffer((x) % kMatrixWidth,(y - 1 + kMatrixHeight) % kMatrixHeight, &buf1[0]).val
          +GetBuffer((x + 1) % kMatrixWidth,(y - 1 + kMatrixHeight) % kMatrixHeight, &buf1[0]).val
          +GetBuffer((x) % kMatrixWidth,(y - 2 + kMatrixHeight) % kMatrixHeight, &buf1[0]).val)/DIVISOR);
        int newhue = floor((GetBuffer((x - 1 + kMatrixWidth) % kMatrixWidth,(y - 1 + kMatrixHeight) % kMatrixHeight, &buf1[0]).hue
          +GetBuffer((x) % kMatrixWidth,(y - 1 + kMatrixHeight) % kMatrixHeight, &buf1[0]).hue
          +GetBuffer((x + 1) % kMatrixWidth,(y - 1 + kMatrixHeight) % kMatrixHeight, &buf1[0]).hue
          +GetBuffer((x) % kMatrixWidth,(y - 2 + kMatrixHeight) % kMatrixHeight, &buf1[0]).hue)/4);
        newpixel.val = newvalue;
        newpixel.hue = newhue;
        SetBuffer(x,y,&buf1[0],newpixel);
      }
    }

    DrawBuffer(&buf1[0]);
    sparkle.show();
    delay(ANIMDELAY);
  }
}

// function to copy one buffer to another
void CopyBuffer(CHSV *origbuf, CHSV *targetbuf)
{
  for (byte x = 0; x < kMatrixWidth; x++)
  {
    for (byte y = 0; y < kMatrixHeight; y++)
    {
      SetBuffer(x,y,targetbuf,GetBuffer(x,y,origbuf));
    }
  }
}

// fill buffer with a single value
void ClearBuffer(CHSV *buffer, CHSV value)
{
  for(byte x = 0; x < kMatrixWidth; x++)
  {
    for(byte y = 0; y < kMatrixHeight; y++)
    {
      buffer[x + (y * kMatrixWidth)]=value;
    }
  }

}

// set buffer pixel
void SetBuffer(byte x,byte y,CHSV *buffer, CHSV value)
{
  buffer[x + (y * kMatrixWidth)] = value;
}

// get buffer pixel
CHSV GetBuffer(byte x,byte y,CHSV *buffer)
{
  return buffer[x + (y * kMatrixWidth)];
}

// draw buffer to sparkle shield
void DrawBuffer(CHSV *buffer)
{
  for(byte x = 0; x < kMatrixWidth; x++)
  {
    for(byte y = 0; y < kMatrixHeight; y++)
    {
      sparkle.set(x, y, GetBuffer(x, y, buffer));
    }
  }
}

void setup()
{
  sparkle.setBrightness(BRIGHTNESS);  
}



