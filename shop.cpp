/******************************************************
** Program Filename: shop.cpp
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: File defines class and functions declared in shop.h
** Input: Function-specific inputs that lets user view shop details,
**		  add and remove menu items, search item by its name or price,
**		  place an order, and clone the shop.
** Output: Displays the corresponding info based on user inputs that 
** 		   relates to shop details, menu, and orders
******************************************************/
#include "shop.h"
#include "coffee.h"
#include "menu.h"
#include "order.h"

using namespace std;

//default constructor
Shop::Shop(){
	this->phone = "";
	this->address = "";
	this->revenue = 0.0;
	this->order_arr = nullptr;
	this->num_orders = 0;
}

//non-default constructor
Shop::Shop(string phone, string address, float revenue, Order *order_arr, int num_orders){
	this->phone = phone;
	this->address = address;
	this->revenue = revenue;
	this->order_arr = new Order[num_orders];
	this->num_orders = num_orders;
}

//CC
Shop::Shop(const Shop &clone) {
	this->phone = clone.phone;
	this->address = clone.address;
	this->revenue = clone.revenue;
	this->num_orders = clone.num_orders;

	this->order_arr = new Order[this->num_orders];
	for (int i = 0; i < this->num_orders; i++){
		this->order_arr[i] = order_arr[i];
	}
}

//AOO
Shop& Shop::operator=(const Shop &clone) {
	if (this != &clone){
		this->phone = clone.phone;
		this->address = clone.address;
		this->revenue = clone.revenue;
		this->num_orders = clone.num_orders;

		delete[] this->order_arr;

		this->order_arr = new Order[this->num_orders];
		for (int i = 0; i < this->num_orders; i++){
			this->order_arr[i] = order_arr[i];
		}		
	}
	return *this;
}

//destructor
Shop::~Shop(){
	//deallocate memory for order array to prevent memory leaks
	delete [] order_arr;
	this->order_arr = nullptr;
}

/*********************************************************************
** Function: Shop::load_menu()
** Description: Opens menu.txt and reads the info in the file
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Menu object is populated and printed
*********************************************************************/
void Shop::load_menu(){
	//Opens menu.txt and reads the info
	ifstream menu_info("menu.txt");
	if (menu_info.is_open()){
		this->m.populate_menu(menu_info);
		menu_info.close();
	}
	//error check
	else {
		cerr << "Error opening menu." << endl;
	}
	this->m.print_menu();
}

/*********************************************************************
** Function: Shop::load_orders()
** Description: Opens orders.txt and reads the info in the file
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Order array is populated
*********************************************************************/
void Shop::load_orders(){
	//Opens order.txt and reads for any info
	ifstream order_info("orders.txt");
	if (order_info.is_open()){
		//populate order info based on orders made
		for (int i = 0; i < num_orders; i++){
			order_arr[i].populate_order(order_info);
		}
		order_info.close();
	}
	//error check
	else {
		cerr << "Error loading orders." << endl;
	}
}

/*********************************************************************
** Function: Shop::load_data()
** Description: Opens shop_info.txt and reads the info in the file
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Shop object is populated with data
*********************************************************************/
void Shop::load_data(){
	//Reads info from "shop_info.txt"
	ifstream shop_info("shop_info.txt");
	if (shop_info.is_open()){
		//Prints phone number and address
		getline(shop_info, phone);	
		getline(shop_info, address);
	}
	load_menu(); //Call menu data
	load_orders(); //Call data of orders made
}

/*********************************************************************
** Function: Shop::add_order()
** Description: Adds a new order to the order array and updates order file
** Parameters: const Order& new_order - the order to be added
** Pre-Conditions: none
** Post-Conditions: Order array is updated with the new order placed
*********************************************************************/
void Shop::add_order(const Order& new_order){
	Order* new_order_arr = new Order[num_orders + 1];
	for (int i = 0; i < num_orders; i++){
		new_order_arr[i] = order_arr[i];
	}
	new_order_arr[num_orders] = new_order; 

	delete[] order_arr; //Deallocates memory of old order array

	order_arr = new_order_arr; //Updates old array with new array

	num_orders++; //Increments number of orders
	
	ofstream order_file("orders.txt");
	
	//Updates file with correct number of orders
	order_file << this->num_orders << endl;

	//Inputs order info when an order is made into the file
	for (int i = 0; i < num_orders; i++){
		order_file << new_order.get_id() << " "; 
		order_file << new_order.get_coffee_name() << " ";
		order_file << new_order.get_coffee_size() << " ";
		order_file << new_order.get_quantity() << endl;	
	}
	order_file.close();	
}

/*********************************************************************
** Function: Shop::find_best_seller()
** Description: Finds the best-selling coffee for a specific size based 
**				on quantity of orders
** Parameters: char size - Size of coffee drinks (s - small, m - medium, l - large)
** Pre-Conditions: Shop, menu, and orders must be initialized
** Post-Conditions: Returns the best-selling coffee of specific sizes
*********************************************************************/
Coffee Shop::find_best_seller(char size){
	int max_Q = -1; 
	Coffee best_seller;

	//Iterates to get number of coffee
	for (int i = 0; i < m.get_num_coffee(); i++){
		float total_Q = 0.0;

		//Iterates through number of orders to check for any orders placed
		for (int j = 0; j < num_orders; j++){

			//Checks if the order's coffee size and name matches the current coffee item from menu
			if (order_arr[j].get_coffee_size() == size && order_arr[j].get_coffee_name() == m.get_coffee_name(i)){
				total_Q += order_arr[j].get_quantity(); //Adds quantity to total quantity
			}
		}

		//Updates total quantity if total quantity is greater
		if (total_Q > max_Q){
			max_Q = total_Q; //Updates max quantity to new max quantity
			best_seller = m.get_coffee_by_index(i); //Update best selling item to the current item
		}
	}
	return best_seller; //Return best selling coffee item
}

/*********************************************************************
** Function: Shop::print_top_drinks()
** Description: Finds the top 3 popular drinks based on total revenue
** Parameters: int n - Number of top drinks that needs to be displayed
** Pre-Conditions: Shop, menu, and orders must be initialized
** Post-Conditions: Returns the top 3 popular drinks based on total revenue made
*********************************************************************/
void Shop::print_top_drinks(int n){	
	//Arrays used to store the top n drinks
	string* top_drinks = new string[n];
	float* top_rev = new float[n];

	//Initialize arrays with default values
	for (int i = 0; i < n; i++){
		top_drinks[i] = "";
		top_rev[i] = -1.0;
	}

	//Iterate through menu to calculate total revenue
	for (int i = 0; i< m.get_num_coffee(); i++){
		float total = 0.0;

		//Iterate through order array to find matching drinks and calculate total revenue
		for (int j = 0; j < num_orders; j++){
			if (order_arr[j].get_coffee_name() == m.get_coffee_name(i)){
				total += order_arr[j].get_quantity() * m.get_coffee_price(i, order_arr[j].get_coffee_size());
			}
		}

		//Update top drinks array if a new drink is found
		for (int k = 0; k < n; k++){
			if (total > top_rev[k]){
				
				//Shift top drinks down to make room for new top drink
				for (int l = 0; l > k; l--){
					top_drinks[l] = top_drinks[l - 1];
					top_rev[l] = top_rev[l - 1];
				}

				//Add new top drinks to array
				top_drinks[k] = m.get_coffee_name(i);
				top_rev[k] = total;
				break;
			}
		}
	}

	//Prints out top popular drinks
	cout << endl << "Top " << n << " Popular Drinks" << endl;;
	
	//Displays top drinks that makes the most revenue
	for (int i = 0; i < n; i++){
		cout << i + 1 << ". " << top_drinks[i] << " - $" << top_rev[i] << endl;
	}

	//Deallocates memory of top drinks and top revenue arrays
	delete[] top_drinks;
	delete[] top_rev;
}

/*********************************************************************
** Function: Shop::view_shop_detail()
** Description: Prints out shop info, menu, and order info
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Shop details are printed
*********************************************************************/
void Shop::view_shop_detail(){
	//Prints out shop info here
	cout << "Phone Number: " << phone << endl;
	cout << "Address: " << address << endl; 
	cout << "The shop revenue is: $" << revenue << endl << endl;

	//Prints menu after shop info
	cout << "Here is our menu: " << endl;
	m.print_menu();

	//Prints order info after the shop menu
	cout << endl << "Order info: " << endl;
	//Prints out message if no orders have been placed
	if (num_orders == 0){
		cout << "No orders to be displayed!" << endl << endl;;
	}
	//Prints the orders made if orders have been placed
	else {
		for (int i = 0; i < num_orders; i++){
			order_arr[i].print_order();
		}
	}

	//Checks if any order is made before displaying best selling drinks
	if (num_orders ==  0 || m.get_num_coffee() == 0){
		cerr << "No orders placed to determine best-sellers." << endl;
	}
	//Prints out the best selling drinks if an order is made
	else {
		/*For some reason, the first coffee item on the menu is set as a placeholder whenever
		a new order is made. Not sure it this is something to do with how my for loops
		are set up in the best selling drinks function.*/
		cout << "Best selling drinks at the moment: " << endl;
		find_best_seller('s').print_coffee(); //Small size drinks
		find_best_seller('m').print_coffee(); //Medium size drinks
		find_best_seller('l').print_coffee(); //Large size drinks		
	}

	//Checks for any orders made, if there are no orders, print error message
	if (m.get_num_coffee() == 0 || num_orders == 0){
		cerr << endl << "No orders placed to determine top 3 drinks." << endl;
	}
	else {
		//Print the top drinks
		print_top_drinks(3);
	}
}

/*********************************************************************
** Function: Shop::add_to_menu()
** Description: Prompts user to add a new coffee item to the menu
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: New coffee item is added to the menu
*********************************************************************/
void Shop::add_to_menu(){
	string word;
	float small_cost, medium_cost, large_cost;

	//Asks user to input a name and prices of different sizes (small, medium, large)
	cout << "Enter the name of the new coffee drink (1 word): " << endl;
	cin >> word;
	
	//Print statements to prompt user to enter a price for each drink size
	cout << "Enter price of small size (8oz): ";
	cin >> small_cost;

	cout << "Enter price of medium size (16oz): ";
	cin >> medium_cost;	

	cout << "Enter price of large size (24oz): ";
	cin >> large_cost;

	//Calls add_to_menu and also adds the new item to the menu
	Coffee add_coffee(word, small_cost, medium_cost, large_cost);
	this->m.add_to_menu(add_coffee);

	cout << "This new drink has been successfully added to the coffee menu!" << endl;
}

/*********************************************************************
** Function: Shop::remove_from_menu()
** Description: Prompts user to remove a coffee item from the menu
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Coffee item is removed from the menu
*********************************************************************/
void Shop::remove_from_menu(){
	m.print_menu(); //Print menu for user to decide what to remove

	//Prompts user on which item they want to remove
	//Asks user for a number
	int index = -1;
	cout << "Which of the drinks above from our menu would you like to remove?" << endl;
	cout << "Enter a number corresponding to the item." << endl;
	cin >> index;
	
	//Error handling if user inputs something that isn't on the menu
	while (index < 1 || index > m.get_num_coffee()){
		cout << "Item doesn't exist! Please try again." << endl;
		return;
	}

	this->m.remove_from_menu(index - 1);

	cout << "This drink has been successfully removed from our menu!" << endl;
}

/*********************************************************************
** Function: Shop::search_by_name()
** Description: Prompts user to search up a name of a coffee item from the menu
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Coffee item is searched and results are printed
*********************************************************************/
void Shop::search_by_name(){
	//Prompts user to input coffee name
	string coffee_name;
	cout << "Enter a coffee name: ";
	cin >> coffee_name;

	//Takes user input into count for coffee name
	Coffee found = m.search_coffee_by_name(coffee_name);
	//Checks if the name of coffee is within the list of coffees in menu
	cout << "Results: " << endl;	
	if (found.get_name() != ""){
		found.print_coffee(); //Calls print coffee function to print out the results
	}
	//Checks if user enters an non-existing item
	else {
		cout << "Sorry, we don't have that product at the moment." << endl;
	}
}

/*********************************************************************
** Function: Shop::search_by_price()
** Description: Prompts user to search a coffee within a price range
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Coffee item is search and results are printed
*********************************************************************/
void Shop::search_by_price(){
	//Prompts for user input
	float price;
	cout << "Enter your budget for one drink, and I will list out our products below or equal to your budget: " << endl;
	cin >> price;

	//Menu takes in user input into account
	Menu price_res = m.search_coffee_by_price(price);
	
	//Checks if the user enters a positive value
	if (price_res.get_num_coffee() > 0){
		price_res.print_menu(); //Prints out the menu based on the user's input
	}
	else {
		cout << "Error. Please try again. (Non-positive values not accepted)." << endl;
		return;
	}
}

/*********************************************************************
** Function: Shop::place_order()
** Description: Prompts user to place an order
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Order is placed and shop details are updated
*********************************************************************/
void Shop::place_order() {
	m.print_menu();

	int input;
	cout << "Which of the drinks from above would you like to order?" << endl;
	cout << "Enter a number corresponding to the item." << endl;
	cin >> input;

	//Error handling
	if (input < 1 || input > m.get_num_coffee()){
		cout << "Item not located on menu!" << endl;
		return;
	}

	string coffee_name = m.get_coffee_name(input - 1);

	char coffee_size;
	int quantity;

	//Asks for size of drink
	cout << "Enter the size: s-small, m-medium, l-large: " << endl;
	cin >> coffee_size;

	//Calculates item price based on quantity and item ordered
	float cof_cost = m.get_coffee_price(input - 1, coffee_size);
	if (cof_cost == -1.0){
		cout << "Error calculating price." << endl;
		return;
	}

	//Asks for quantity of items
	cout << "Enter quantity: " << endl;
	cin >> quantity;

	float total = cof_cost * quantity; //Total cost is set to cost of item multiplied by quantity of items
	revenue += total; //Adds total to the shop revenue

	//Order confirmation
	char con_input;
	cout << "Your total cost is: $" << total << endl;
	cout << "Confirmed? y-yes, n-no" << endl;
	cin >> con_input;

	//Checks if the user confirmed their order or not
	if (con_input == 'y'){
		Order new_order(num_orders + 1, coffee_name, coffee_size, quantity);
		add_order(new_order);
		cout << "Your order has been placed. Your order number is " << num_orders << endl;
	}
	else{
		cout << "Your order has been cancelled." << endl;
		return;
	}
}

/*********************************************************************
** Function: Shop::clone_shop()
** Description: Clones the current shop object
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Shop object is cloned and returned
*********************************************************************/
Shop Shop::clone_shop() {
	Shop cloned_shop = Shop(); // test CC  
	cloned_shop = *this;

    Shop cloned_shop2 = *this; // test AOO

    cout << "Shop cloned successfully!" << endl; 

    return cloned_shop;
}