#include <iostream>

int main() {
    using namespace std;
    int number, originalNumber, reversedNumber = 0, remainder;

    cout << "Enter a 4-digit number: ";
    cin >> number;

    originalNumber = number;

    if (number < 1000 || number > 9999) {
        cout << "Invalid input. Please enter a 4-digit number." << endl;
        return 1; 
    }

    while (number != 0) {
        remainder = number % 10;
        reversedNumber = reversedNumber * 10 + remainder;
        number /= 10;
    }

    cout << "The reversed number of " << originalNumber << " is: " << reversedNumber << endl;

    return 0;
}
