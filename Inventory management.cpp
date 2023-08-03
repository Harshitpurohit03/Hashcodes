#include <iostream> 
 #include <string> 
 #include <vector> 
  
 using namespace std; 
  
 // Structure to represent an item in the inventory 
 struct InventoryItem { 
     string name; 
     int quantity; 
 }; 
  
 // Function to add an item to the inventory 
 void addItem(vector<InventoryItem>& inventory) { 
     InventoryItem item; 
     cout << "Enter item name: "; 
     cin >> item.name; 
     cout << "Enter item quantity: "; 
     cin >> item.quantity; 
     inventory.push_back(item); 
     cout << "Item added to inventory." << endl; 
 } 
  
 // Function to remove an item from the inventory 
 void removeItem(vector<InventoryItem>& inventory) { 
     if (inventory.empty()) { 
         cout << "Inventory is empty. Cannot remove any item." << endl; 
         return; 
     } 
  
     cout << "Enter the index of the item to remove: "; 
     int index; 
     cin >> index; 
  
     if (index < 0 || index >= inventory.size()) { 
         cout << "Invalid index. Please enter a valid index." << endl; 
         return; 
     } 
  
     inventory.erase(inventory.begin() + index); 
     cout << "Item removed from inventory." << endl; 
 } 
  
 // Function to display the current inventory 
 void displayInventory(const vector<InventoryItem>& inventory) { 
     if (inventory.empty()) { 
         cout << "Inventory is empty." << endl; 
         return; 
     } 
  
     cout << "Current Inventory:" << endl; 
     for (size_t i = 0; i < inventory.size(); ++i) { 
         cout << i << ". " << inventory[i].name << " - " << inventory[i].quantity << " units" << endl; 
     } 
 } 
  
 int main() { 
     vector<InventoryItem> inventory; 
     int choice; 
  
     cout << "Simple Inventory Management System" << endl; 
     cout << "---------------------------------" << endl; 
  
     while (true) { 
         cout << "Options:" << endl; 
         cout << "1. Add item" << endl; 
         cout << "2. Remove item" << endl; 
         cout << "3. Display inventory" << endl; 
         cout << "4. Exit" << endl; 
         cout << "Enter your choice: "; 
         cin >> choice; 
  
         switch (choice) { 
         case 1: 
             addItem(inventory); 
             break; 
         case 2: 
             removeItem(inventory); 
             break; 
         case 3: 
             displayInventory(inventory); 
             break; 
         case 4: 
             cout << "Exiting the program." << endl; 
             return 0; 
         default: 
             cout << "Invalid choice. Please enter a valid option." << endl; 
         } 
     } 
  
     return 0; 
 } 
 
