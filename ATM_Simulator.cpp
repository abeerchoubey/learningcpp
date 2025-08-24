#include <iostream>

using namespace std;

int main() {
    //ATM SIMULATOR BY ABEER
    int bal=0;
    cout << "░▄▄▄▄░" << endl;
    cout << "▀▀▄██►" << endl;
    cout << "▀▀███►" << endl;
    cout << "░▀███►░█►" << endl;
    cout << "▒▄████▀▀" << endl;
    while (true) {
        cout << "\n\nWhat would you like to do? enter ONLY NUMBER corresponding to the action!!\n 1 --> Withdraw \n 2 --> Deposit\n\n >>>";
        int action;
        cin >> action;
        switch (action) {
            case 1:
                if (bal==0) {
                    cout << "You have no money, please deposit before withdrawing";
                    continue;
                }
                else {
                    cout << "You have " << bal << "money" << endl;
                    cout << "How much money would you like to withdraw?\n>>>";
                    int amount;
                    cin >> amount;
                    bal -= amount;
                    cout << "You have " << bal << " money left" << endl;
                }
            case 2:
                if (bal==0) {
                    cout << "You have" << bal << " money" << endl;
                    cout << "How much money would you like to deposit?\n>>>";
                    int amount;
                    cin >> amount;
                    bal += amount;
                    cout << "You have " << bal << " money left" << endl;
                }
        }
        cout << "If you want to continue, input 1, if you want to terminate this simulator, input 2.\n>>>";
        int terminator;
        cin >> terminator;
        if (terminator==1) {
            continue;
        }
        else if (terminator==2) {
            break;
        }
        else {
            cout<<"Invalid Input" << endl;
            continue;
        }
    }
    return 0;
}
