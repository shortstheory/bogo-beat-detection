#include <fstream>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <cstdio>
#include <ctime>
#include <vector>

int main()
{
    const long mill = 1000000;
      std::ifstream input("data");
    FILE *file;
    file = fopen("/dev/ttyACM1","w");  //Opening device file
    fprintf(file, "%d", 0);
   // float x;

    std::clock_t start;
    double duration;
    start = std::clock();

    std::vector<float> data;
    while (!input.eof()) {
        float temp;
        input >> temp;
        data.push_back(temp);
    }

    int i;
    //nsleep(20*100);
    for (i = 0; i < data.size();) {
        if ((std::clock() - start) > data[i] * mill) {
            std::cout << data[i] << ' ' << std::clock() - start << std::endl;
            fprintf(file, "%d", 1);
            std::clock_t currentTime = std::clock();
            fflush(file);
            fprintf(file, "%d", 0);
            fflush(file);
            usleep(1000000);
 
            std::cout << "offtime";
            i++;
        }
    }
    return 0;
}
