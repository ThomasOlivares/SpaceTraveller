#pragma once

#include <SFML/System/Vector2.hpp>

class Circle{

	public :
							Circle();
							Circle(const Circle& circle);
							Circle(sf::Vector2f center_, float radius_);

		float 				getRadius() const;
		void 				setRadius(float radius_);
		sf::Vector2f 		getCenter() const;
		void 				setCenter(sf::Vector2f center_);

		bool 				contain(sf::Vector2f center);

	private :
		sf::Vector2f 		center;
		float 				radius;
};