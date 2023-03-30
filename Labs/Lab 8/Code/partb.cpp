/**Reads the value of a switch
 * -Uses base address of I/O
 * @param pBaseBase address returned by'mmap'
 * @param switchNumSwitch number (0 to 9)
 * @returnSwitch value read
 */
int Read1Switch(char * pBase, int switchNum) {

    // Read the switch register
    int switchRegisterValue = RegisterRead(pBase, SW_BASE);
    
    // Mask the value to extract the specified switch bit
    int switchBitMask = 1 << switchNum;

    // if the result is non-zero, then the switch is on, off otherwise
    int switchValue;
    //use the bitwise AND operator and compare result against the bit mask
    if (switchRegisterValue & switchBitMask == switchBitMask) {
        switchValue = 1;
    } else {
        switchValue = 0;
    }

    return switchValue;

}
