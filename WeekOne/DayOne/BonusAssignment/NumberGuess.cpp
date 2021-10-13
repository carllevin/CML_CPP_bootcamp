#include <iostream>
#include <math.h>

int main() {
    bool condition = true;
    char answer;
    int incVar, number = 64, NbrOfQuestion = 1;
    std::cout << "Think of a number 1-128"<< std::endl;
    
    while(condition){
        std::cout << "True or False - Is your number greater than " << number << "?[y/n]" << std::endl;
        std::cin >> answer;
        std::cout << "Number of questions: " << NbrOfQuestion << std::endl;

        incVar = 64 /pow(2,NbrOfQuestion);
        NbrOfQuestion ++;
        if(NbrOfQuestion < 8){
            if(answer == 'y'){
                number = number + incVar;
            } else {
                number = number - incVar;
            }
        }
        
        if(NbrOfQuestion == 8){
            if(answer == 'y'){
                number++;
                std::cout << "The number you are thinking of is "<< number<< std::endl;
            } else {
                std::cout << "The number you are thinking of is "<< number << std::endl;
            }            
            condition = false;
        }
    }
    return 0;
}