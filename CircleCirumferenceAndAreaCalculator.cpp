#include <iostream>

using namespace std;

int main() {
    const float pi = 3.14;
    double rad;
    cout << "Enter the radius of the circle:>>";
    cin >> rad;
    double circ = 2*rad*pi, area = pi*(rad*rad);
    cout << "\nThe Area is : " << area << "\n And the Circumference is : " << circ << "\n\n\n\nAppoximated by taking pi as: " << pi << "\nAnd taking Radius as: " << rad << endl;
    return 0;
}
