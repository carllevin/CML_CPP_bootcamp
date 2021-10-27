#include "Shape.hpp"



int main(){
    Circle c(2);
    Rectangle r(3,4);
    std::cout << "Area of circle: " << c.area << std::endl;
    std::cout << "Area of Rectangle: " << r.area << std::endl;
    std::cout << "Perimiter of circle: " << c.perimiter << std::endl;
    std::cout << "Perimiter of Rectangle: " << r.perimiter << std::endl;

    if(r>c){
        std::cout << "Rectangle is bigger"<< std::endl;
    }
}

