#include <iostream>

// оголошення функцій з інших файлів
void runGenerator();   // з Generator.cpp
void runExecutor();    // з Executor.cpp

int main() {
    std::cout << "--- Generating files... ---\n";
    runGenerator();

    std::cout << "--- Running executor... ---\n";
    runExecutor();

    std::cout << "--- Done ---\n";
    return 0;
}
 