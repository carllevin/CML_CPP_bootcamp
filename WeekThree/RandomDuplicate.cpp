#include <iostream> 
#include <vector> 
#include <map>
#include<time.h>
#include <iterator>

/* Generate randomnumbers between 0-33,tenthousand times,then print how many duplicates of each number
you have generated--print in ascending order. */


int main() {
    srand(time(0));
    std::vector<int> duplicatesVector(34);
    std::vector<int> numbers;
    int randNumber;

    for(int i=0; i < 10000; i++) {
        randNumber = rand() % 34;
        numbers.push_back(randNumber);
        duplicatesVector[randNumber] = duplicatesVector[randNumber] + 1;
    }

    std::multimap<int, int> duplicatesMap;

    for(int i = 0; i < 34; i++){
        duplicatesMap.insert(std::pair <int, int> (duplicatesVector[i], i));

    }

    for (auto itr = duplicatesMap.begin(); itr != duplicatesMap.end(); ++itr) {
        std::cout << itr->first << '\t' << itr->second << '\n';
    }
}