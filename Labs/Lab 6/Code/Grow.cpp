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
