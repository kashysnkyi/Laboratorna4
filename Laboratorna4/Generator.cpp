#include <iostream>
#include <fstream>
#include <random>
#include <vector>

// структура частот
struct ActionFreq {
    double r0, w0, r1, w1, s;
};

void generateFile(const std::string& name, ActionFreq f, int total)
{
    std::ofstream out(name);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> d(0, 100);

    for (int i = 0; i < total; i++) {
        double x = d(gen);

        if (x < f.r0) out << "read 0\n";
        else if (x < f.r0 + f.w0) out << "write 0 1\n";
        else if (x < f.r0 + f.w0 + f.r1) out << "read 1\n";
        else if (x < f.r0 + f.w0 + f.r1 + f.w1) out << "write 1 1\n";
        else out << "string\n";
    }
}

void runGenerator()
{
    int total = 200000;

    std::cout << "Generating variant file...\n";
    generateFile("actions_var1.txt", { 10, 5, 50, 5, 30 }, total);

    std::cout << "Generating equal file...\n";
    generateFile("actions_equal.txt", { 20, 20, 20, 20, 20 }, total);

    std::cout << "Generating bad file...\n";
    generateFile("actions_bad.txt", { 1, 1, 1, 1, 96 }, total); // 96% string

    std::cout << "Files generated.\n";
}
