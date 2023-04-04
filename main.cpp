#include <iostream>
#include "src/Manager.h"

int main() {
    Manager m;
    std::cout << "sexo" << std::endl;
    m.readFiles();
    std::cout << "mega sexo" << std::endl;
    m.mainMenu();
    return 0;
}
