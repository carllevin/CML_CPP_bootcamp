#include <iostream>
#include <iterator>
#include <set>

int main(){
    std::multiset<int> s1;
    std::srand(time(nullptr));

    for(int i = 0; i < 1024; i++){
        int randNumber = rand();
        s1.insert(randNumber);
    }

    int compareNumber = rand();
    auto itr = s1.upper_bound(compareNumber);
    int higherbound = *itr;
    itr--;
    int lowerbound = *(itr);


    std::cout << "Compare value: " << compareNumber << std::endl;
    std::cout << "The number before the compare value: " << lowerbound << std::endl;
    std::cout << "The number after the compare value: " << higherbound << std::endl;
}