#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

std::vector<int> conversionToBinarySystem(int num) {
    std::vector<int> bin, bin32;
    int division = 1, remainder;

    while (division != 0) {
        division = num / 2;
        remainder = num % 2;
        if (remainder == 0) {
            bin.emplace_back(0);
        }
        else {
            bin.emplace_back(1);
        }
        num = division;
        remainder = 0;
    }

    bin32.resize(32 - bin.size());
    std::reverse(bin.begin(), bin.end());
    int n = bin32.size() - bin.size();
    bin32.insert(bin32.end(), bin.begin(), bin.end());

    return bin32;
};

struct Start {

    int temperature = 23, humidity = 80, pressure = 761;

};
void writeToFile(std::vector<int> a) {
    std::ofstream fout("Test.txt");

    for (int i = 0; i < a.size(); i++) {
        fout << a[i];
    };

    fout.close();
};
std::string readingFromFile() {
    std::ifstream fin("Test.txt");
    std::string resultFromFile;

    while (std::getline(fin, resultFromFile))
    {
        std::cout << resultFromFile << std::endl;
    }

    fin.close();

    return resultFromFile;
};

int main()
{
    Start oneDay;
    std::vector<int> BinaryTemperature, BinaryHumidity, BinaryPressure, result;

    BinaryTemperature = conversionToBinarySystem(oneDay.temperature);
    BinaryHumidity = conversionToBinarySystem(oneDay.humidity);
    BinaryPressure = conversionToBinarySystem(oneDay.pressure);

    result = BinaryTemperature;
    result.insert(result.end(), BinaryHumidity.begin(), BinaryHumidity.end());
    result.insert(result.end(), BinaryPressure.begin(), BinaryPressure.end());
     

    writeToFile(result);
    
    readingFromFile();
    
}

