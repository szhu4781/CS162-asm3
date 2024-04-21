/******************************************************
** Program Filename: order.cpp
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: File defines class and functions declared in order.h
** Input: none
** Output: none
******************************************************/
#include "order.h"

using namespace std;

//Default constructor
Order::Order(){
    id = 0;
    coffee_name = "";
    coffee_size = ' ';
    quantity = 0;
}

//Non-default constructor
Order::Order(int id, string coffee_name, char coffee_size, int quantity){
    this->id = id;
    this->coffee_name = coffee_name;
    this->coffee_size = coffee_size;
    this->quantity = quantity;
}

/*********************************************************************
** Function: Order::set_id()
** Description: Sets the ID number for a order.
** Parameters: const int id - ID to set.
** Pre-Conditions: none
** Post-Conditions: Order ID is set to a specific value.
*********************************************************************/
void Order::set_id(const int id){
    this->id = id;
}

/*********************************************************************
** Function: Order::set_coffee_name()
** Description: Sets the coffee name for a order.
** Parameters: const string coffee_name - Coffee name to set.
** Pre-Conditions: none
** Post-Conditions: Name of coffee is set to specific value
*********************************************************************/
void Order::set_coffee_name(const string coffee_name){
    this->coffee_name = coffee_name;
}

/*********************************************************************
** Function: Order::set_coffee_size()
** Description: Sets the coffee size for a order.
** Parameters: const char coffee_size - Coffee size to set.
** Pre-Conditions: none
** Post-Conditions: Size of coffee is set to a specific value.
*********************************************************************/
void Order::set_coffee_size(const char coffee_size){
    this->coffee_size = coffee_size;
}

/*********************************************************************
** Function: Order::set_quantity()
** Description: Sets the quantity for a order.
** Parameters: const int quantity - 
** Pre-Conditions: none
** Post-Conditions: Quantity is set to a specific value.
*********************************************************************/
void Order::set_quantity(const int quantity){
    this->quantity = quantity;
}

/*********************************************************************
** Function: Order::get_id()
** Description: Gets the ID number for a order.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns order ID.
*********************************************************************/
int Order::get_id() const {
    return id;
}

/*********************************************************************
** Function: Order::get_coffee_name()
** Description: Gets the name of coffee for a order.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns coffee name.
*********************************************************************/
string Order::get_coffee_name() const {
    return coffee_name;
}

/*********************************************************************
** Function: Order::get_coffee_size()
** Description: Gets the coffee size for a order.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns coffee size.
*********************************************************************/
char Order::get_coffee_size() const {
    return coffee_size;
}

/*********************************************************************
** Function: Order::get_quantity()
** Description: Gets the quantity for a order.
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns quantity.
*********************************************************************/
int Order::get_quantity() const {
    return quantity;
}

/*********************************************************************
** Function: Order::populate_order()
** Description: Reads data from file and populates order
** Parameters: ifstream& file - Input file stream
** Pre-Conditions: File stream is opened and positioned correctly
** Post-Conditions: The order is populated with data from file
*********************************************************************/
void Order::populate_order(ifstream& file){
    file >> id >> coffee_name >> coffee_size >> quantity;
}

/*********************************************************************
** Function: Order::print_order()
** Description: Prints details of order made
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Order details are printed to console
*********************************************************************/
void Order::print_order(){
    cout << "Order #: " << id << " ";
    cout << coffee_name << " ";
    cout << coffee_size << " ";
    cout << quantity << endl;
}