#include <iostream>

using namespace std;

int main() {
    long long int n;
    cout << "Enter the number of fibonacci numbers to generate: ";
    cin >> n;
    long long int a = 0, b = 1;
    cout << a << " " << b << " ";

    for (long long int i = 2; i < n; i++) {
        long long int next = a + b;
        cout << next << " ";
        a = b;
        b = next;
    }
    return 0;
}
