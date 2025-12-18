#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

const double gravityAccel = 1000;

struct velocity
{
    double x;
    double y;
};


double calc(double velX, double velY)
{
    double length = -1;

    double flightTime = velY / 10.0;
    length = flightTime * velX;

    return length;
}

signed main()
{
    const int windowX = 1200;
    const int windowY = 800;
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "PixelDrift");

    sf::CircleShape mass(20);
    mass.setFillColor(sf::Color::Black);
    mass.setOrigin(mass.getRadius(), mass.getRadius());
    mass.setPosition(100, 679);

    sf::RectangleShape floor({1200, 100});
    floor.setFillColor(sf::Color::Red);
    floor.setPosition(0, 0);
    floor.setPosition(0, windowY - 100);

    double speed = 0;
    double velocityX = 0;
    double velocityY = 0;

    sf::Clock clock;

    velocity velocityInput = {300, -1000};
    //std::cin >> velocityInput.x >> velocityInput.y;
    velocityX = velocityInput.x;
    velocityY = velocityInput.y;
    
    while(window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        window.clear(sf::Color(200, 255, 200));
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }    

        speed = std::sqrt((velocityX * velocityX) + (velocityY * velocityY));

        {// acceleration:
            if(mass.getPosition().y < 680)
            {
                velocityY += gravityAccel * dt;
            }
            else
            {
                velocityX = 0;
                velocityY = 0;
            }
            mass.move(velocityX * dt, velocityY * dt);
        }

        window.draw(floor);
        window.draw(mass);
        window.display();

        std::cout << int(velocityY * 100) << "\n";
    }

    return 0;
}