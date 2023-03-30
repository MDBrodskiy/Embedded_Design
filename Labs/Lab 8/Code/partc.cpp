/** Changes the state of an LED (ON or OFF)
 *  @param pBase Base address returned by 'mmap'
 *  @param ledNum LED number (0 to 9)
 *  @param state State to change to (ON or OFF)
 */
void Write1Led(char *pBase,int ledNum, int state) {

    if (ledNum < 0 || ledNum > 9) {
        cout << "ERROR: Invalid LED number. Only LED numbers 0 to 9 are valid." << endl;
        return;

    }
    
    // Read the LED redister
    int ledRegisterValue = RegisterRead(pBase, LEDR_BASE);

    // Set the state of the specified LED based on the state parameter
    if (state == 1) {
        ledRegisterValue = (1 << ledNum);
    } else {
        ledRegisterValue &= ~(1 << ledNum);
    }

    // Write the new LED register value
    RegisterWrite(pBase, LEDR_BASE, ledRegisterValue);

    // Read the LED register again and print out the value to double check (this can be commented out)
    int UpdatedRegisterValue = RegisterRead(pBase, LEDR_BASE);
    cout << "LED Register Updated Value: " << UpdatedRegisterValue << endl << endl;

}
