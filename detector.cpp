#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

long long globalCount = 0;

struct bucketValue {
    float left;
    float right;
    bucketValue() {
        left = 0;
        right = 0;
    }
};

float fillBucket(bucketValue *bucket, std::ifstream &input)
{
    float sum = 0;
    int i;
    for (i = 0; i < 1024; i++) {
        input >> bucket[i].left >> bucket[i].right;
        sum += bucket[i].left * bucket[i].left + bucket[i].right * bucket[i].right;
        globalCount++;
    }
    return sum;
}

float bufferMeanValue(std::vector<float> &buffer)
{
    unsigned int i;
    float sum = 0;
    for (i = 0; i < buffer.size(); i++) {
        sum += buffer[i];
    }
    sum /= 43.0;
    return sum;
}

int main()
{
    std::ifstream input("values");
    bucketValue bucket[1024];
    std::vector<float> buffer;
    int j;
    float temp;
    for (j = 0; j < 43; j++) {
        temp = fillBucket(bucket, input) / 1024.0;
        buffer.push_back(temp);
    }
    float previous=0;
    while (!input.eof()) {
        if (buffer[0] > bufferMeanValue(buffer) * 1.3) {
            if (previous == 0) {
                std::cout << globalCount / 44100.0 << std::endl;
            } else {
                std::cout << globalCount / 44100.0 << std::endl;// - previous << std::endl;
            }
            previous = globalCount / 44100.0;
        }

        temp = fillBucket(bucket, input) / 1024.0;
        buffer.erase(buffer.begin());
        buffer.push_back(temp);
    }
    return 0;
}
