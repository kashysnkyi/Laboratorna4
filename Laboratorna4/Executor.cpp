#include "DataStructure.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread>

void executeFile(DataStructure& ds, const std::string& filename) {
    std::ifstream file(filename);
    std::string op;
    int index, value;

    while (file >> op) {
        if (op == "read") {
            file >> index;
            ds.read(index);
        }
        else if (op == "write") {
            file >> index >> value;
            ds.write(index, value);
        }
        else if (op == "string") {
            ds.toString();
        }
    }
}

double runSingle(DataStructure& ds, const std::string& file)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    executeFile(ds, file);
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(t2 - t1).count();
}

void testFile(const std::string& name)
{
    std::cout << "\n===== Testing file: " << name << " =====\n";

    DataStructure ds1(2);

    std::cout << "--- Single thread ---\n";
    double t_single = runSingle(ds1, name);
    std::cout << t_single << " sec\n";

    // 2 threads
    std::cout << "--- 2 threads ---\n";
    double r1 = 0, r2 = 0;

    DataStructure ds2(2);
    std::thread th1([&]() { r1 = runSingle(ds2, name); });
    std::thread th2([&]() { r2 = runSingle(ds2, name); });
    th1.join();
    th2.join();

    std::cout << "T1: " << r1 << " sec\n";
    std::cout << "T2: " << r2 << " sec\n";
    std::cout << "Avg: " << (r1 + r2) / 2 << " sec\n";

    // 3 threads
    std::cout << "--- 3 threads ---\n";
    double a = 0, b = 0, c = 0;

    DataStructure ds3(2);
    std::thread t3([&]() { a = runSingle(ds3, name); });
    std::thread t4([&]() { b = runSingle(ds3, name); });
    std::thread t5([&]() { c = runSingle(ds3, name); });

    t3.join();
    t4.join();
    t5.join();

    std::cout << "T1: " << a << " sec\n";
    std::cout << "T2: " << b << " sec\n";
    std::cout << "T3: " << c << " sec\n";
    std::cout << "Avg: " << (a + b + c) / 3 << " sec\n";
}

void runExecutor()
{
    testFile("actions_var1.txt");
    testFile("actions_equal.txt");
    testFile("actions_bad.txt");
}
