#include <webots/robot.h>
#include <webots/distance_sensor.h>
#include "distance.h"

float chekingForObstacle(float a, WbDeviceTag b) {
    a=((wb_distance_sensor_get_value(b)*5)/1660);
    return a;
}
