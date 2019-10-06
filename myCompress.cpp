#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int compress(int argc, char *argv[]) {
    int counter0 = 0; // counts the zeros
    int counter1 = 0; // counts the ones
    static fstream sourceFile;
    static fstream destFile;
    char currChar;
    string textString = "";

    // Open source and destination file
    sourceFile.open(argv[1], ios::in);
    destFile.open(argv[2], ios::out | ios::app);

    // Can't get the source or destination file, program exit
    if (sourceFile.fail() || destFile.fail()) {
        cout << "FIles not found. Program Exit\n";
        sourceFile.close();
        destFile.close();
        return 0;
    }

    // State Status and start compress
    cout << "File compress complete\n";

    // gets character
    while (sourceFile.good()) {
        sourceFile.get(currChar);

        // When character is a space or new line
        if (currChar == ' ' || currChar == '\n') {
            // if the 0 counter is greater than or equal to 16
            if (counter0 >= 16) {
                destFile << "-" + to_string(counter0) + "-";
                textString.clear();
                counter0 = 0;
                textString += currChar;
            }

            // if 1 counter is greater than or equal to 16
            else if (counter1 >= 16) {
                destFile << "+" + to_string(counter1) + "+";
                textString.clear();
                counter1 = 0;
                textString += currChar;
            }

            // No compressing needed
            else {
                counter0 = 0;
                counter1 = 0;
                destFile << textString;
                textString.clear();
                textString += currChar;
            }
        }

        // Executes if current character is 1
        else if (currChar == '1') {
            // adds character to string if 0's counter is zero
            if (counter0 == 0) {
                textString += currChar;
            }

            else if (counter0 >= 16) {
                destFile << "-" + to_string(counter0) + "-";
                textString.clear();
                counter0 = 0;
                textString += currChar;
            }

            // Nothing to compress and writes string into appended file
            else {
                destFile << textString;
                textString.clear();
                counter0 = 0;
                textString += currChar;
            }
            counter1++;
        }

        // Executes if current charater is 0
        else if (currChar == '0') {
            // adds 0 to string if 1's counter is zero
            if (counter1 == 0) {
                textString += currChar;
            }

            // If number of ones are greater than or equal to 16 and compress
            else if (counter1 >= 16) {
                destFile << "+" + to_string(counter1) + "+";
                textString.clear();
                counter1 = 0;
                textString += currChar;
            }

            // Nothing to compress, text String to destination file
            else {
                destFile << textString;
                textString.clear();
                counter1 = 0;
                textString += currChar;
            }
            counter0++;
        }
    }
    sourceFile.close();
    destFile.close();
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        // arguments not equal to 3
    } else {
    compress(argc, argv);
    }

    return 0;
}
