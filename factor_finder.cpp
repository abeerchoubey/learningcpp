#include <iostream>

int main() {
    //factors calculator
    int num;
    std::cout << "Enter the number of which you want the factors of. >>>";
    std::cin >> num;
    for(int x=1;x<=num;x++) {
        if(num % x == 0) {
            std::cout << x << " is a factor of " << num << std::endl;
            continue;
        }
    }
    return 0;
}
