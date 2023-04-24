#include "stm32g4xx.h"                  // Device header
#include "pid.h"
#include "control.h"
#include "STRUCT.h"
//加速度环PID
PID_TYPE PID_ROL_Angle;
PID_TYPE PID_PIT_Angle;
PID_TYPE PID_YAW_Angle;
//角速度环PID 
PID_TYPE PID_ROL_Rate;
PID_TYPE PID_PIT_Rate;
PID_TYPE PID_YAW_Rate;
//高度环PID 
PID_TYPE PID_ALT_Rate;
PID_TYPE PID_ALT;


