/*
 * mo52.c
 *
 * Created: 28-Nov-21 9:57:08 AM
 * Author : AHMAD
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include "util/delay.h"
#include  "uart.h"
#include "gpio.h"
#include "DC_Motor.h"
#include "Dio.h"
#include "Pwm.h"
#define F_CPU 16000000UL
int main(void)
{

	UART_configurations configs = {
		9600,
		BITS_5,
		NO_PARITY,
     	BITS_1
	};
	UART_init(&configs);
	uint8 val = 0;
	
    DcMotor_Init(DC_MOTOR1_IN1_PIN,DC_MOTOR1_IN2_PIN);
   DcMotor_Init(DC_MOTOR2_IN1_PIN,DC_MOTOR2_IN2_PIN);
	
    /* Replace with your application code */
    while (1) 
    {   
	
		val = UART_receiveByte();
			

		if (val == 17){
			DcMotor_Control(DC_MOTOR_TURN_CCW,DC_MOTOR_SPEED_MID,DC_MOTOR1_IN1_PIN,DC_MOTOR1_IN2_PIN);
			DcMotor_Control(DC_MOTOR_TURN_CW,DC_MOTOR_SPEED_MID,DC_MOTOR2_IN1_PIN,DC_MOTOR2_IN2_PIN);
			_delay_ms(300);
		}
		else if (val == 18){
	DcMotor_Control(DC_MOTOR_TURN_CW,DC_MOTOR_SPEED_MID,DC_MOTOR1_IN1_PIN,DC_MOTOR1_IN2_PIN);
			DcMotor_Control(DC_MOTOR_TURN_CCW,DC_MOTOR_SPEED_MID,DC_MOTOR2_IN1_PIN,DC_MOTOR2_IN2_PIN);
				_delay_ms(300);
		}
		else if (val == 19){
			DcMotor_Control(DC_MOTOR_TURN_CCW,DC_MOTOR_SPEED_MID,DC_MOTOR1_IN1_PIN,DC_MOTOR1_IN2_PIN);
			DcMotor_Control(DC_MOTOR_TURN_CCW,DC_MOTOR_SPEED_MID,DC_MOTOR2_IN1_PIN,DC_MOTOR2_IN2_PIN);
				_delay_ms(300);
		}
		else if (val == 20){
			DcMotor_Control(DC_MOTOR_TURN_CW,DC_MOTOR_SPEED_MID,DC_MOTOR1_IN1_PIN,DC_MOTOR1_IN2_PIN);
			DcMotor_Control(DC_MOTOR_TURN_CW,DC_MOTOR_SPEED_MID,DC_MOTOR2_IN1_PIN,DC_MOTOR2_IN2_PIN);
				_delay_ms(300);
		}
		else if (val == 21){
			DcMotor_Control(DC_MOTOR_TURN_CW,DC_MOTOR_SPEED_HIGH,DC_MOTOR1_IN1_PIN,DC_MOTOR1_IN2_PIN);
         	DcMotor_Control(DC_MOTOR_TURN_CW,DC_MOTOR_SPEED_HIGH,DC_MOTOR2_IN1_PIN,DC_MOTOR2_IN2_PIN);
			 	_delay_ms(300);
		}
		else	if (val == 22){
			DcMotor_Control(DC_MOTOR_TURN_CW,DC_MOTOR_SPEED_STOP,DC_MOTOR1_IN1_PIN,DC_MOTOR1_IN2_PIN);
			DcMotor_Control(DC_MOTOR_TURN_CCW,DC_MOTOR_SPEED_STOP,DC_MOTOR2_IN1_PIN,DC_MOTOR2_IN2_PIN);
				_delay_ms(300);
		}
    DcMotor_Control(DC_MOTOR_TURN_CW,DC_MOTOR_SPEED_STOP,DC_MOTOR1_IN1_PIN,DC_MOTOR1_IN2_PIN);
	DcMotor_Control(DC_MOTOR_TURN_CCW,DC_MOTOR_SPEED_STOP,DC_MOTOR2_IN1_PIN,DC_MOTOR2_IN2_PIN);

	}
}

