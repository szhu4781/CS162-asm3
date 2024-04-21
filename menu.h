/******************************************************
** Program Filename: menu.h
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: File for Menu class and function declarations.
** Input: none
** Output: none
******************************************************/
#ifndef MENU_H
#define MENU_H 

#include <string>
#include <fstream>
#include <iostream>
#include "coffee.h"

using namespace std;

class Menu {
  private:
    int num_coffee;
    Coffee* coffee_arr;
  public:
    //Menu constructors
    Menu();
    Menu(int num_coffee, Coffee* coffee_arr);

    //Menu destructor
    ~Menu();

    int get_num_coffee(); //Gets number of coffees; used for error handling for shop
    string get_coffee_name(int index); //Gets name of coffee; used for placing orders
    float get_coffee_price(int index, char size); //gets price of coffee;
    Coffee get_coffee_by_index(int index) const; //gets index of coffee;

    void add_to_menu(Coffee& coffee_to_add); //add a coffee object into the Menu
    void remove_from_menu(int index_of_coffee_on_menu); //remove a coffee object from the Menu
    Coffee search_coffee_by_name(string name); //search coffee by name from coffee array
    Menu search_coffee_by_price(float budget); //search coffee by price

    
    void populate_menu(ifstream& file); //populate menu data using text file
    void print_menu(); //print populated menu data
};

#endif