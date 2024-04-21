/******************************************************
** Program Filename: order.h
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: File for Order class and function declarations.
** Input: none
** Output: none
******************************************************/
#ifndef ORDER_H
#define ORDER_H 

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Order
{
private:
	int id;
	string coffee_name;
	char coffee_size;
	int quantity;
public:
	//order constructors
	Order();
	Order(int id, string coffee_name, char coffee_size, int quantity);

	//Mutator functions
    void set_id(const int id);
    void set_coffee_name(const string coffee_name);
    void set_coffee_size(const char coffee_size);
    void set_quantity(const int quantity);

    //Accessor functions
    int get_id() const;
    string get_coffee_name() const;
    char get_coffee_size() const;
    int get_quantity() const;
	
	void populate_order(ifstream& file); //populate order data
	void print_order(); //print order object
};
#endif