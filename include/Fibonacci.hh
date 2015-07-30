#ifndef FIBONACCI_HH
#define FIBONACCI_HH

#include <SFML/Graphics.hpp>
#include <vector>

class Fibonacci : public sf::Drawable, public sf::Transformable {


private:
float displayx,displayy;
sf::RectangleShape square;
sf::CircleShape circle;

// Fibonacci variables
float max;
float n_minus_one, n_minus_two;
std::vector<float> sequence;
std::vector<float>::iterator it;
std::vector<sf::Vector2f> location;

public:
Fibonacci(float,float,float);
~Fibonacci() {};
void draw(sf::RenderTarget&, sf::RenderStates) const;
void generateSequence();
void generateVisuals();

};
#endif
