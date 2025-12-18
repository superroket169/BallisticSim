#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

// yerçekimi sabiti
const double gravityAccel = 1000;
const std::string trueTypeFormatPath = "DejaVuSans-Bold.ttf";

struct velocity
{
    double x;
    double y;
};

bool button(int x, int y, int w, int h, std::string str, sf::RenderWindow &window ,sf::Color color, sf::Font &font)
{
    sf::Text boxText(str, font, 24);
    boxText.setFillColor(sf::Color::Black);
    boxText.setPosition(x + 50, y + (h/2) - 15);

    sf::RectangleShape b;
    b.setSize({(float)w, (float)h});
    b.setPosition((float)x, (float)y);
    b.setFillColor(color);
    window.draw(b);
    window.draw(boxText);

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        if (b.getGlobalBounds().contains(worldPos))
            return 1;
        
    
    return 0;
}
std::string typeString = "m";

signed main()
{
    sf::Font font;
    font.loadFromFile(trueTypeFormatPath);

    const int floorHeight = 100;
    const int massRadius = 20;
    const int windowX = 1200;
    const int windowY = 800;
    sf::RenderWindow window(sf::VideoMode(windowX, windowY), "PixelDrift");

    sf::CircleShape mass(massRadius);
    mass.setFillColor(sf::Color::Black);
    mass.setOrigin(mass.getRadius(), mass.getRadius());
    mass.setPosition(floorHeight, windowY - floorHeight - massRadius - 1);

    sf::RectangleShape floor({windowX, floorHeight});
    floor.setFillColor(sf::Color::Red);
    floor.setPosition(0, 0);
    floor.setPosition(0, windowY - floorHeight);

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
        if(button(50, 50, 200, 100, typeString, window, sf::Color::Blue, font));

        speed = std::sqrt((velocityX * velocityX) + (velocityY * velocityY));

        {// acceleration:
            if(mass.getPosition().y < (windowY - floorHeight - massRadius))
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