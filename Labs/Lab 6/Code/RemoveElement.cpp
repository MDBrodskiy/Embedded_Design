int RemoveElement() {

    if (count == 0) { // If no elements, print error message

        cout << endl << "Error: No elements in vector" << endl << endl;
        return 1; // Return error code

    }

    else {

        v[count - 1] = 0; // Free last element
        count = count - 1; // Subtract one from count
        cout << endl << "Successfully removed value" << endl << endl;

    }

    return 0; // Return Success

}
