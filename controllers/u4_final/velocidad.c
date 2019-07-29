#include <webots/robot.h>
#include <webots/position_sensor.h>
#include "velocidad.h"

#define RADIO 0.075

double d=0;
float a,b,c;

float velocidad(WbDeviceTag b) {
  a = wb_position_sensor_get_value(b);
  c = ((a - d)/0.064)*RADIO;
  d=a;
  return (c);
}
