#include <fstream>
#include <iostream>
#include <vector>


int main(){
    std::ifstream inFile("Input.txt");
    std::string word1;
    std::string word2;
    std::vector<std::pair<std::string, int>> wordQuantities;
    int quantity;

    while(inFile >> word1){
        std::ifstream lookUpFile("LookUp.txt");
        quantity = 0;
        while(lookUpFile >> word2 ){
            if(word1==word2){
                quantity++;
            }
        }
        wordQuantities.push_back(std::make_pair(word1, quantity));
    }

    for(int i = 0; i < wordQuantities.size(); i++){
        std::cout << wordQuantities[i].first << " occurs " << wordQuantities[i].second << " in textfile Lookup.txt"  << std::endl;
    }

}