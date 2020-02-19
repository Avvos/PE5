#include "Rectangle.h"
#include <cstdlib>

// Bug Fix: Prevent points to be inserted other than point one bottom left and point 2 top right
Rectangle::Rectangle(Point p1, Point p2){
    if(p1.x > p2.x && p1.y > p2.y){ // checks if the first point is to the top right of the second and flips them
        Point t = p1;
        p1 = p2;
        p2 = t;
    }else if(p1.x > p2.x && p1.y < p2.y){ // checks if the second point is to the left and above the first and flips their x's 
        Point t1 = {.x = p2.x, .y = p1.y};
        Point t2 = {.x = p1.x, .y = p2.y};
        p1 = t1;
        p2 = t2;
    }else if(p1.x < p2.x && p1.y > p2.y){ // checks if the first point is above and to the right of the second and flips their y's
        Point t1 = {.x = p1.x, .y = p2.y};
        Point t2 = {.x = p2.x, .y = p1.y};
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
// Bug Fix: Added a check if the points don't intersect one onther but the edges still cross each other
bool Rectangle::Overlaps(Rectangle& other){
    Point p1 = this->p1_;
    Point p2 = this->p2_;
    Point p3 = other.get_p1();
    Point p4 = other.get_p2();
    
    if(p1.x > p4.x || p3.x > p2.x){ // checks if the rectangles are to the left or right of one another
        return false;
    }else if(p1.y > p4.y || p3.y > p2.y){ // checks if the rectangles are above or below one another
        return false;
    }else{
        return true;
    }
}

// returns the area of this rectangle
// Bug Fix: Added an absolute value
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
// Bug Fix: Added a check for the area before continuing the shrink
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