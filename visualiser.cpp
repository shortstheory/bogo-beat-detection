#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <time.h>
//#include <cstdio.h>
const int bands = 256;
const int n = 256;
const int width = n / bands;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 900), "FFT Visualiser");
    window.setVerticalSyncEnabled(true);
    sf::RectangleShape bars[n], t;
    int i;
    t.setSize(sf::Vector2f(200, 500));
    t.setPosition(500, 100);
    double val[256];
    double subbands[bands];
    std::ifstream input("output/fftWindows");
//    sf::Color barColor;
    for (i = 0; i < bands; i++) {
        bars[i].setFillColor(sf::Color(n - i * width, 0 + i * width, i*width));
    }
    sf::Music music;
    if (!music.openFromFile("sounds/file1.wav")) {
        return -1;
    }
    music.play();
    while (window.isOpen()) {
        //while (!input.eof()) {
        std::clock_t start = std::clock();
        double a, b;
        for (i = 0; i < n && !input.eof(); i++) {
            input >> a >> b;

            input >> val[i];
            //input.flush();
        }
        std::cout << a << std::endl;
        for (i = 0; i < bands; i++) {
            double sum=0;
            for (int j = 0; j < width; j++) {
                sum+=val[j+i*width];
            }
            subbands[i] = sum / width;
        }
        for (i = 0; i < bands; i++) {
            double height = subbands[i] *100;
            bars[i].setSize(sf::Vector2f(4*width, height));
            bars[i].setPosition(i*(width*4 + 1), 1000 - height);\
        }
        window.clear(sf::Color::Black);
        for (i = 0; i < bands; i++) {
             window.draw(bars[i]);
         }
         while (std::clock() - start < 0.021 * 1000000)
         {}
             // window.draw(t);
        window.display();
            //usleep(0.02322*1000000);
//}
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}
