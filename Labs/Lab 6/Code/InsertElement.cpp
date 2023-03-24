int InsertElement() {

    int index;
    double value;

    cout << "Enter the index of new element: ";
    cin >> index;

    while (index > count - 1|| index < 0) {

        cout << endl << "Error: Invalid index" << endl;
        cout << "Enter the index of new element: ";
        cin >> index;

    }

    if (count == size) {

        Grow();

    }

    cout << "Enter the new element: ";
    cin >> value;
    cout << endl << endl;

    int swap = v[index];
    int swap2 = 0;
    v[index] = value;

    for (int i = index; i < size; i++) {

        swap2 = v[i + 1];
        v[i + 1] = swap;
        swap = swap2;

    }

    count++;

    return 0; // Return success

}
