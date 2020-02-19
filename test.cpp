#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "Rectangle.h"

TEST_CASE( "Point initializes", "[PtInit]" ) {

    Point p1;
    p1.x = 1;
    p1.y = 1;
    Point p2;
    p2.x = 1;
    p2.y = 1;

    REQUIRE( p1.x == p2.x );
    REQUIRE( p1.y == p2.y );

    SECTION( "Changing Point value" ) {
        p2.x = 2;
        p2.y = 2;

        REQUIRE( p1.x != p2.x );
        REQUIRE( p1.y != p2.y );
    }
    SECTION( "Rectangle initializes" ) {
        Rectangle R(p1,p2);
        Point p3 = R.get_p1();
        REQUIRE( p3.x == p1.x );
        REQUIRE( p3.y == p1.y );
        Point p4 = R.get_p2();
        REQUIRE( p4.x == p2.x );
        REQUIRE( p4.y == p2.y );
    }
}

TEST_CASE( "Rectangle Testing", "[Rec]" ) {

    Point p1;
    p1.x = -1;
    p1.y = -1;
    Point p2;
    p2.x = 1;
    p2.y = 1;

    SECTION( "Input negetive values" ) {
        Rectangle R1(p1,p2);
        
        Point p3 = R1.get_p1();
        REQUIRE( p3.x == p1.x );
        REQUIRE( p3.y == p1.y );
        Point p4 = R1.get_p2();
        REQUIRE( p4.x == p2.x );
        REQUIRE( p4.y == p2.y );
    }
    SECTION( "Have a lower value as the second coordinates" ) {
        p1.x = 2;
        p1.y = 2;
        p2.x = 1;
        p2.y = 1;
        
        Rectangle R2(p1,p2);
        
        Point p3 = R2.get_p1();
        REQUIRE( p3.x == p2.x );
        REQUIRE( p3.y == p2.y );
        Point p4 = R2.get_p2();
        REQUIRE( p4.x == p1.x );
        REQUIRE( p4.y == p1.y );
    }
}

TEST_CASE( "Rectangle Width", "[Width]" ) {

    Point p1;
    p1.x = 1;
    p1.y = 1;
    Point p2;
    p2.x = 2;
    p2.y = 2;

    SECTION( "Correct width function" ) {
        Rectangle R1(p1,p2);
        REQUIRE( R1.GetWidth() == 1 );
        
        Rectangle R2(p1,p1);
        REQUIRE( R2.GetWidth() == 0 );
        
        p1.x = -1;
        p1.y = -1;
        Rectangle R3(p1,p2);
        REQUIRE( R3.GetWidth() == 3 );
    }
    SECTION( "Width with neg" ) {
        p1.x = -2;
        p1.y = -2;
        p2.x = -1;
        p2.y = -1;
        Rectangle R1(p1,p2);
        REQUIRE( R1.GetWidth() == 1 );
    }
    SECTION( "Correct Hight function" ) {
        Rectangle R1(p1,p2);
        REQUIRE( R1.GetHeight() == 1 );
        
        Rectangle R2(p1,p1);
        REQUIRE( R2.GetHeight() == 0 );
        
        p1.x = -1;
        p1.y = -1;
        Rectangle R3(p1,p2);
        REQUIRE( R3.GetHeight() == 3 ); //height with neg values
    }
    SECTION( "Height with neg" ) {
        p1.x = -2;
        p1.y = -2;
        p2.x = -1;
        p2.y = -1;
        Rectangle R1(p1,p2);
        REQUIRE( R1.GetHeight() == 1 );
    }
}

TEST_CASE( "Rectangle Overlaps", "[Overlap]" ) {

    Point p1;
    p1.x = 1;
    p1.y = 1;
    Point p2;
    p2.x = 2;
    p2.y = 2;
    Point p3;
    p3.x = 3;
    p3.y = 3;
    Point p4;
    p4.x = 2;
    p4.y = 3;

    SECTION( "Overlap works" ) {
        Rectangle R1(p1,p1); //point at 1,1
        Rectangle R2(p1,p2); //from 1,1 to 2,2
        Rectangle R3(p2,p3); //from 2,2 to 3,3
        Rectangle R4(p1,p4); //from 1,1 to 2,3
        
        REQUIRE( R1.Overlaps(R2) == true );
        REQUIRE( R1.Overlaps(R3) == false );
        REQUIRE( R2.Overlaps(R4) == true );
        REQUIRE( R4.Overlaps(R3) == true ); //check between points
        
    }
}

TEST_CASE( "Rectangle Area", "[Area]" ) {

    Point p1;
    p1.x = 1;
    p1.y = 1;
    Point p2;
    p2.x = 2;
    p2.y = 2;
    Point p3;
    p3.x = 1;
    p3.y = 2;
    Point p4;
    p4.x = -1;
    p4.y = -1;
    
    SECTION( "Area works generally" ) {
        Rectangle R2(p1,p2); //from 1,1 to 2,2
        Rectangle R3(p4,p2); //from -1,-1 to 2,2
        
        REQUIRE( R2.CalculateArea() == 1 );
        REQUIRE( R3.CalculateArea() == 9 );
        
    }
    
    SECTION( "Area works for a point rectangle" ) {
        Rectangle R1(p1,p1); //point at 1,1
        
        REQUIRE( R1.CalculateArea() == 0 );
    }

    SECTION( "Area works with flipped point insert" ) {
        Rectangle R2(p2,p1); //from 2,2 to 1,1
        Rectangle R3(p2,p4); //from 2,2 to -1,-1
        
        REQUIRE( R2.CalculateArea() == 1 );
        REQUIRE( R3.CalculateArea() == 9 );
        
    }
    SECTION( "Area Works with lines" ) {
        Rectangle R2(p1,p3); //from 1,1 to 1,2
        Rectangle R3(p2,p3); //from 2,2 to 1,2
        
        REQUIRE( R2.CalculateArea() == 0 );
        REQUIRE( R3.CalculateArea() == 0 );
        
    }
    SECTION( "Area Works with Neg and Pos" ) {
        p1.x = -1;
        p1.y = 1;
        p2.x = -3;
        p2.y = 3;
        Rectangle R(p1,p2); //from -1,1 to -2,2
        
        REQUIRE( R.CalculateArea() == 4 );
        
    }
}

TEST_CASE( "Rectangle Expands", "[Expand]" ) {

    Point p1;
    p1.x = 2;
    p1.y = 2;
    Point p2;
    p2.x = 3;
    p2.y = 3;

    SECTION( "Expand works generally" ) {
        Rectangle R(p1,p2);
        R.Expand();
        Point p3 = R.get_p1();
        REQUIRE( p3.x == 1 );
        REQUIRE( p3.y == 1 );
        Point p4 = R.get_p2();
        REQUIRE( p4.x == 4 );
        REQUIRE( p4.y == 4 );
    }
    SECTION( "Expand works on a point" ) {
        Rectangle R(p2,p2);
        R.Expand();
        Point p3 = R.get_p1();
        REQUIRE( p3.x == 2 );
        REQUIRE( p3.y == 2 );
        Point p4 = R.get_p2();
        REQUIRE( p4.x == 4 );
        REQUIRE( p4.y == 4 );
    }
    SECTION( "Expand works on a line" ) {
        p1.x = 3;
        Rectangle R(p1,p2);
        R.Expand();
        Point p3 = R.get_p1();
        REQUIRE( p3.x == 2 );
        REQUIRE( p3.y == 1 );
        Point p4 = R.get_p2();
        REQUIRE( p4.x == 4 );
        REQUIRE( p4.y == 4 );
    }
}
TEST_CASE( "Rectangle Shrinks", "[Shrink]" ) {

    Point p1;
    p1.x = 1;
    p1.y = 1;
    Point p2;
    p2.x = 4;
    p2.y = 4;

    SECTION( "Shrink works generally" ) {
        Rectangle R(p1,p2);
        R.Shrink();
        Point p3 = R.get_p1();
        REQUIRE( p3.x == 2 );
        REQUIRE( p3.y == 2 );
        Point p4 = R.get_p2();
        REQUIRE( p4.x == 3 );
        REQUIRE( p4.y == 3 );
    }
    SECTION( "Shrink works on a point" ) {
        Rectangle R(p2,p2);
        R.Shrink();
        REQUIRE( R.CalculateArea() == 0 );
    }
    SECTION( "Shrink works on a almost line" ) {
        p1.x = 2;
        p1.y = 2;
        Rectangle R(p1,p2);
        R.Shrink();
        REQUIRE( R.CalculateArea() == 0 );
    }
}