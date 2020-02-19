#include "Rectangle.h"
#include <cstdlib>

Rectangle::Rectangle(Point p1, Point p2){
    if(p1.x > p2.x && p1.y > p2.y){
        Point t = p1;
        p1 = p2;
        p2 = t;
    }else if(p1.x > p2.x && p1.y < p2.y){
        Point t1 = {.x = p2.x, .y = p1.y};
        Point t2 = {.x = p1.x, .y = p2.y};
        p1 = t1;
        p2 = t2;
    }
    p1_ = p1;
    p2_ = p2;
}

// get the width of the rectangle  
// between p1.x and p2.x
int Rectangle::GetWidth(){
    return p2_.x - p1_.x;
}
// get the height of the rectangle
// between p1.y and p2.y
int Rectangle::GetHeight(){
    return p2_.y - p1_.y;
}

// returns true if this rectangle shares any points with the other one
bool Rectangle::Overlaps(Rectangle& other){
    Point P1 = this->p1_;
    Point P2 = this->p2_;
    Point P3 = other.get_p1();
    Point P4 = other.get_p2();

}

// returns the area of this rectangle
int Rectangle::CalculateArea(){
    int dx = p2_.x - p1_.x;
    int dy = p2_.y - p1_.y;
    return abs(dx*dy);
}

// moves the bottom left coordinate down one and to the left one
// moves the upper right coordinate up one and to the right one
void Rectangle::Expand(){
    p1_.x--;
    p1_.y--;
    p2_.x++;
    p2_.y++;
}

// moves the bottom left coordinate up one and to the right one
// moves the upper right coordinate down one and to the left one
void Rectangle::Shrink(){
    if(this->CalculateArea() == 0){
        return;
    }
    p1_.x++;
    p1_.y++;
    if(this->CalculateArea() == 0){
        return;
    }
    p2_.x--;
    p2_.y--;
}