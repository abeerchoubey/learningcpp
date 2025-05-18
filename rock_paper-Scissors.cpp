#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    int x;
    srand(time(0));
    int y=std::rand() % 3+1;
    cout << "Rock Paper Scissors game by Abeer" << endl;
    cout << "Enter 1 if you choose rock" << endl;
    cout << "Enter 2 if you choose paper" << endl;
    cout << "Enter 3 if you choose scissors" << endl;
    cout << "--->>";
    cin >> x;
    cout << endl;
    switch(x) {
        case 1:
            cout << "You have chosen Rock" << endl;
            switch(y) {
                case 1:
                    cout << "It is a tie" << endl;
                    break;
                case 2:
                    cout << "The Computer Wins" << endl;
                    break;
                case 3:
                    cout << "You win" << endl;
                    break;
            }
            break;
        case 2:
            cout << "You have chosen paper" << endl;
            switch(y) {
                case 1:
                    cout << "You win" << endl;
                    break;
                case 2:
                    cout << "It is a tie" << endl;
                    break;
                case 3:
                    cout << "The computer wins" << endl;
                    break;
            }
            break;
        case 3:
            cout << "You have chosen scissors" << endl;
            switch(y) {
                case 1:
                    cout << "The computer wins" << endl;
                    break;
                case 2:
                    cout << "You win" << endl;
                    break;
                case 3:
                    cout << " It is a tie" << endl;
                    break;
                
            }
            break;
            
    }
    return 0;
}