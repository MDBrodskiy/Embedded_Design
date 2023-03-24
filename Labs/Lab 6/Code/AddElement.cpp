int AddElement() {

    if (count == size) {

        Grow(); // If vector at capacity, increase size

    }

    cout << "Enter the new element: ";
    cin >> v[count]; // Set input value to empty vector slot
    count++; // Increase count value

    return 0; // Return success

}
