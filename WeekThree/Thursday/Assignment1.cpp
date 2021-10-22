#include <iostream>
#include <bitset>


int main(){
    std::string bits = "1011101001011011";
    std::bitset<16> set1(bits); 
    std::bitset<16> seatBeltsMask("1111100000000000");
    std::bitset<16> windowsMask("0000011110000000");
    std::bitset<16> doorsMask("0000000001111000");
    std::bitset<16> lightsMask("0000000000000111");

    std::cout << (set1 & seatBeltsMask).count() << " seatbelts are used"  << std::endl;
    std::cout << (set1 & windowsMask).count() << " windows are open"  << std::endl;
    std::cout << (set1 & doorsMask).count() << " doors  are open"  << std::endl;
    std::cout << (set1 & lightsMask).count() << " lights are on"  << std::endl;

    return 0;
}