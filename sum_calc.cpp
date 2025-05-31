#include <iostream>

int main() {
    using namespace std;
    int number, originalNumber, digit, sum = 0;

    cout << "Enter a 4-digit number: ";
    cin >> number;

    originalNumber = number;

    if (number < 1000 || number > 9999) {
        cout << "Invalid input. Please enter a 4-digit number." << endl;
        return 1;
    }

    while (number > 0) {
        digit = number % 10;
        sum += digit;
        number /= 10;
    }

    cout << "The sum of the digits of " << originalNumber << " is: " << sum << endl;

    return 0;
}
