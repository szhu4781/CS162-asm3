/******************************************************
** Program Filename: main.cpp
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: Main file for where the program is ran
** Input: User inputs through the console/terminal or wherever the program is executed
** Output: Displayed info corresponding to user choices, 
** 		   updates to menu and orders based on user inputs
******************************************************/
#include <iostream>
#include "display.h"

using namespace std;

/*********************************************************************
** Function: main()
** Description: Main function for running the program
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Program is execute allowing user interaction
*********************************************************************/
int main()
{
	//your main function lives here
	cout << "Welcome to Coffee++" << endl;
	int choice = -1;
	Shop s;
	//populate your Shop:
	//your code here:
	s.load_data();

	while (choice != QUIT){
		choice = get_choice();
		perform_action(s, choice);
	}

	cout << "Bye!" << endl;

	return 0;
}
