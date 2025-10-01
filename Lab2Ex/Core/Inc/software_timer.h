/*
 * software_timer.h
 *
 *  Created on: Sep 28, 2025
 *      Author: ngoqu
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

const int TIMER_SIZE;
extern int timer_counter[];
extern int timer_flag[];
extern int TIMER_CYCLE;


void setTimers(int);
void setTimer(int,int);
void timer_run();


#endif /* INC_SOFTWARE_TIMER_H_ */
