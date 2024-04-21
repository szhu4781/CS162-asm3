/******************************************************
** Program Filename: menu.cpp
** Author: Shengwei Zhu
** Date: 11/10/2023
** Description: File defines class and functions declared in menu.h
** Input: none
** Output: none
******************************************************/
#include "menu.h"
#include "coffee.h"

using namespace std;

//function defintions from menu.h goes here

//Default constructor
Menu::Menu(){
	num_coffee = 0;
	coffee_arr = nullptr;
}

//Non-default constructor
Menu::Menu(int num_coffee, Coffee* coffee_arr){
	this->num_coffee = num_coffee;
	this->coffee_arr = new Coffee[num_coffee];
	for (int i = 0; i < num_coffee; i++){
		this->coffee_arr[i] = coffee_arr[i];
	}
}

//Destructor
Menu::~Menu(){
	delete[] this->coffee_arr;
}

/*********************************************************************
** Function: Menu::get_num_coffee()
** Description: Gets the number of coffee
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Returns the number of coffees
*********************************************************************/
int Menu::get_num_coffee(){
	return num_coffee;
}

/*********************************************************************
** Function: Menu::get_coffee_name()
** Description: Gets the name of coffee for the menu
** Parameters: int index - index of the coffee item
** Pre-Conditions: Index should be within a valid range
** Post-Conditions: Returns the name of coffee or an empty string if index is unreachable
*********************************************************************/
string Menu::get_coffee_name(int index){
	if (index >= 0 && index < num_coffee){
		return coffee_arr[index].get_name();
	}
	else {
		return "";
	}
}

/*********************************************************************
** Function: Menu::get_coffee_price()
** Description: Gets the prices of coffee for the menu
** Parameters: int index - index of the coffee item
**			   char size - size of the coffee item
** Pre-Conditions: Index should be within a valid range; size should be s, m, or l
** Post-Conditions: Returns the prices of coffee for specific size or -1.0 if index is unreachable
*********************************************************************/
float Menu::get_coffee_price(int index, char size){
	if (index >= 0 && index < num_coffee){
		if (size == 's'){
			return coffee_arr[index].get_small_cost();
		}
		else if (size == 'm'){
			return coffee_arr[index].get_med_cost();
		}
		else if (size =='l'){
			return coffee_arr[index].get_large_cost();
		}
	}
	return -1.0;
}


Coffee Menu::get_coffee_by_index(int index) const {
	if (index >= 0 && index < num_coffee){
		return coffee_arr[index];
	}
	else {
		cout << "Error";
		return Coffee();
	}
}

/*********************************************************************
** Function: Menu::add_to_menu()
** Description: Adds a new coffee item to the mneu
** Parameters: Coffee& coffee_to_add - the coffee item to add
** Pre-Conditions: none
** Post-Conditions: Shop menu is updated with the new coffee added onto the menu
*********************************************************************/
void Menu::add_to_menu(Coffee& coffee_to_add){
	//Increase size of array when new coffee item gets added
	Coffee* new_coffee_arr = new Coffee[num_coffee + 1];

	//Copy elements from old array
	for (int i = 0; i < this->num_coffee; i++){
		new_coffee_arr[i] = this->coffee_arr[i];
	}

	//New coffee item is added to the end of array
	new_coffee_arr[num_coffee] = coffee_to_add;

	//Delete old array to prevent memory leaks
	delete[] coffee_arr;

	//Coffee array is updated with the new version
	this->coffee_arr = new_coffee_arr;

	//Number of coffee items on menu increases
	this->num_coffee++;

	//Updates file with the correct number of items
	ofstream update_file("menu.txt");
	update_file << this->num_coffee << endl;
	for (int i = 0; i < num_coffee; i++){
		update_file << this->coffee_arr[i].get_name() << " ";
		update_file << this->coffee_arr[i].get_small_cost() << " ";
		update_file << this->coffee_arr[i].get_med_cost() << " ";
		update_file << this->coffee_arr[i].get_large_cost() << endl;
	}
	update_file.close();
} 

/*********************************************************************
** Function: Menu::remove_from_menu()
** Description: Removes a new coffee item to the menu
** Parameters: int index_of_coffee_on_menu - index of coffee being removed
** Pre-Conditions: none
** Post-Conditions: Shop menu is updated with the coffee removed from the menu
*********************************************************************/
void Menu::remove_from_menu(int index_of_coffee_on_menu){
	//Decrease array size when new coffee item gets added
	Coffee* new_coffee_arr = new Coffee[num_coffee - 1];

	//Copy elements from the old array
	for (int i = 0; i < index_of_coffee_on_menu; i++){
		new_coffee_arr[i] = this->coffee_arr[i];
	}

	//Copy elements after a coffee item is removed
	for (int i = index_of_coffee_on_menu + 1; i < num_coffee; i++){
		new_coffee_arr[i - 1] = coffee_arr[i];
	}

	//Delete old array to prevent leaks
	delete[] coffee_arr;

	//Updates old coffee array with new one
	this->coffee_arr = new_coffee_arr;

	//Decreases the number of coffees on the menu
	this->num_coffee--;

	ofstream update_file("menu.txt");
	
	//Updates file with the correct number of items	
	update_file << this->num_coffee << endl;
	
	//Goes through coffee array to get the info and updates the file with the right info
	for (int i = 0; i < num_coffee; i++){
		update_file << this->coffee_arr[i].get_name() << " ";
		update_file << this->coffee_arr[i].get_small_cost() << " ";
		update_file << this->coffee_arr[i].get_med_cost() << " ";
		update_file << this->coffee_arr[i].get_large_cost() << endl;
	}
	update_file.close();
} 

/*********************************************************************
** Function: Menu::search_by_name()
** Description: Searches coffee by its name on the menu
** Parameters: string name - name of coffee being searched
** Pre-Conditions: none
** Post-Conditions: If a coffee is found, it is returned with its info
*********************************************************************/
Coffee Menu::search_coffee_by_name(string name) {
	Coffee found; 
	int count = 1; //this is used for numbered list formatting, nothing too important
	
	//Checks if there is coffee found by iterating through array of coffees
	for (int i = 0; i < num_coffee; i++){
		if (coffee_arr[i].get_name() == name){
			found = coffee_arr[i];
			cout << count << ". ";
			count++;
			break;
		}
	}
	return found;
}

/*********************************************************************
** Function: Menu::search_by_price()
** Description: Searches coffee by its price
** Parameters: float budget - the price of the coffee being searched
** Pre-Conditions: none
** Post-Conditions: If a coffee is found, it returns coffee items that fall within the price range
*********************************************************************/
Menu Menu::search_coffee_by_price(float budget){
	Menu temp;

	//Iterates through the number of coffees
	for (int i = 0; i < num_coffee; i++){
		//Checks if the budget is equal or less than the price that the user entered
		if (coffee_arr[i].get_small_cost() <= budget || coffee_arr[i].get_med_cost() <= budget || coffee_arr[i].get_large_cost() <= budget){
			temp.add_to_menu(coffee_arr[i]); //Stores the info in a temporarily menu 'temp'
		}
	}
	return temp;
}

/*********************************************************************
** Function: Menu::populate_menu()
** Description: Populates menu with coffee items from menu file
** Parameters: ifstream& file - Input file stream
** Pre-Conditions: File stream is opened and positioned correctly
** Post-Conditions: The menu is populated with data from menu file
*********************************************************************/
void Menu::populate_menu(ifstream& file){
	file >> this->num_coffee;

	this->coffee_arr = new Coffee [this->num_coffee];

	for (int i = 0; i < this->num_coffee; i++){
		//populate a single coffee
		coffee_arr[i].populate_coffee(file);
	}
}

/*********************************************************************
** Function: Menu::print_menu()
** Description: Prints out menu with a list of coffee items
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: Menu is printed in the console and displayed in a numbered list format
*********************************************************************/
void Menu::print_menu() {
	//prints populated coffee items
	for (int i = 0; i < num_coffee; i++){
		cout << endl << i + 1 << ". ";
		coffee_arr[i].print_coffee();
	}
}