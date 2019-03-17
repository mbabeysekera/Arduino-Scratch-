#ifndef find_str // This will check whether the file name "find_str" define or not
#define find_str // If not then define "find_str"

uint8_t W_GetMatch(char Word[]) { // Define a function name "W_GetMatch"
  while (Serial.available()) { // Wait until serial data is coming
    int Wlen = strlen(Word); // Find the length of the data (Word) to be checked
    int i = 0, tout = 0; // Set an itterative parametr and a timeout parameter as i and tout
    char str[20]; // Construct an empty arry to store temporary data
    while (i != Wlen) { // Check the terminator condition
      if (Serial.available()) { //check the serial data availability 
        str[i++] = Serial.read(); // Read the serial data coming from the databus and store in the temporary array
        str[i] = '\0'; // Add an null character to make a srting 
        tout = 0; // If the Process is completed successfully then reset the timeout
      }
      if (tout == 100) return 0; // If the process is not completed correctly within the timeout then return 0.
      tout++; // Increment timeout while the serial data is not coming
    }
    if (strcmp(Word, str) == 0) return 1; // Check the given and serially taken data to find the match. If matched, return 1.
    else {
      int timeout = 0; // Define an another timeout 
      while (1) { // Forever loop
        if (Serial.available()) { // Check serial data availability
          char  temp = Serial.read(); // Read serial data (one character at a time)
          for (int s = 0; s < Wlen; s++) { // Shift each character forward in the str array to add the next incoming data from serial bus
				if (s == (Wlen - 1)) { // At the end of the array put a null character to make it a string
				  str[s++] = temp; // Last character taken from serial
				  str[s] = '\0'; // Add the null at the end
				}
				else { 
				  str[s] = str[s + 1]; // Shift data in the array one by one
				}
          }
          if (strcmp(Word, str) == 0) { // Lastly, Check the given and serially taken data to find the match. If matched, return 1.
            return 1; // This will terminate the forever while loop
          }
          timeout = 0; // Reset timeout variable to 0.
        }
        if (timeout == 100)return 0; // If the process is not completed correctly within the timeout then return 0.
        timeout++; // Increment timeout while the serial data is not coming
      }
    }
  }
  return 0; // End the return type function correctly.
}

#endif //  End the newly defined file