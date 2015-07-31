#include "../include/Fibonacci.hh"
#include <iostream>
#include <cmath>
#include <sstream>

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
  plusorminusY = 1;
  n_minus_one = 1;
  n_minus_two = 0;
  sequence.push_back(0.0);
  sequence.push_back(0.0);
  //sequence.push_back(n_minus_one);

  // Animation
  first = true;
  counter = 0;
  top.setRadius( radius );
  originRect = top.getLocalBounds();
  top.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  top.setFillColor( sf::Color::Red );

  bottom.setRadius( radius );
  originRect = bottom.getLocalBounds();
  bottom.setOrigin( (originRect.width)/2.0, (originRect.height)/2.0 );
  bottom.setFillColor( sf::Color(0,255,255) );

  // Text
  if( !font.loadFromFile("fonts/arial.ttf")) {
    std::cerr << "ERROR: Font did not load properly." << std::endl;
  }
  text.setFont(font);
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
  int count = 3; //0,0,1,1,2,3,5,8,13,21,34,55,89,144........
  bool Xdirection = true;
  bool Ydirection = false;
  bool first = true;

  sf::Vector2f origin( 0.725*displayx, displayy/2.0 );
  sf::Vector2f offset(0,0);
  sf::Vector2f totaloffset(0,0);
  //std::cout << sequence[7] << " " << sequence[1] << std::endl;

  for( int i=0; i<1500; i++ ) {
    if( i%90==0 && i > 0 && i%180 != 0) { 
      count++;
      plusorminusY++;
      offset += sf::Vector2f( pow(-1,plusorminusX)*sequence[count-2], 0);
      Spiral.push_back( offset );
      //std::cout << offset.x << " 1 " << offset.y << std::endl;
      first = false;
    }

    if( i%180 == 0 && i > 0) {
      count++;
      plusorminusX++;
      Xdirection = false;
      Ydirection = true;
      offset += sf::Vector2f( 0, pow(-1,plusorminusY)*sequence[count-2]);  
      //std::cout << offset.x << " 2 " << offset.y << std::endl; 
      Spiral.push_back( offset );
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
      sf::Vector2f Xtemp( -sequence[count]*sin(i*conv), sequence[count]*cos(i*conv) );
      sf::Vector2f placeX = origin + Xtemp + offset;

      circle.setPosition( placeX.x, placeX.y); 
      visuals.push_back( circle );
    }    
      
    if( Ydirection && !first) {
      sf::Vector2f Ytemp( -sequence[count]*sin(i*conv), sequence[count]*cos(i*conv) );
      sf::Vector2f placeY = origin + Ytemp + offset;

      circle.setPosition( placeY.x, placeY.y); 
      visuals.push_back( circle );
	
    }
  }
}

void Fibonacci::Approximation() {
  float b = 0.0053468;
  sf::Vector2f origin( 0.725*displayx, displayy/2.0 );

  for(int i=0; i<2000; i++){
    float x = 0.10*cos(i*conv)*exp(b*i);
    float y = 0.10*sin(i*conv)*exp(b*i);
    sf::Vector2f position( x, y );
    sf::Vector2f temp = origin+position;
      
    circle.setFillColor( sf::Color((2*i)%255,(6*i)%255,(3*i)%255 ));
    circle.setPosition( temp.x, temp.y );
    visuals.push_back(circle);    
  }
}

void Fibonacci::draw(sf::RenderTarget& target, sf::RenderStates) const {
  std::vector<sf::CircleShape>::const_iterator cit;
  // for( cit = visuals.begin(); cit != visuals.end(); cit++ ) {
  //   target.draw( *cit );
  // }
  for( cit = visualsBottom.begin(); cit != visualsBottom.end(); cit++ ) {
    target.draw( *cit );
  }
  target.draw(sweep);
}

void Fibonacci::generateAnimation(int theta) {
  int startingPoint = 3;
  float width = 1.5;
  sf::Vector2f origin( 0.725*displayx, displayy/2.0 );
  sf::Vector2f size(0,0);
  sf::Vector2f temp(0,0);
  sf::Vector2f temp1(0,0);
  sf::Vector2f total(0,0);
  sweep.setFillColor( sf::Color::Red );
  if(theta<90) {
    size = sf::Vector2f(width,sequence[startingPoint]);
    sweep.setSize( size );
    sweep.setOrigin( size.x/2.0,0 );
    sweep.setPosition(origin.x,origin.y);
    sweep.setRotation( theta );
    temp = sf::Vector2f( -sequence[startingPoint]*sin(theta*conv), sequence[startingPoint]*cos(theta*conv) );
    total = temp + origin;
    bottom.setPosition(total);
    visualsBottom.push_back(bottom);

    std::ostringstream temp;
    temp << sequence[startingPoint];
    counterString= temp.str();
  }

  if( theta % 90 == 0 && theta > 0 ) {
    first = false;
    counter++;
    size = sf::Vector2f(width,sequence[startingPoint + counter]);
    sweep.setSize(size);
    temp = origin + Spiral[counter-1];
    sweep.setPosition( temp ); 

    std::ostringstream temp;
    temp << sequence[startingPoint+counter];
    counterString= temp.str();
  }

  if(theta >= 90 ) {
    sweep.setRotation( theta );
    
    temp1 = sf::Vector2f( -sequence[startingPoint+counter]*sin(theta*conv), sequence[startingPoint+counter]*cos(theta*conv) );
    total =  origin + Spiral[counter-1] + temp1;
    bottom.setPosition( total );
    visualsBottom.push_back(bottom);
  }
}
