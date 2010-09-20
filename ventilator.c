 /****************************************************************
 *       SECU-3  - An open source, free engine control unit
 *    Designed by Alexey A. Shabelnikov. Ukraine, Gorlovka 2007.
 *       Microprocessors systems - design & programming.
 *    contacts:
 *              http://secu-3.narod.ru
 *              ICQ: 405-791-931
 ****************************************************************/

#include <ioavr.h>
#include "ventilator.h"
#include "secu3.h"

//��������/��������� ����������
#define SET_VENTILATOR_STATE(s) {PORTB_Bit1 = s;}


/*
//number of PWM discretes
#define PWM_STEPS 10

//MUST be same as in vstimer!
#define TIMER2_RELOAD_VALUE 100

volatile uint8_t pwm_state; //0 - passive, 1 - active
volatile uint8_t pwm_duty;
*/

void vent_init_ports(void)
{
 //������������� ����� �����/������       
 PORTB&= ~(1<<PB1);
 DDRB |= (1<<DDB1);   
}

void vent_init_state(void)
{ 
/* pwm_state = 0;
 pwm_duty = 0; // 0%
 OCR2 = TIMER2_RELOAD_VALUE + 5; 
 TIMSK|=(1 << OCIE2);*/
}

/*
void vent_set_duty(uint8_t duty)
{
 pwm_duty = duty;
 
 //We don't need interrupts if duty is 0 or 100%
// if (duty == 0)
// {
//  TIMSK&=~(1 << OCIE2);
//  SET_VENTILATOR_STATE(0);
// }
// else if (duty == PWM_STEPS)
// {
//  TIMSK&=~(1 << OCIE2);
//  SET_VENTILATOR_STATE(1);
// }
// else
//  TIMSK|=(1 << OCIE2);  
}

//���������� �� �������� �/� 2 - ��� ��������� ���
#pragma vector=TIMER2_COMP_vect
__interrupt void timer2_comp_isr(void)
{ 
  uint8_t r = OCR2;
  if (0==pwm_state)
  { //start active part
   SET_VENTILATOR_STATE(1);
   r+=pwm_duty;
   ++pwm_state;
  }
  else
  { //start passive part
   SET_VENTILATOR_STATE(0);
   r+=PWM_STEPS-pwm_duty;
   --pwm_state;   
  } 
  
  if (r < TIMER2_RELOAD_VALUE)
    r+=TIMER2_RELOAD_VALUE;
    
  OCR2 = r;
}
*/

void vent_control(struct ecudata_t *d)
{
 //���������� ������� ������������ ���������� ���������, ��� ������� ��� ���� ������������ � ������� 
 if (d->param.tmp_use)
 {
  if (d->sens.temperat >= d->param.vent_on)
   SET_VENTILATOR_STATE(1);
  if (d->sens.temperat <= d->param.vent_off)   
   SET_VENTILATOR_STATE(0); 
  }

 /* vent_set_duty(5);    */
}
