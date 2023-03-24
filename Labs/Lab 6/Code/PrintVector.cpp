int PrintVector() {

    cout << endl << "<"; // Print left bracket

    for (int i = 0; i < count - 1; i++) {// Iterate through elements, printing each

        cout << v[i] << ", ";

    }

    if (count > 0) cout << v[count - 1]; // Print last element without comma
    cout << ">" << endl << endl; // Print right bracket

    return 0; // Return success

}
