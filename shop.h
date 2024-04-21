/******************************************************
** Program Filename: shop.h
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: File for Shop class and function declarations.
** Input: none
** Output: none
******************************************************/
#ifndef SHOP_H
#define SHOP_H

#include <string>
#include <fstream>
#include <iostream>
#include "menu.h"
#include "order.h"
#include "coffee.h"

using namespace std;

class Shop {
  private:
    Menu m;
    string phone;
    string address; 
    float revenue;      //shop revenue
    Order *order_arr;   //order array
    int num_orders;     //number or orders
  public:
    //constructors
    Shop();
    Shop(string phone, string address, float revenue, Order *order_arr, int num_orders);

    //Copy constructor
    Shop(const Shop&);

    //AOO
    Shop &operator=(const Shop&);
    
    //destructor
    ~Shop();

    void load_menu(); //reads from menu text file
    void load_orders(); //reads from order text file
    void load_data(); //reads from files to correctly populate coffee, menu, etc.
    void add_order(const Order &new_order); //adds any new orders to a list of orders to be displayed along with shop info
    Coffee find_best_seller(char size); //finds best selling item
    void print_top_drinks(int n); //prints top 3 drinks based on revenue

    void view_shop_detail(); //prints out shop info from user input
    void add_to_menu(); //lets user add item to menu
    void remove_from_menu(); //lets user remove item from menu
    void search_by_name(); //lets user search name of coffee
    void search_by_price(); //lets user search item by price
    void place_order(); //lets user place an order
    Shop clone_shop(); //clones shop by copying the details of the original shop
    
};

#endif
