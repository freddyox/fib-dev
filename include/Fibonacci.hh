#ifndef FIBONACCI_HH
#define FIBONACCI_HH

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Fibonacci : public sf::Drawable, public sf::Transformable {


private:
  float displayx,displayy;
  float radius,conv;
  sf::CircleShape top,bottom,circle;
  sf::Vector2f origin;

  // Fibonacci variables
  float max;
  float n_minus_one, n_minus_two;
  std::vector<float> sequence;
  std::vector<float>::iterator it;
  std::vector<sf::CircleShape> visuals,visualsBottom;
  int plusorminusX, plusorminusY;

  // Animation
  bool first;
  int counter;
  std::string counterString;
  sf::RectangleShape sweep;
  std::vector<sf::Vector2f> Spiral;
  std::vector<sf::Vector2f>::iterator Spit;

  // Text
  sf::Text text;
  sf::Font font;
  std::vector<sf::Text> textVec;

public:
  Fibonacci(float,float,float);
  ~Fibonacci() {};
  void draw(sf::RenderTarget&, sf::RenderStates) const;
  void generateSequence();
  void generateVisuals();
  void Approximation();
  void generateAnimation(int);
  std::string getFibonacciString() {return counterString;}
};
#endif
