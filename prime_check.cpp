#include <iostream>
using namespace std;
int main() {
    int x;
    cout << "Enter a number under 2.7m which should be a positive integer which is not 0 or 1 :";
    cin >> x;
    int y=0, z=0;
    if (x<=1){
        cout<<"number not valid";
    }
    while(y<=x){
        y+=1;
        if(y%x==0){
            z+=1;
        }
        else {
            
        }
    }
    if (z==2){
        cout<<"This number is a prime";
    }
    else {
        cout<<"This number is a composite / not prime ";
    }
    return 0;
}
