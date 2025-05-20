// Prime number checking
#include <iostream>
#include <cmath>

using namespace std;

int main() {
    long long int n;
    cout << "Enter a number to be checked:";
    cin >> n;
    bool bIsPrime = true;
    if (n < 2) {
        bIsPrime = false;

    } else {
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                bIsPrime = false;
                break;
            }
        }
    }
    if (bIsPrime) {
        cout << n << " is a prime number." << endl;
    } else {
        cout << n << " is a composite number." << endl;
    }
    cout << "Press any key to exit...";
    cin.ignore();
    cin.get();
    return 0;
}
