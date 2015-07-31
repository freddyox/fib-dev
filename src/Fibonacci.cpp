#include "../include/Fibonacci.hh"
#include <iostream>
#include <cmath>

Fibonacci::Fibonacci(float width, float height, float maximum) {
  displayx = width;
  displayy = height;
  max = maximum;
  conv = 3.141592 / 180.0;

  radius = 1.0;
  circle.setRadius( radius );
  sf::FloatRect originRect = circle.getLocalBounds();
  circle.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  circle.setFillColor( sf::Color::Red );

  // Fibonacci Initial Conditions
  plusorminusX = 0;
  plusorminusY = 0;
  n_minus_one = 1;
  n_minus_two = 0;
  sequence.push_back(0.0);
  sequence.push_back(0.0);
  sequence.push_back(n_minus_one);
}

void Fibonacci::generateSequence() {
  for(int i=0; i<max; i++ ) {
    int temp = n_minus_one + n_minus_two;
    sequence.push_back( temp );
    n_minus_two = n_minus_one;
    n_minus_one = temp;
  }
}

void Fibonacci::generateVisuals() {
  int count = 7; //0,0,1,1,2,3,5,8,13,21,34........
  bool Xdirection = true;
  bool Ydirection = false;
  bool first = true;
 
  sf::Vector2f origin( displayx/2.0, displayy/2.0 );
  sf::Vector2f offset(0,0);
  
  for( int i=0; i<271; i++ ) {
    if( i%90==0 && i > 0) { 
      count++;
      first = false;
    }

    if( i%180 == 0 && i > 0) {
      plusorminusX++;
      Xdirection = false;
      Ydirection = true;
    }

    if( i%270==0 && i > 0 ) {
      Xdirection = true;
      Ydirection = false;
    }
    
    if( first ) {
      sf::Vector2f Xtemp( -sequence[count]*sin(i*conv), sequence[count]*cos(i*conv) );
      sf::Vector2f placeX = origin + Xtemp + offset;	  
      circle.setPosition( placeX.x, placeX.y); 
      visuals.push_back( circle );
    }

    if( Xdirection && !first) {
      offset = sf::Vector2f( sequence[count-2], 0 );
      sf::Vector2f Xtemp( -sequence[count]*sin(i*conv), sequence[count]*cos(i*conv) );
      sf::Vector2f placeX = origin + Xtemp + offset;
	  
      circle.setPosition( placeX.x, placeX.y); 
      //circle.setFillColor(sf::Color( (2*i)%255,i%255,(3*i)%255));
      visuals.push_back( circle );
    }    
      
    if( Ydirection && !first) {
      offset = sf::Vector2f( sequence[count-3], sequence[count-2] );

      sf::Vector2f Ytemp( -sequence[count]*sin(i*conv), sequence[count]*cos(i*conv) );
      sf::Vector2f placeY = origin + Ytemp + offset;

      circle.setPosition( placeY.x, placeY.y); 
      visuals.push_back( circle );
	
    }
  }
}

void Fibonacci::draw(sf::RenderTarget& target, sf::RenderStates) const {
  std::vector<sf::CircleShape>::const_iterator cit;
  for( cit = visuals.begin(); cit != visuals.end(); cit++ )
    target.draw( *cit );
}
