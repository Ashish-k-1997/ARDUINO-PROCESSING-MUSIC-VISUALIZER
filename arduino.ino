#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 53  // MUST be on PORTB!
#define LAT A3
#define OE  52
#define A   A0
#define B   A1
#define C   A2
// Last parameter = 'true' enables double-buffering, for flicker-free,
// buttery smooth animation.  Note that NOTHING WILL SHOW ON THE DISPLAY
// until the first call to swapBuffers().  This is normal.
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false, 2);

byte height[64], bars=64;
int x,y, amplitude;

void lightcolumn()
{
 
  
  for(int x=0; x<bars; x++)
  {
    
   amplitude=int(height[x]);
         
  if(amplitude>15)  // <-O-> set the threshold for the band to turn red
  {
  for( y = 0; y < amplitude; y++){
  matrix.drawPixel(x, y, matrix.Color333(7, 0, 0));
  }
  for(y = amplitude; y <16; y++)
  {
  matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));  
  }
  }
  
  else if(amplitude>13) // <-O-> set the threshold for the band to turn yellow
  {
  for( y = 0; y < amplitude; y++){
  matrix.drawPixel(x, y, matrix.Color333(5, 6, 1));
  }
  for(y = amplitude; y < 16; y++)
  {
  matrix.drawPixel(x, y, matrix.Color333(0, 0, 0));  
  }
  }
  
  else if(amplitude>9) // <-O-> set the threshold for the band to turn green
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
 Serial.begin(9600); 
 Serial.flush();
 matrix.begin();  

  matrix.swapBuffers(false);
 for(int i=0;i<64;i++)
  for(int j=0;j<16;j++)
   matrix.drawPixel(i, j, matrix.Color333(0, 2, 2));

 delay(500); 

  for(int i=0;i<64;i++)
   for(int j=0;j<16;j++)
    matrix.drawPixel(i, j, matrix.Color333(0, 0, 0));

}

void loop() 
{
  
  while(true)
  {
   if(Serial.available())
    if(Serial.read()==0xff)
    { 
        Serial.readBytes(height, bars);
        
        lightcolumn();
        matrix.swapBuffers(false);     
        
    }
  }
}
