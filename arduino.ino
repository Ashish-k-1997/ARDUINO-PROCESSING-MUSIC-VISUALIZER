/*------------------------------------------------------------------------------------------------------------------------------
     Arduino - Processing Spectrum Analyzer with gui.

This program is intended to do a FFT on incoming audio signal from microphone or sterio mix on PC 
The program is based on http://processing.org/learning/libraries/forwardfft.html
Youtube video sample: https://www.youtube.com/watch?v=X35HbE7k3DA
Source code : https://github.com/Ashish-k-1997/ARDUINO-PROCESSING-MUSIC-VISUALIZER


           Created: 7 Oct 2016 by Ashish Kumar
     Last Modified: 27 April 2017 by Ashish Kumar
     
     Variables with the <-O-> symbol indicates that it can be adjusted for the reason specified.
     
           By Ashish Kumar
           Ashish.k.199710@gmail.com
           https://www.facebook.com/Ashishk199710
           https://github.com/Ashish-k-1997

DO NOT DISTRUBUTE WITHOUT PERMISSION, SUPPORT DEVELOPER.           
-------------------------------------------------------------------------------------------------------------------------------
*/

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
                                                                // Predefined variables.
#define CLK 53  // MUST be on PORTB!
#define LAT A3
#define OE  52
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false, 2);   // Inilization of RGB pannel, last parameter specifies number of displays chained together   
                                                          // Second last parameter = 'true' enables double-buffering, for flicker-free,
                                                          // buttery smooth animation but uses more ram.  Note that NOTHING WILL SHOW ON THE DISPLAY
                                                          // until the first call to swapBuffers().  This is normal.

byte height[64];   // Height is number of led to light up in single row. Bars stores number of rows in display setup, 64 due to 2 display so total 64 rows of led.
int x,y, amplitude, bars=64;         // Loop variable for leds.

void lightcolumn()
{ 
  for(int x=0; x<bars; x++)
  {
    
   amplitude=int(height[x]);
         
  if(amplitude>15)  
  {
  for( y = 0; y < amplitude; y++){
  matrix.drawPixel(x, y, matrix.Color333(7, 0, 0));
  }
  for(y = amplitude; y <16; y++)
  {
  matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));  
  }
  }
  
  else if(amplitude>13) 
  {
  for( y = 0; y < amplitude; y++){
  matrix.drawPixel(x, y, matrix.Color333(5, 6, 1));
  }
  for(y = amplitude; y < 16; y++)
  {
  matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));  
  }
  }
  
  else if(amplitude>9) 
  {
  for(y = 0; y < amplitude; y++){
  matrix.drawPixel(x, y, matrix.Color333(6, 1, 6));
  }
  for(y = amplitude; y < 16; y++)
  {
  matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));  
  }
  } 
  
  else if(amplitude>6)
  {
  for(y = 0; y < amplitude; y++){
  matrix.drawPixel(x, y, matrix.Color333(0, 0, 7));
  }
  for(y = amplitude; y < 16; y++)
  {
  matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));  
  }
  }
  else
  {
  for(y = 0; y < amplitude; y++){
  matrix.drawPixel(x, y, matrix.Color333(0, 3, 5));
  }
  for(y = amplitude; y < 16; y++)
  {
  matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));  
  }
  }
   
 }

}





void setup() 
{
 Serial.begin(15360); 
 Serial.flush();
 matrix.begin();  

 matrix.swapBuffers(false);
 //All leds blue.
 for(int i=0;i<64;i++)         
  for(int j=0;j<16;j++)
   matrix.drawPixel(i, j, matrix.Color333(0, 2, 2));

 delay(200); 

  //All leds black.
  for(int i=0;i<64;i++)
   for(int j=0;j<16;j++)
    matrix.drawPixel(i, j, matrix.Color333(0, 0, 0));

}

void loop() 
{
  while(true)   //Its is faster.
  {
    if(Serial.read()==0xff)  // Marker.
    { 
        Serial.readBytes(height, bars);  //Reading data.
        lightcolumn();      
    }
  }
}
