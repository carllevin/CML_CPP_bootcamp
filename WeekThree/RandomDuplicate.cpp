#include <iostream> 
#include <vector> 

/* Generaterandomnumbersbetween0-33,tenthousandtimes,thenprinthowmanyduplicatesofeachnumber
youhavegenerated--printinascendingorder. */

//Fix it with a map. Or was it multimap?

int main() {
    std::vector<int> duplicates(34);
    std::vector<int> numbers;
    int randNumber;

    for(int i=0; i < 10000; i++) {
        randNumber = rand() % 34;
        numbers.push_back(randNumber);
        duplicates[randNumber] = duplicates[randNumber] + 1;
    }

    for(int i = 0; i<34; i++){
        std::cout << "Number of duplicates of " << i << " is " << duplicates[i] << std::endl;
    }
}