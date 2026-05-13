#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <random>
using namespace std;

struct coffee {
    int id;
    string name;
    double price;
    int quantity;
};

const int MAX_COFFEES = 100; 
coffee coffees[MAX_COFFEES];
int coffeeCount = 0;

ofstream file("coffees.txt");

void loadFromFile() { // Load coffees from file
    ifstream file("coffees.txt");
    if (file.is_open()) { // Check if file opened successfully
        coffee c;
        coffeeCount = 0;
        while (file >> c.id >> c.name >> c.price >> c.quantity && coffeeCount < MAX_COFFEES) {
            coffees[coffeeCount++] = c;
        }
        file.close(); // Close the file after reading
    }
}

void saveToFile() { // Save coffees to file
    ofstream file("coffees.txt");
    for (int i = 0; i < coffeeCount; i++) { // Write each coffee to file
        file << coffees[i].id << " " << coffees[i].name << " " << coffees[i].price << " " << coffees[i].quantity << "\n";
    }
    file.close();
}

int generateRandomID() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<int> dist(1000, 9999);
    return dist(gen);
}

void displayCoffees() { // Display all coffees
     if (coffeeCount == 0) {
        cout << "No coffees available.\n";
        return;
    }
    cout << "\n============ COFFEE LIST =============\n";
    cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(10) << "Price" << setw(10) << "Quantity\n"; // Header for coffee list
    cout << string(40, '-') << "\n";
    for (int i = 0; i < coffeeCount; i++) {
        stringstream priceStr;
        priceStr << "$" << fixed << setprecision(2) << coffees[i].price;
        cout << left << setw(5) << coffees[i].id << setw(15) << coffees[i].name << setw(10) << priceStr.str() << setw(10) << coffees[i].quantity << "\n";
    }
}

void addCoffee() {
    if (coffeeCount >= MAX_COFFEES) { // Check if we can add more coffees
        cout << "Maximum coffees reached!\n";
        return;
    }
    coffee c; // Create a new coffee object
    bool validInput = false;
    
    // Get ID with validation
    do {
        c.id = generateRandomID();
        bool idExists = false;
        for (int i = 0; i < coffeeCount; i++) {
            if (coffees[i].id == c.id) {
                idExists = true;
                break;
            }
        }
        if (!idExists) {
            validInput = true;
        }
    } while (!validInput);
    
    cout << "Enter Name: "; cin.ignore(); getline(cin, c.name);
    
    // Get Price with validation
    validInput = false;
    do {
        cout << "Enter Price: $";
        if (cin >> c.price) {
            validInput = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
    } while (!validInput);
    
    // Get Quantity with validation
    validInput = false;
    do {
        cout << "Enter Quantity: ";
        if (cin >> c.quantity) {
            validInput = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
    } while (!validInput);
    
    coffees[coffeeCount++] = c;
    cout << "Coffee added successfully!\n";
    saveToFile();
}

void updateCoffee() { // Update existing coffee
    int id;
    bool validInput = false;
    
    // Get ID with validation
    do {
        cout << "Enter Coffee ID to update: ";
        if (cin >> id) {
            validInput = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
    } while (!validInput);
    
    for (int i = 0; i < coffeeCount; i++) {
        if (coffees[i].id == id) {
            cout << "Enter new Name: "; cin.ignore(); getline(cin, coffees[i].name);
            
            // Get new Price with validation
            validInput = false;
            do {
                cout << "Enter new Price: $";
                if (cin >> coffees[i].price) {
                    validInput = true;
                } else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input! Please enter a number.\n";
                }
            } while (!validInput);
            
            // Get new Quantity with validation
            validInput = false;
            do {
                cout << "Enter new Quantity: ";
                if (cin >> coffees[i].quantity) {
                    validInput = true;
                } else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input! Please enter a number.\n";
                }
            } while (!validInput);
            
            cout << "Coffee updated successfully!\n";
            saveToFile();
            return;
        }
    }
    cout << "Coffee with ID " << id << " not found!\n"; // Coffee not found message
}


void deleteCoffee() { // Delete a coffee by ID
    int id;
    bool validInput = false;
    
    // Get ID with validation
    do {
        cout << "Enter Coffee ID to delete: ";
        if (cin >> id) {
            validInput = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
    } while (!validInput);
    
    for (int i = 0; i < coffeeCount; i++) {
        if (coffees[i].id == id) {
            for (int j = i; j < coffeeCount - 1; j++) {
                coffees[j] = coffees[j + 1];
            }
            coffeeCount--;
            cout << "Coffee deleted successfully!\n";
            saveToFile();
            return;
        }
    }
    cout << "Coffee with ID " << id << " not found!\n";
}

string toLower(string str) { // Convert string to lowercase
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void searchCoffee() { // Search for a coffee by ID or Name
    int choice;
    bool validInput = false;
    
    // Get search choice with validation
    do {
        cout << "\nSearch by:\n1. ID\n2. Name\nEnter choice: ";
        if (cin >> choice && (choice == 1 || choice == 2)) {
            validInput = true;
        } else {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter 1 or 2.\n";
        }
    } while (!validInput);
    
    cin.ignore(); // Clear buffer
    
    if (choice == 1) { // Search by ID
        int id;
        validInput = false;
        
        // Get ID with validation
        do {
            cout << "Enter Coffee ID to search: ";
            if (cin >> id) {
                validInput = true;
            } else {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input! Please enter a number.\n";
            }
        } while (!validInput);
        
        for (int i = 0; i < coffeeCount; i++) {
            if (coffees[i].id == id) {
                cout << "\nFound: ID=" << coffees[i].id << ", Name=" << coffees[i].name << ", Price=$" << fixed << setprecision(2) << coffees[i].price << ", Qty=" << coffees[i].quantity << "\n";
                return;
            }
        }
        cout << "Coffee with ID " << id << " not found!\n";
    } else if (choice == 2) { // Search by Name
        string searchName;
        cout << "Enter Coffee Name to search: ";
        getline(cin, searchName);
        string searchNameLower = toLower(searchName);
        
        for (int i = 0; i < coffeeCount; i++) {
            if (toLower(coffees[i].name) == searchNameLower) {
                cout << "\nFound: ID=" << coffees[i].id << ", Name=" << coffees[i].name << ", Price=$" << fixed << setprecision(2) << coffees[i].price << ", Qty=" << coffees[i].quantity << "\n";
                return;
            }
        }
        cout << "Coffee with name \"" << searchName << "\" not found!\n";
    }
}

int main() { // Main function to run the coffee management system
    loadFromFile();
    int choice = -1; // Initialize choice to -1
    do {
        cout << "\n===== COFFEE MANAGEMENT SYSTEM =====\n";
        cout << "1. Display Coffees\n";
        cout << "2. Add Coffee\n";
        cout << "3. Update Coffee\n";
        cout << "4. Delete Coffee\n";
        cout << "5. Search Coffee\n";
        cout << "0. Exit\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";
        if (!(cin >> choice)) { // Check if input is valid
            cin.clear(); // Clear error flag
            cin.ignore(10000, '\n'); // Clear buffer
            cout << "Invalid input! Please enter a number.\n";
            choice = -1; // Reset choice to keep loop running
            continue;
        }
        
        switch (choice) {
            case 1: displayCoffees(); break; // Display all coffees
            case 2: addCoffee(); break; // Add a new coffee
            case 3: updateCoffee(); break; // Update an existing coffee
            case 4: deleteCoffee(); break; // Delete a coffee
            case 5: searchCoffee(); break; // Search for a coffee
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n"; break; // Handle invalid menu choices 
        }
    } while (choice != 0);
    return 0;
}