// Grade counter:-

#include <iostream>

using namespace std;

int main() {
    int aa,a,b,c,d;
    cout << "Enter marks out of hundred" << endl;
    cout << "Enter the marks needed for A+ :";
    cin >> aa;
    cout << "\nEnter the marks needed for A :";
    cin >> a;
    cout << "\nEnter the marks needed for B :";
    cin >> b;
    cout << "\nEnter the marks needed for C :";
    cin >> c;
    cout << "\nEnter the marks needed for D :";
    cin >> d;
    cout << "How many students do you need to grade? :";
    int students;
    cin >> students;
    int i = 0;
    while(i<students) {
        i++;
        cout << "Enter student number " << i << "s Marks :";
        int marks;
        cin >> marks;
        if (marks>=aa) {
            cout << "The grade of this student is A+ " << endl;
        } else if (marks >= a and marks < aa) {
            cout << "The grade of this student is A" << endl;
        } else if (marks >= b and marks < a) {
            cout << "The grade of this student is B" << endl;
        } else if (marks >=c and marks < b) {
            cout << "The Grade of this student is C" << endl;
        } else if (marks >=d and marks < c) {
            cout << "the Grade of this student is D" << endl;
        } else if (marks < d) {
            cout << "This student Failed.";
        } else{
            cout << "Invalid input";
        }
    }
    int close;
    cout << "Press enter to exit this program"
    cin >> close;
    return 0;
}
