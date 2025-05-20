#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    // Number guessing game
    cout << "This is a number guessing game \n This was made by Abeer Choubey" << endl;
    int n = 0;
    srand(time(0));
    n = rand() % 20 + 1; // Random number between 1 and 20
    cout << "Guess a number between 1 and 20" << endl;
    int guess = 0;
    cin >> guess;
    int count = 1;
    while (guess != n) {
        if (guess < n) {
            cout << "Your guess is too low" << endl;
        } else {
            cout << "Your guess is too high" << endl;
        }
        cout << "Guess again" << endl;
        cin >> guess;
        count++;
    }
    cout << "Congratulations! You guessed the number in " << count << " tries." << endl;
    cout << "The number was " << n << endl;
    return 0;
}
