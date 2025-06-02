#include "reg52.h"
 
sbit RightCon1A = P3^2;
sbit RightCon1B = P3^3;
 
sbit LeftCon1A = P3^4;
sbit LeftCon1B = P3^5;
 
void goForwardLeft()
{
  LeftCon1A = 0;
  LeftCon1B = 1;
}
 
void stopLeft()
{
  LeftCon1A = 0;
  LeftCon1B = 0;
}
 
void goForwardRight()
{
  RightCon1A = 0;
  RightCon1B = 1;
}
void stopRight()
{
  RightCon1A = 0;
  RightCon1B = 0;
}
 
 
 
void goForward()
{
  LeftCon1A = 0;
  LeftCon1B = 1;
  
  RightCon1A = 0;
  RightCon1B = 1;
}
 
void goRight()
{
  LeftCon1A = 0;
  LeftCon1B = 1;
  
  RightCon1A = 0;
  RightCon1B = 0;
}
 
 
void goLeft()
{
  LeftCon1A = 0;
  LeftCon1B = 0;
  
  RightCon1A = 0;
  RightCon1B = 1;
}
 
void goBack()
{
  LeftCon1A = 1;
  LeftCon1B = 0;
  
  RightCon1A = 1;
  RightCon1B = 0;
}
 
void stop()
{
  LeftCon1A = 0;
  LeftCon1B = 0;
  
  RightCon1A = 0;
  RightCon1B = 0;
}

