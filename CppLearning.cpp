#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

struct Start {

    int temperature, humidity, pressure;
    Start(int temperature, int humidity, int pressure) : temperature{ temperature }, humidity{ humidity }, pressure{ pressure } {}
    int getTemperature() const { return temperature; }
    int getHumidity() const { return humidity; }
    int getPressure() const { return pressure; }

    void setTemperature(int startTemperature) { temperature = startTemperature; }
    void setHumidity(int startHumidity) { humidity = startHumidity; }
    void setPressure(int startPressure) { pressure = startPressure; }

};
// Для текстовых файлов
std::ostream& operator << (std::ostream& os, const Start& start)
{
    return os << start.getTemperature() << " " << start.getHumidity() << " " << start.getPressure();
};
std::istream& operator >> (std::istream& in, Start& start)
{
    int temperature, humidity, pressure;
    in >> temperature >> humidity >> pressure;
    // если ввод не удался, устанавливаем некоторые значения по умолчанию
    if (in)
    {
        start.setTemperature(temperature);
        start.setHumidity(humidity);
        start.setPressure(pressure);
    }
    return in;
};
void saveToFileTxt(std::vector<Start> weather, std::string file) {  // сохранение в текстовый файл
    std::ofstream fout(file);
    if (fout.is_open()) {
        for (const Start& weather : weather)
        {
            fout << weather << std::endl;
        }
    }
    fout.close();
};
void loadFromFileTxt(std::string file) {    // чтение из текстового файла
    std::vector<Start> new_start; // вектор для считываемых данных
    std::ifstream fin(file);
    if (fin.is_open())
    {
        Start start{ 0,0,0 };
        while (fin >> start)
        {
            new_start.push_back(start);
        }
    }
    for (const Start& start : new_start)
    {
        std::cout << start << std::endl;
    }
    fin.close();
};
void saveToFileBin(std::vector<Start> weather, std::string file) {  // сохранение в бинарный файл
    std::ofstream fout(file, std::ios_base::binary);

    if (fout.is_open()) {
        for (const Start& weather : weather)
        {
            fout.write((char*)&weather, sizeof(weather));
        }

    }

    fout.close();
};
void loadFromFileBin(std::string file) { // чтение из бинарного файла
    std::vector<Start> new_start; // вектор для считываемых данных 
    std::ifstream fin(file, std::ios_base::binary); // чтение ранее записанных данных из файла

    if (fin.is_open()) {
        Start start{ 0, 0, 0 };  // создание пустой структуры 

        while (fin.read((char*)&start, sizeof(start)))
        {
            new_start.push_back(start);
        }
    }
    fin.close();
    for (const Start& start : new_start)
    {
        std::cout << start << std::endl;
    }

};
int main()
{
    // Для текстовых файлов
    std::string nameFileTxt = "Test.txt";
    std::vector<Start> weather = { {10, 63, 760}, {15, 63, 758}, {20, 60, 763}, {27, 50, 769} };

    saveToFileTxt(weather, nameFileTxt);
    loadFromFileTxt(nameFileTxt);

    std::cout << "*************************" << std::endl;

    // Для бинарных файлов
    std::string nameFileBin = "Test.bin";

    saveToFileBin(weather, nameFileBin);
    loadFromFileBin(nameFileBin);

}

