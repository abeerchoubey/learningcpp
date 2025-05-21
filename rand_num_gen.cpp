// This random number generator does NOT use any libraries like cstdlib
#include <iostream>

using namespace std;

unsigned long long int seed = 1;

unsigned long long int random_num() {
    seed = (seed * 9124 + 1) % 32768;
    return seed;
}

int main() {
    int n;
    cout << "Enter the number of random values you want: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Random number " << i + 1 << ": " << random_num() << endl;
    }

    return 0;
}
