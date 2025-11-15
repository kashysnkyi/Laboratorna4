#pragma once
#include <vector>
#include <string>
#include <mutex>
#include <sstream>

class DataStructure {
private:
    std::vector<int> fields;         // наші 2 поля
    std::vector<std::mutex> mtx;     // окремий м’ютекс на кожне поле
    std::mutex string_mtx;           // м’ютекс для string операції

public:
    DataStructure(int m);

    int read(int index);
    void write(int index, int value);
    std::string toString();
};
