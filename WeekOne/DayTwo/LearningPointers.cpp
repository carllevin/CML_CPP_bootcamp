#include <iostream>

int main(){
    int a = 14;
    int *b = new int;

    b = &a;

    std::cout << b << std::endl;



    return 0;
}