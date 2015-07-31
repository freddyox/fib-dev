//    ************************************************************
//    *                           Fibonacci                      *
//    *                           July 2015                      *
//    ************************************************************
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <iostream>
#include <sstream>
#include <string>

#include "../include/Fibonacci.hh"

const float gDisplayx = 1000;
const float gDisplayy = 1000;
int main() {
  //GAME SETUP
  sf::RenderWindow window(sf::VideoMode(gDisplayx,gDisplayy), "Fibonacci");
  window.setFramerateLimit(60);

  // Handling Time 
  sf::Clock clock;
  float t = 0.0;
  float dt = 1.0/60.0;
  sf::Time time;
  int clicker=0;

  //////////////////////////////////////////////////////
  //                   Parameters                     //
  //////////////////////////////////////////////////////


  // Initializations
  Fibonacci fib( window.getSize().x, window.getSize().y, 30. );
  fib.generateSequence();
  fib.generateVisuals();
  //fib.Approximation();
  
  // Text
  sf::Text text;
  sf::Font font;
  if( !font.loadFromFile("fonts/arial.ttf")) {
    std::cerr << "ERROR: Font did not load properly." << std::endl;
  }
  std::string temp;
  text.setFont(font);
  text.setColor( sf::Color::Blue );
  text.setCharacterSize(30);
  text.setPosition(0.25*1000,0.25*1000);

  while( window.isOpen() ) {

    sf::Event event;
    while( window.pollEvent(event) ) {
      if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ) {
	window.close();
      }
    }
    window.clear();

    // UPDATING
    if( clicker < 1267 ) {
      fib.generateAnimation(clicker);
      temp = fib.getFibonacciString();
    }
    text.setString( temp );
    // DRAWINGS
    window.draw(fib);
    window.draw(text);
    window.display();   

    t += dt;
    clicker++;
  }

  return 0;
}
