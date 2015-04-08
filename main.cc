#include <iostream>
#include <fstream>

int main(int argc, char * argv[]) {

    if(argc <= 1) {
        std::cout << "Error! No filename specified!" << std::endl;
        return -1;
    }

    std::fstream text_file(argv[1], std::ios_base::in);
    

    return 0;
}
