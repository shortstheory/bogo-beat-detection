#include <iostream>
#include <fstream>
#include <fftw3.h>
#include <math.h>
#include <algorithm>
const int n = 1024;
void findSubbands(double* input, double* output)
{
    int i;
    int j;
    for (i = 0; i < n / 2; i++) {
        double sum = 0;
        for (j = 0; j < 32; j++) {
            sum += input[i*32 + j];
        }
        output[i] = sum / 32.0;
    }
}

int main()
{
    fftw_complex inputCh0[n], inputCh1[n];
    fftw_complex outputCh0[n], outputCh1[n];
    //fftw_complex;
    //fftw_plan p;
    double subbands[32];
    double fftValue[n/2];
    double meanValues[n/2];
    double outputSubbands[n/2][32];
    double meanSubbands[32];

    std::ifstream input("values");
    std::ofstream output("fftWindows");

    int i;
    int j;
    long itCounter = 0;
    while (!input.eof()) {
        for (i = 0; i < n; i++) {
           input >> inputCh0[i][0] >> inputCh1[i][0];
           inputCh0[i][1] = 0; //complex part is 0
           inputCh1[i][1] = 0;
           outputCh0[i][0] = 0;
           outputCh0[i][1] = 0;
           outputCh1[i][0] = 0;
           outputCh1[i][1] = 0;
       }
       fftw_plan p0 = fftw_plan_dft_1d(n, inputCh0, outputCh0, FFTW_FORWARD, FFTW_ESTIMATE);
       fftw_plan p1 = fftw_plan_dft_1d(n, inputCh1, outputCh1, FFTW_FORWARD, FFTW_ESTIMATE);
       fftw_execute(p0);
       fftw_execute(p1);
       for (j = 0; j < 256; j++) {
           double magnitude0 = log10(sqrt(outputCh0[j][0]*outputCh0[j][0] + outputCh0[j][1]*outputCh0[j][1]));
           double magnitude1 = log10(sqrt(outputCh1[j][0]*outputCh1[j][0] + outputCh1[j][1]*outputCh1[j][1]));
           fftValue[j] = sqrt(magnitude0 * magnitude0 + magnitude1 * magnitude1);
           fftValue[j] = (j == 0) ? 0 : fftValue[j];
           output << itCounter * 1024 / 44100.0 << ' ' << 44100 * j / n << ' ' << fftValue[j] << std::endl;
              // meanValues[j] += fftValue[j];
       }
       itCounter++;
   }
   return 0;
}
/*    for (i = 0; i < n; i++) {
        input >> inputCh0[i][0] >> inputCh1[i][0];
        inputCh0[i][1] = 0; //complex part is 0
        inputCh1[i][1] = 0;
    }
    for (i = 0; i < 43; i++) {
        for (j = 0; j < 1024; j++) {
            input >> inputCh0[i] >> inputCh1[i];
        }
        fftw_plan p0 = fftw_plan_dft_1d(n, inputCh0, outputCh0[i], FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_plan p1 = fftw_plan_dft_1d(n, inputCh1, outputCh1[i], FFTW_FORWARD, FFTW_ESTIMATE);
        fftw_execute(p0);
        fftw_execute(p1);
        for (j = 0; j < 512; j++) {
            double magnitude0 = log10(sqrt(outputCh0[i][j][0]*outputCh0[i][j][0] + outputCh0[i][j][1]*outputCh0[i][j][1]));
            double magnitude1 = log10(sqrt(outputCh1[i][j][0]*outputCh1[i][j][0] + outputCh1[i][j][1]*outputCh1[i][j][1]));
            fftValue[j] = sqrt(magnitude0 * magnitude0 + magnitude1 * magnitude1);
            fftValue[j] = (j == 0) ? 0 : fftValue[j];
            meanValues[j] += fftValue[j];
        }
    }
    for (i = 0; i < 512; i++) {
        meanValues[i] /= 43;
    }
    findSubbands(meanValues, meanSubbands);
    findSubbands(m)
    while (!input.eof()) { //sets our window to n/2 of previous and n/2 of next for smoother results
*/
        //do fft
        //do frequency sub-bands, this method is fucking crazy

        /*for (i = 1; i < n / 4; i++) { //don't need 0hz. or high f for that matter
            //how should we handle values now?
            //should we take magnitude of logs of channels?
            //yeah we should
            double magnitude0 = log10(sqrt(outputCh0[i][0]*outputCh0[i][0] + outputCh0[i][1]*outputCh0[i][1]));
            double magnitude1 = log10(sqrt(outputCh1[i][0]*outputCh1[i][0] + outputCh1[i][1]*outputCh1[i][1]));
            double fftValue = sqrt(magnitude0 * magnitude0 + magnitude1 * magnitude1);

            maxv = std::max(maxv, fftValue);
            //512 unique values/window
            if (fftValue > 6) {
            //    output << 44100.0 * i / n << ' ' << "time " << n/2*itCounter/44100.0 << ' ' << fftValue << std::endl;
            //    std::cout << 44100.0 * i / n << ' '  << maxv << " time " << n/2*itCounter/44100.0 << std::endl;
            }
        }*/
        /*for (i = 0; i < 16; i++) { //generate subbands
            double sum = 0;
            for (int j = 32*i; j < 32*i + 32; j++) {
                double magnitude0 = log10(sqrt(outputCh0[j][0]*outputCh0[j][0] + outputCh0[j][1]*outputCh0[j][1]));
                double magnitude1 = log10(sqrt(outputCh1[j][0]*outputCh1[j][0] + outputCh1[j][1]*outputCh1[j][1]));
                double fftValue = sqrt(magnitude0 * magnitude0 + magnitude1 * magnitude1);
                sum += fftValue;
            }
            subbands[i] = sum / 31.0;
            output << 1024 * i << "time " << n/2*itCounter/44100.0 << ' ' << subbands[i] << std::endl;
        }*/
        /*
        for (i = 0; i < n / 2; i++) {
            //update values
            inputCh0[i][0] = inputCh0[i + n / 2][0];
            inputCh1[i][0] = inputCh1[i + n / 2][0];
            if (!input.eof()) {
                input >> inputCh0[i + n / 2][0] >> inputCh1[i + n / 2][0];
            }
        }*/
        /*for (i = 0; i < n; i++) { //trying out
            //update values
            if (!input.eof()) {
                input >> inputCh0[i][0] >> inputCh1[i][0];
            }
        }*/
//        itCounter++;
    //}
