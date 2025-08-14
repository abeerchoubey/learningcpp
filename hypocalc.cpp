#include <iostream>
#include <cmath>

using namespace std;

int main () {
    double x,y;
    cout << "Enter base of the triangle: ";
    cin >> x;
    cout << "Enter height of the triangle: ";
    cin >> y;
    double z;
    z = sqrt(pow(x,2) + pow(y,2));
    cout << "The hypotenuse is: " << z << endl;
    return 0;
}
