#include <iostream>

class Shape{
    public:
        int perimiter = 0;
        int area = 0;
        Shape()=default;

        bool operator >(Shape s){
            return (this->area > s.area || (this->area == s.area && this->perimiter > s.perimiter));
        }

        bool operator <(Shape s){
            return (this->area < s.area || (this->area == s.area && this->perimiter < s.perimiter));
        }

        bool operator ==(Shape s){
            return (this->area == s.area && this->perimiter == s.perimiter);
        }
};

class Circle: public Shape{
    private:
        const int pi = 3;
    
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

template <typename T1, typename T2>
void compareShapes(T1 &_a, T2 &_b){
    if(_a > _b){
        std::cout << "First input is bigger than the second input" << std::endl;
    } else if(_a == _b){
        std::cout << "First input is equal the size of the second input " << std::endl;
    } else {
        std::cout << "First input is smaller than the second input" << std::endl;
    }

}

int main() {
    Circle c(2);
    Rectangle r1(3,4);
    Rectangle r2(3,4);
    int a = 3;
    int b = 2;
    
    compareShapes(c, r1);
    compareShapes(r1, c);
    compareShapes(r1,r2);
    
    compareShapes(a,b); //Why does this work and not compareShapes(3,2)? Because we have &-reference in input to function

}