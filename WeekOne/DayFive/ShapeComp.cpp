#include <iostream>

class Shape{
    public:
        int perimiter = 0;
        int area = 0;
        Shape()=default;
};

class Circle: public Shape{
    private:
        int pi = 3;
    
    public:
        Circle(int radius){
            this->perimiter = 2*radius*pi;
            this->area = radius*radius*pi; 
        }
};

class Rectangle: public Shape{
    private:
        
    public:
        Rectangle(int width, int height){
            this->perimiter = 2*width+2*height;
            this->area = width*height;
        }
};

class Square: public Shape{
    public:
        Square(int side){
            this->perimiter = 4* side;
            this->area = side*side;
        }
};

class Triangle: public Shape{
    public:
        Triangle(int side) {
            this->perimiter = 3* side;
            this->area = side*side/2;
        }
};


int main(){
    Circle c(2);
    std::cout << c.area << std::endl;


}

