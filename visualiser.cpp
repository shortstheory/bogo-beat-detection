#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <time.h>
//#include <cstdio.h>
const int bands = 64;
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
    std::vector<double> val(n);
    std::vector<double> subbands(bands);
    std::vector<double> history(n*43);
    std::ifstream input("output/fftWindows");
//    sf::Color barColor;
    for (i = 0; i < bands; i++) {
        bars[i].setFillColor(sf::Color(n - i * width, 0 + i * width, i*width));
    }
    sf::Music music;
    if (!music.openFromFile("sounds/file2.wav")) {
        return -1;
    }
    music.play();
    auto historyIt = history.begin();
    while (historyIt != history.end()) {
        *historyIt=0;
        historyIt++;
    }
    input.close();
    input.open("output/fftWindows");
    while (window.isOpen()) {
        //while (!input.eof()) {
        std::clock_t start = std::clock();
        double a, b;
        for (i = 0; i < n && !input.eof(); i++) {
            input >> a >> b;
            input >> val[i];
            //input.flush();
        }
        for (i = 0; i < 43 * (n - 1); i++) {
			history[n + i] = history[i];
		}
		for (i = 0; i < n; i++) {
			history[i] = val[i];
		}

        for (i = 0; i < bands; i++) {
            double sum=0;
            for (int j = 0; j < width; j++) {
                sum+=val[j+i*width];
            }
            subbands[i] = sum / width;
            std::cout << a << ' ' << subbands[i] << std::endl;
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
