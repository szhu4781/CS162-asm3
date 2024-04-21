/******************************************************
** Program Filename: coffee.cpp
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: File defines class and functions declared in coffee.h
** Input: none
** Output: none
******************************************************/
#include "coffee.h"

using namespace std;

//default constructor
Coffee::Coffee(){
}

//non-default constructor
Coffee::Coffee(string name, float small_cost, float medium_cost, float large_cost){
    this->name = name;
    this->small_cost = small_cost;
    this->medium_cost = medium_cost;
    this->large_cost = large_cost;
}

/*********************************************************************
** Function: Coffee::set_name()
** Description: Sets the name of coffee
** Parameters: const string name - Name of coffee to set.
** Pre-Conditions: none
** Post-Conditions: Name of coffee is set to a specific value
*********************************************************************/
void Coffee::set_name(const string name){
    this->name = name;
}

/*********************************************************************
** Function: Coffee::set_small_cost()
** Description: Sets the cost of small size
** Parameters: const float small_cost - Cost of small size to set.
** Pre-Conditions: none
** Post-Conditions: Cost of small size is set to a specific value
*********************************************************************/
void Coffee::set_small_cost(const float small_cost){
    this->small_cost = small_cost;
}

/*********************************************************************
** Function: Coffee::set_med_cost()
** Description: Sets the cost of medium size
** Parameters: const float med_cost - Cost of medium size to set.
** Pre-Conditions: none
** Post-Conditions: Cost of medium size is set to a specific value
*********************************************************************/
void Coffee::set_med_cost(const float medium_cost){
    this->medium_cost = medium_cost;
}

/*********************************************************************
** Function: Coffee::set_large_cost()
** Description: Sets the cost of large size
** Parameters: const float large_cost - Cost of large size to set.
** Pre-Conditions: none
** Post-Conditions: Cost of large size is set to a specific value
*********************************************************************/
void Coffee::set_large_cost(const float large_cost){
    this->large_cost = large_cost;
}

/*********************************************************************
** Function: Coffee::get_name()
** Description: Gets name of coffee
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns name of coffee
*********************************************************************/
string Coffee::get_name() const {
    return name;
}

/*********************************************************************
** Function: Coffee::get_small_cost()
** Description: Gets cost of small size
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns cost of small size
*********************************************************************/
float Coffee::get_small_cost() const {
    return small_cost;
}

/*********************************************************************
** Function: Coffee::get_medium_cost()
** Description: Gets cost of medium size
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns cost of medium size
*********************************************************************/
float Coffee::get_med_cost() const {
    return medium_cost;
}

/*********************************************************************
** Function: Coffee::get_large_cost()
** Description: Gets cost of large size
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns cost of large size
*********************************************************************/
float Coffee::get_large_cost() const {
    return large_cost;
}

/*********************************************************************
** Function: Coffee::populate_coffee()
** Description: Reads data from file and populates coffee
** Parameters: ifstream& file - Input file stream
** Pre-Conditions: File stream is opened and positioned correctly
** Post-Conditions: The coffee is populated with data from file
*********************************************************************/
void Coffee::populate_coffee(ifstream& file){
    file >> this->name >> this->small_cost >> this->medium_cost >> this->large_cost;
}

/*********************************************************************
** Function: Coffee::print_coffee()
** Description: Prints details of coffee
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Coffee details are printed to console
*********************************************************************/
void Coffee::print_coffee() {
    cout << name << endl;
    cout << "   Small - $" << small_cost << endl;
    cout << "   Medium - $" << medium_cost << endl;
    cout << "   Large - $" << large_cost << endl;
}