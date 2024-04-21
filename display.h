/******************************************************
** Program Filename: display.h
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: File for calling user choice options
** Input: none
** Output: none
******************************************************/
#ifndef DISPLAY_H
#define DISPLAY_H

#include "shop.h"

#define QUIT 8

/* name: get_choice()
 * description: get an user input for option
 * parameters: none
 * pre-condition: none
 * post-conditon: a choice (1-8) is returned
 */
int get_choice();

/* name: perform_action()
 * description: perform an action based on user input
 * parameters: 	Shop &s - a reference to the Shop obj
 				int choice - user input for an option
 * pre-condition: choice is 1-8
 * post-conditon: an option is performed
 */
void perform_action(Shop &s, int choice);

#endif
