// check the greatest among three numbers

#include <iostream>

using namespace std;

int main() {
    double e,n,s;
    cout << "Enter three numbers:-->\n\n\nFirst Number:";
    cin >> e;
    cout << "\n\nSecond Number:";
    cin >> n;
    cout << "\n\nThird Number:";
    cin >> s;
    if (e>n and e>s) {
        cout << "\n" << e << " is the greatest among the numbers.";

    } else if (n>e and n>s) {
        cout << "\n" << n << " is the greatest among the numbers.";
    } else if (s>n and s>e) {
        cout << "\n" << s << " is the greatest among the numbers.";
    } else if (s==n and e==n) {
        cout << "\nAll are the same";
    }
    return 0;
}
