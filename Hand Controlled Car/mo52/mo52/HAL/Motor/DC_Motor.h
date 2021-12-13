/*
 * DC_Motor.h
 *
 * Created: 10/15/2021 1:30:05 AM
 *  Author: Abdelaziz Moustafa
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "Dio.h"
#include "ATmega32_Cfg.h"


#define DC_MOTOR_DIR_REG        (PORTC_DIR_REG)
#define DC_MOTOR_OUT_REG        (PORTC_OUT_REG)
#define DC_MOTOR1_IN1_PIN        (DIO_PIN0)
#define DC_MOTOR1_IN2_PIN        (DIO_PIN1)

#define DC_MOTOR2_IN1_PIN        (DIO_PIN2)
#define DC_MOTOR2_IN2_PIN        (DIO_PIN3)

#define DC_MOTOR_EN_DIR_REG     (PORTD_DIR_REG)
#define DC_MOTOR_EN_PIN         (DIO_PIN5)
typedef enum
{
	DC_MOTOR_TURN_CW,
	DC_MOTOR_TURN_CCW
}DcMotor_RotationDirType;

typedef enum
{DC_MOTOR_SPEED_STOP,
	DC_MOTOR_SPEED_LOW,
	DC_MOTOR_SPEED_MID,
	DC_MOTOR_SPEED_HIGH
}DcMotor_SpeedType;

void DcMotor_Init(uint8 pin1, uint8 pin2 );
void DcMotor_Control(DcMotor_RotationDirType Dir, DcMotor_SpeedType Speed,uint8 pin1, uint8 pin2);

#endif /* DC_MOTOR_H_ */