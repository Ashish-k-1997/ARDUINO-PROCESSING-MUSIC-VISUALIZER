import processing.serial.*;  // Libraries
import ddf.minim.analysis.*;
import ddf.minim.*;

Serial arduino;             // Objects or instances
Minim minim;
AudioInput in;
FFT fft;


int buffer_size = 4096; // Global variables
float sample_rate = 128000;
int freq_width = 250;// <-O-> set the frequency range for each band over 400hz. larger bands will have less intensity per band. smaller bands would result in the overall range being limited
//arrays to hold the 64 bands' data
byte[] height = new byte[64]; 
float[] freq_height = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int i;



// Need G4P library



import g4p_controls.*;

boolean main=false;

public void setup(){
  size(480, 320, JAVA2D);
  createGUI();
  customGUI();
  
  
  
  // Place your setup code here  
  
    minim = new Minim(this);
 in = minim.getLineIn(Minim.MONO,buffer_size,sample_rate);
 
   // create an FFT object that has a time-domain buffer 
  // the same size as line-in's sample buffer
 fft = new FFT(in.bufferSize(), in.sampleRate());

}

public void draw()
{
  background(0);
  
  if(main)
 { 
  // perform a forward FFT on the samples in input buffer
  fft.forward(in.mix);
  
  freq_height[0] = fft.calcAvg((float) 0, (float) 60);
  freq_height[1] = fft.calcAvg((float) 61, (float) 120);
  freq_height[2] = fft.calcAvg((float) 121, (float) 180);
  freq_height[3] = fft.calcAvg((float) 181, (float) 240);
  freq_height[4] = fft.calcAvg((float) 241, (float) 300);
  freq_height[5] = fft.calcAvg((float) 301, (float) 360);
  freq_height[6] = fft.calcAvg((float) 361, (float) 430);
  freq_height[7] = fft.calcAvg((float) 431, (float) 520);
  freq_height[8] = fft.calcAvg((float) 521, (float) 700);
  
  for(i = 9; i < 64; i++)
  {
   freq_height[i] = fft.calcAvg((float) (501+(freq_width*(i-9))), (float) (700+(freq_width*(i-9))));
  }
  
  freq_height[64] = (fft.calcAvg((float) 20, (float) 60));
  
  
  // <-O-> Log scaling function. Feel free to adjust x and y
  
  float x = 8;
  float y = 3;
  for(i=0; i<64; i++)
  {    
    freq_height[i] = freq_height[i]*(log(x)/y);
    x = x + (x); 
  }
  

   

// Amplitude Ranges  if else tree
    for(i=0; i<64; i++){    
    if (freq_height[i] < 2000 && freq_height[i] > 400){height[i] = 16;}
    else{ if (freq_height[i] <= 400 && freq_height[i] > 300){height[i] = 15;}
    else{ if (freq_height[i] <= 300 && freq_height[i] > 220){height[i] = 14;}
    else{ if (freq_height[i] <= 220 && freq_height[i] > 140){height[i] = 13;}
    else{ if (freq_height[i] <= 140 && freq_height[i] > 120){height[i] = 12;}
    else{ if (freq_height[i] <= 120 && freq_height[i] > 100){height[i] = 11;}
    else{ if (freq_height[i] <= 100 && freq_height[i] > 80){height[i] = 10;}
    else{ if (freq_height[i] <= 80 && freq_height[i] > 70){height[i] = 9;}
    else{ if (freq_height[i] <= 70 && freq_height[i] > 60){height[i] = 8;}
    else{ if (freq_height[i] <= 60 && freq_height[i] > 50){height[i] = 7;}
    else{ if (freq_height[i] <= 50 && freq_height[i] > 40){height[i] = 6;}
    else{ if (freq_height[i] <= 40 && freq_height[i] > 30){height[i] = 5;}
    else{ if (freq_height[i] <= 30 && freq_height[i] > 20){height[i] = 4;}
    else{ if (freq_height[i] <= 20 && freq_height[i] > 15){height[i] = 3;}
    else{ if (freq_height[i] <= 15 && freq_height[i] > 10){height[i] = 2;}
    else{ if (freq_height[i] <= 10 && freq_height[i] > 5){height[i] = 1;}
    else{ if (freq_height[i] <= 5 && freq_height[i] > 0){height[i] = 0;}
  }}}}}}}}}}}}}}}}}
    

      
  arduino.write(0xff);
  arduino.write(height);
  

  } //while loop ends 
  
  
  
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI()
{

}

public void Start()
{
 arduino = new Serial(this, "COM7" , 9600);
 delay(2000);
}



void stop()
{
  // always close Minim audio classes when you finish with them
  in.close();
  minim.stop();
  super.stop();
  exit(); 
}