/*
 * =====================================================================================
 *
 *       Filename:  lab6_3.cpp
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

int Grow() {

    double *nv = new double[2 * size]; // Allocate double the memory for new vector

    for (int i = 0; i < size; i++) { // Copy the values from v to nv

        nv[i] = v[i];

    }

    Finalize(); // Free memory consumed by vector v

    v = nv; // Set v to nv

    cout << endl << "Vector grown" << endl; // Print statements
    cout << "Previous capacity: " << size << " elements" << endl;

    size = 2 * size; // Double the size
    cout << "New capacity: " << size << " elements" << endl << endl;

    return 0; // Return success

}

int PrintVector() {

    cout << endl << "<"; // Print left bracket

    for (int i = 0; i < count - 1; i++) {// Iterate through elements, printing each

        cout << v[i] << ", ";

    }

    if (count > 0) cout << v[count - 1]; // Print last element without comma
    cout << ">" << endl << endl; // Print right bracket

    return 0; // Return success

}

int AddElement() {

    if (count == size) {

        Grow(); // If vector at capacity, increase size

    }

    cout << "Enter the new element: ";
    cin >> v[count]; // Set input value to empty vector slot
    count++; // Increase count value

    return 0; // Return success

}

int main() {

    Initialize(); // Initialize values

    string options[] = {"Print the array", "Append element at the end", "Remove last element", "Insert one element", "Exit"}; // Store options in array for ease of access

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

                PrintVector();
                break;
                
            case 2:

                AddElement();
                break;

            case 3:

                break;

            case 4:

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
