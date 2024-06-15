#include <iostream>
#include <fstream>
#include <cstdlib>  // for rand() and srand()
#include <ctime>    // for time()

using namespace std;

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    // Check if the input is valid
    if (cin.fail() || n <= 0) {
        cerr << "Invalid input. Please enter a positive integer." << endl;
        return 1;
    }

    // Creating the file name based on the input number
    string filename = to_string(n) + ".txt";

    // Opening the file to write the numbers
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error creating file " << filename << endl;
        return 1;
    }

    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    // Generating and writing random numbers to the file
    for (int i = 0; i < n; ++i) {
        int randomNumber = (rand() % 100000) + 1;
        outFile << randomNumber << endl;
    }

    cout << "Random numbers generated and stored in " << filename << endl;

    // Closing the file
    outFile.close();
    return 0;
}
