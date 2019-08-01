/*
* File: u4_project.c
* Date: 26 de julio del 2019
* Description:
* Author: Lazaro Piñeiro Alcocer, David Gonzalez, Victor Xix
* Modifications:
*/
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>
#include <webots/keyboard.h>

#include <stdio.h>

#include <distance.h>
#include <velocidad.h>
#include <control.h>

#define TIME_STEP 64
#define PI 3.1416
#define VELOCITY 4

enum {
  AUTOMATIC,
  MANUAL
};
/*variables globales*/
double left_distance_sensor,right_distance_sensor,vel_robot;
int veces, veces2=0;
short int robot_state;
int paro;
double robot_velocity;

void stopRobot(WbDeviceTag wheel1,WbDeviceTag wheel2,WbDeviceTag wheel3,
               WbDeviceTag wheel4) {
  wb_motor_set_velocity(wheel1, 0);
  wb_motor_set_velocity(wheel2, 0);
  wb_motor_set_velocity(wheel3, 0);
  wb_motor_set_velocity(wheel4, 0);
}

void forwardRobot(WbDeviceTag wheel1,WbDeviceTag wheel2,WbDeviceTag wheel3,
                  WbDeviceTag wheel4) {
  wb_motor_set_velocity(wheel1, -VELOCITY);
  wb_motor_set_velocity(wheel2, -VELOCITY);
  wb_motor_set_velocity(wheel3, -VELOCITY);
  wb_motor_set_velocity(wheel4, -VELOCITY);
}

void backwardRobot(WbDeviceTag wheel1,WbDeviceTag wheel2,WbDeviceTag wheel3,
                   WbDeviceTag wheel4) {
  wb_motor_set_velocity(wheel1, VELOCITY);
  wb_motor_set_velocity(wheel2, VELOCITY);
  wb_motor_set_velocity(wheel3, VELOCITY);
  wb_motor_set_velocity(wheel4, VELOCITY);
}

void leftRobot(WbDeviceTag wheel1,WbDeviceTag wheel2,WbDeviceTag wheel3,
               WbDeviceTag wheel4) {
  wb_motor_set_velocity(wheel1, VELOCITY);
  wb_motor_set_velocity(wheel2, -VELOCITY);
  wb_motor_set_velocity(wheel3, -VELOCITY);
  wb_motor_set_velocity(wheel4, VELOCITY);
}

void rightRobot(WbDeviceTag wheel1,WbDeviceTag wheel2,WbDeviceTag wheel3,
                WbDeviceTag wheel4) {
  wb_motor_set_velocity(wheel1, -VELOCITY);
  wb_motor_set_velocity(wheel2, VELOCITY);
  wb_motor_set_velocity(wheel3, VELOCITY);
  wb_motor_set_velocity(wheel4, -VELOCITY);
}

void turnRightRobot(WbDeviceTag wheel1,WbDeviceTag wheel2,WbDeviceTag wheel3,
                    WbDeviceTag wheel4) {
  wb_motor_set_velocity(wheel1, -0.785398);
  wb_motor_set_velocity(wheel2, 0.785398);
  wb_motor_set_velocity(wheel3, -0.785398);
  wb_motor_set_velocity(wheel4, 0.785398);
}

void turnLeftRobot(WbDeviceTag wheel1,WbDeviceTag wheel2,WbDeviceTag wheel3,
                   WbDeviceTag wheel4) {
  wb_motor_set_velocity(wheel1, 0.785398);
  wb_motor_set_velocity(wheel2, -0.785398);
  wb_motor_set_velocity(wheel3, 0.785398);
  wb_motor_set_velocity(wheel4, -0.785398);
}

void autonomousMode (WbDeviceTag wheel1,WbDeviceTag wheel2,WbDeviceTag wheel3,
                     WbDeviceTag wheel4,WbDeviceTag ds_l, WbDeviceTag ds_r) {

  left_distance_sensor=chekingForObstacle(left_distance_sensor,ds_l);
  right_distance_sensor=chekingForObstacle(right_distance_sensor,ds_r);

  wb_motor_set_position(wheel1, INFINITY);
  wb_motor_set_velocity(wheel1, -5.5);
  wb_motor_set_position(wheel2, INFINITY);
  wb_motor_set_velocity(wheel2, -5.5);
  wb_motor_set_position(wheel3, INFINITY);
  wb_motor_set_velocity(wheel3, -5.5);
  wb_motor_set_position(wheel4, INFINITY);
  wb_motor_set_velocity(wheel4, -5.5);

  if (right_distance_sensor<=0.17&&right_distance_sensor<left_distance_sensor) {
  veces++;
  }
  if (veces>=1 && veces<=137) {
  turnRightRobot(wheel1, wheel2, wheel3,wheel4);
  veces++;
  } else {
  veces=0;
}

  if (left_distance_sensor<0.17&&left_distance_sensor<right_distance_sensor) {
  veces2++;
  }
  if (veces2>=1 && veces2<=149) {
  turnLeftRobot(wheel1, wheel2, wheel3,wheel4);
  veces2++;
  } else {
  veces2=0;
}
}

int main(int argc, char **argv) {
  wb_robot_init();

  WbDeviceTag wheel1 = wb_robot_get_device("motor1");
  WbDeviceTag wheel2 = wb_robot_get_device("motor2");
  WbDeviceTag wheel3 = wb_robot_get_device("motor3");
  WbDeviceTag wheel4 = wb_robot_get_device("motor4");

  /////////position sensor//////////
  WbDeviceTag ps1 = wb_robot_get_device("pos1");
  WbDeviceTag ps2 = wb_robot_get_device("pos2");
  WbDeviceTag ps3 = wb_robot_get_device("pos3");
  WbDeviceTag ps4 = wb_robot_get_device("pos4");
  wb_position_sensor_enable(ps1, TIME_STEP);
  wb_position_sensor_enable(ps2, TIME_STEP);
  wb_position_sensor_enable(ps3, TIME_STEP);
  wb_position_sensor_enable(ps4, TIME_STEP);

  ///////////distance sensor/////////
  WbDeviceTag ds_l = wb_robot_get_device("distance_sensor");
  WbDeviceTag ds_r = wb_robot_get_device("distance_sensor2");
  wb_distance_sensor_enable(ds_l, TIME_STEP);
  wb_distance_sensor_enable(ds_r, TIME_STEP);

  wb_keyboard_enable(TIME_STEP);

  while (wb_robot_step(TIME_STEP) != -1) {

    left_distance_sensor=chekingForObstacle(left_distance_sensor,ds_l);
    right_distance_sensor=chekingForObstacle(right_distance_sensor,ds_r);

    robot_velocity=velocidad(ps1);

    int key=wb_keyboard_get_key();

    if (key == 'G' || robot_state == AUTOMATIC) {
      autonomousMode(wheel1,wheel2,wheel3,wheel4,ds_l,ds_r);
      robot_state = AUTOMATIC;
    }

    if (key == 'W') {
      robot_state=MANUAL;
      stopRobot(wheel1,wheel2,wheel3,wheel4);
    }
    if (key == WB_KEYBOARD_LEFT && robot_state == MANUAL) {
      paro=key;
      leftRobot(wheel1,wheel2,wheel3,wheel4);
    }

    if (paro != key && robot_state == MANUAL) {
      stopRobot(wheel1,wheel2,wheel3,wheel4);
    }

    if (key==WB_KEYBOARD_UP && robot_state == MANUAL) {
      forwardRobot(wheel1,wheel2,wheel3,wheel4);
    }

    if(key==WB_KEYBOARD_DOWN && robot_state == MANUAL) {
      backwardRobot(wheel1,wheel2,wheel3,wheel4);
    }

    if(key==WB_KEYBOARD_RIGHT && robot_state == MANUAL) {
      rightRobot(wheel1,wheel2,wheel3,wheel4);
    }

    if(key=='A' && robot_state == MANUAL) {
      turnLeftRobot(wheel1,wheel2,wheel3,wheel4);
    }

    if(key=='S' && robot_state == MANUAL) {
      turnRightRobot(wheel1,wheel2,wheel3,wheel4);
    }

    printf("vel=%f m/s\n",robot_velocity);

    };

  wb_robot_cleanup();

  return 0;
  }
