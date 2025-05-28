// Hypotenuse calculator

#include <iostream>
#include <cmath>
int main() {
    using namespace std;
    double x,y;
    cout << "This is a hypotenuse Calculator \nPut in the base and height values of a triangle\n Base>>";
    cin >> x;
    cout << "\n Height";
    cin >> y;
    // (x*x+y*y) = z*z
    // x= base, y= Height, z = hypotenuse
    double temp, z;
    temp = (x*x + y*y);
    z = sqrt(temp);
    cout << "\n"<<  z << endl;
    return 0;
}

