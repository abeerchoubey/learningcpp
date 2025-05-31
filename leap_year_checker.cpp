// Leap year checker
#include <iostream>

int main() {
    using namespace std;
    cout << "Enter the year: ";
    int year;
    cin >> year;
    if (year%4==0) {
        cout <<  "\n" << year << " is a leap year"; 
    } else {
        cout << "\n" << year << " is not a leap year";
    }
    return 0;
}
