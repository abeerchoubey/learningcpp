// check for the least number

#include <iostream>

using namespace std;

int main() {
    double a,b,c;
    cout << "Enter 3 numbers\nFirst number:";
    cin >> a;
    cout << "\nSecond number:";
    cin >> b;
    cout << "\nThird number:";
    cin >> c;
    if (a<b and a<c) {
        cout << "\n" << a << " is the smallest number";
    } else if (b<a and b<c) {
        cout << "\n" << b << " is the smallest number";
    } else if (c<a and c<b) {
        cout << "\n" << c << " is the smallest number";
    } else {
        cout << "\nall are the same" << endl;
    }

    return 0;
}
