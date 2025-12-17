#include <iostream>

const double gravityAccel = 10.0;

double calc(double velX, double velY)
{
    double length = -1;

    double flyTime = velY / 10.0;
    length = flyTime * velX;

    return length;
}

signed main()
{
    std::cout << "[Input]: Enter velocity(X) and velocity(y):\n";
    double i, j;
    std::cin >> i >> j;

    std::cout << calc(i, j) << "\n";
    
    return 0;
}