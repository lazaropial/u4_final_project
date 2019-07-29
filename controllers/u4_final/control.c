#include "control.h"

float control(float vref, float v, float up, float ui, float kp, float ki,float e,float ea) {
  kp=2;
  ki=0.15;
  e=vref-v;
  up=kp*e;
  ea=ea+e;
  ui=ki*ea;
  return (up+ui);
}
