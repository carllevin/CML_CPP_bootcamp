#include "Shape.hpp"

bool Shape::operator >(Shape s){
    return (this->area > s.area || (this->area == s.area && this->perimiter > s.perimiter));
}

bool Shape::operator <(Shape s){
    return (this->area < s.area || (this->area == s.area && this->perimiter < s.perimiter));
}

bool Shape::operator ==(Shape s){
    return (this->area == s.area && this->perimiter == s.perimiter);
}
