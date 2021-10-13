#include <iostream>
enum PaymentMethod  {Card, Swish, Cash};

int main(){
    PaymentMethod payMeth = PaymentMethod::Cash;

    std::cout << payMeth << std::endl;

    if(payMeth == PaymentMethod::Cash){
        std::cout << "Paymentmethod is cash" << std::endl;
    }
}