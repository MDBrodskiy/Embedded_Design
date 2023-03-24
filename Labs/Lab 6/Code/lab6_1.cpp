/*
 * =====================================================================================
 *
 *       Filename:  lab6_1.cpp
 *
 *    Description:  Introduces many functions to work with vectors
 *
 *        Version:  1.0
 *        Created:  03/16/2023
 *       Revision:  none
 *       Compiler:  GCC
 *
 *         Author:  Michael Brodskiy, Dylan Powers
 *
 * =====================================================================================
 */

#include <iostream>
#include <string> // Include string and iostream

using namespace std; // Use std as default namespace

double *v; // Declare global variables
int count, size;

int Initialize() {

    size = 2;
    count = 0;
    v = new double[size]; // Initialize the global variables to default values

    return 0; // Return success

}

int Finalize() {

    free(v); // Free memory consumed by vector v

    return 0; // Return success

}

int main() {

    string options[] = {"Print the array", "Append the element at the end", "Remove last element", "Insert one element", "Exit"}; // Store options in array for ease of access

    int input = 0; // Set input to 0 by default

    while (input != 5) { // Repeat main menu until exit key (5) is entered

        cout << "Main menu:" << endl << endl; // Print main menu header

        for (int i = 1; i <= 5; i++) { // Loop through array, printing it

            cout << i << ". " << options[i - 1] << endl;

        }
        
        cout << endl << "Select an option: "; // Allow user to select option
        cin >> input; // Set input to option selected by user
    
        switch (input) { // If cases 1-4, drop down to print statement; If exit case, return success; If invalid value, print and choose again

            case 1:
                
            case 2:

            case 3:

            case 4:

                cout << "You selected: \"" << options[input - 1] << "\"" << endl << endl;
                break;

            case 5:

                cout << "Exiting..." << endl;
                return 0;
                break;

            default:

                cout << "Invalid Option. Choose Again." << endl << endl;

        }
    
    }

}
