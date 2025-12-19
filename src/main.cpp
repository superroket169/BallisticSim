#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <filesystem>

// yerçekimi sabiti
const double gravityAccel = 1000;
const std::string trueTypeFormatPath = "assets/fonts/DejaVuSans-Bold.ttf";

struct velocity
{
    double x;
    double y;
};

bool button(int x, int y, int w, int h, std::string str, sf::RenderWindow &window ,sf::Color color, sf::Font &font)
{
    static sf::Clock timer;
    sf::Text boxText(str, font, 24);
    boxText.setFillColor(sf::Color::Black);
    boxText.setPosition(x + 10, y + 10);

    sf::RectangleShape b;
    b.setSize({(float)w, (float)h});
    b.setPosition((float)x, (float)y);
    b.setFillColor(color);
    window.draw(b);
    window.draw(boxText);

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        if(b.getGlobalBounds().contains(worldPos) && timer.getElapsedTime().asMilliseconds() > 500)
        {
            timer.restart();
            return 1;
        }
    
    return 0;
}
std::string typeStringFirstButton = "";
std::string typeStringSecondButton = "";

signed main()
{
    std::cout << "CWD = "
              << std::filesystem::current_path()
              << std::endl;

    sf::Font font;
    if(!font.loadFromFile(trueTypeFormatPath))
        std::cerr << "File cant opened\n";

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

    velocity velocityInput = {0, 0};
    //std::cin >> velocityInput.x >> velocityInput.y;
    velocityX = velocityInput.x;
    velocityY = velocityInput.y;

    sf::Color firstButtonColor1 = {100, 100, 255};
    sf::Color firstButtonColor2 = {50, 50, 255};
    sf::Color firstButtonColor = firstButtonColor1;

    sf::Color secondButtonColor1 = {100, 100, 255};
    sf::Color secondButtonColor2 = {50, 50, 255};
    sf::Color secondButtonColor = secondButtonColor1;

    bool inTypingFirstButton = false;
    bool justEnteredFirstButton = false;
    bool inTypingSecondButton = false;
    bool justEnteredSecondButton = false;
    bool grounded = false;
    
    while(window.isOpen())
    {
        float dt = clock.restart().asSeconds();

        window.clear(sf::Color(200, 255, 200));
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();

                if(event.key.code == sf::Keyboard::Enter)
                {
                    if(inTypingFirstButton)
                    {
                        inTypingFirstButton = false;
                        firstButtonColor = firstButtonColor1;
                        justEnteredFirstButton = true;
                    }
                    else if(inTypingSecondButton)
                    {
                        inTypingSecondButton = false;
                        secondButtonColor = firstButtonColor1;
                        justEnteredSecondButton = true;
                    }

                    //inTypingFirstButton = false;
                    //firstButtonColor = firstButtonColor1;
                    //justEnteredFirstButton = true;
                }
            }

            if(event.type == sf::Event::TextEntered && inTypingFirstButton)
            {
                if(event.text.unicode == 8 && !typeStringFirstButton.empty())
                    typeStringFirstButton.pop_back();
                
                if(event.text.unicode < 128)
                {
                    char c = static_cast<char>(event.text.unicode);
                    // only numbers
                    if((c >= '0' && c <= '9') || c == '-')
                        typeStringFirstButton += c;
                }
            }
            if(event.type == sf::Event::TextEntered && inTypingSecondButton)
            {
                if(event.text.unicode == 8 && !typeStringSecondButton.empty())
                    typeStringSecondButton.pop_back();
                
                if(event.text.unicode < 128)
                {
                    char c = static_cast<char>(event.text.unicode);
                    // only numbers
                    if((c >= '0' && c <= '9') || c == '-')
                        typeStringSecondButton += c;
                }
            }
        }

        // first button
        if(button(20, 20, 100, 50, typeStringFirstButton, window, firstButtonColor, font) && !inTypingSecondButton)
        {
            firstButtonColor = firstButtonColor2;
            inTypingFirstButton = true;
        }

        // second button
        if(button(140, 20, 100, 50, typeStringSecondButton, window, secondButtonColor, font) && !inTypingFirstButton)
        {
            secondButtonColor = secondButtonColor2;
            inTypingSecondButton = true;
        }

        speed = std::sqrt((velocityX * velocityX) + (velocityY * velocityY));

        if(!inTypingFirstButton && justEnteredFirstButton)
        {
            justEnteredFirstButton = false;
            grounded = false;
            try
            {
                velocityY -= std::stoi(typeStringFirstButton);
            }
            catch(std::exception e)
            {
                std::cerr << "mmew\n";
            }
        }

        if(!inTypingSecondButton && justEnteredSecondButton)
        {
            justEnteredSecondButton = false;
            grounded = false;
            try
            {
                velocityX = std::stoi(typeStringSecondButton);
            }
            catch(std::exception e)
            {
                std::cerr << "mmew\n";
            }
        }

        {// acceleration:
            float groundY = windowY - floorHeight - massRadius;

            // gravity sadece havadayken
            if(!grounded)
                velocityY += gravityAccel * dt;

            // hareket
            mass.move(velocityX * dt, velocityY * dt);

            // zemin çarpışması
            if(mass.getPosition().y >= groundY)
            {
                mass.setPosition(mass.getPosition().x, groundY);
                velocityY = 0;
                grounded = true;
            }
            else
            {
                grounded = false;
            }
        }

        window.draw(floor);
        window.draw(mass);
        window.display();

        //std::cout << int(velocityY * 100) << "\n";
    }

    return 0;
}