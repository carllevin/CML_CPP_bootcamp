#include <iostream>
#include <bitset>

uint16_t trunkFourBit(uint16_t a){
    return a > 15 ? 15 : a;
}

uint16_t trunkThreeBit(uint16_t a){
    return a > 7 ? 7 : a;
}

int main(){
    uint16_t speed = 60;
    uint16_t front = 1*150;
    uint16_t rear = 1*150;
    uint16_t right = 1*150;
    uint16_t left = 8*150;
    
   std::bitset<16> speedBin(trunkFourBit(speed/20));
   std::bitset<16> frontBin(trunkThreeBit(front/150));
   std::bitset<16> rearBin(trunkThreeBit(rear/150));
   std::bitset<16>  rightBin(trunkThreeBit(right/150));
   std::bitset<16>  leftBin(trunkThreeBit(left/150));

   std::bitset<16> output = (speedBin << 12) | (frontBin << 9) | (rearBin << 6) | (rightBin << 3) | (leftBin);
   std::cout << output << std::endl;
}