/******************************************************
** Program Filename: coffee.h
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: File for Coffee class and function declarations.
** Input: none
** Output: none
******************************************************/
#ifndef COFFEE_H
#define COFFEE_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Coffee {
  private:
    string name;
    float small_cost;
    float medium_cost;
    float large_cost;
    
  public:
    //Coffee constructors
    Coffee();
    Coffee(string name, float small_cost, float medium_cost, float large_cost);

    //Mutator functions
    void set_name(const string name);
    void set_small_cost(const float small_cost);
    void set_med_cost(const float medium_cost);
    void set_large_cost(const float large_cost);

    //Accessor functions
    string get_name() const;
    float get_small_cost() const;
    float get_med_cost() const;
    float get_large_cost() const;

    void populate_coffee(ifstream& file); //Populate coffee data
    void print_coffee(); //Print coffee object
};

#endif