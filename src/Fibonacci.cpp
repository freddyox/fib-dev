#include "../include/Fibonacci.hh"
#include <iostream>

Fibonacci::Fibonacci(float width, float height, float maximum) {
  displayx = width;
  displayy = height;
  max = maximum;
  n_minus_one = 1;
  n_minus_two = 0;
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
  sf::Vector2f origin( displayx/2.0, displayy/2.0 );
  sf::Vector2f temp(0,1);

  location.push_back( temp );
  sf::Vector2f temp(1,0.5);
  location.push_back(temp);
  sf::Vector2f temp(5/2,-1/2);
  location.push_back(temp);
  sf::Vector2f temp(-4,1);
  location.push_back(temp);




  for( it = sequence.begin(); it != sequence.end(); it++ ){
    sf::Vector2f size( *it,*it );
    square.setSize( size );
    square.setFillColor(sf::Color::Red);
    //quare.setPosition( );
  }
}

void Fibonacci::draw(sf::RenderTarget& target, sf::RenderStates) const {
  target.draw(circle);
}
