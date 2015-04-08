#include <iostream>
#include <fstream>

void conversion(std::istream& is) {
    std::string line;
    int line_size;
    int i = 0;
    if(!std::getline(is, line))
      return;
    line_size = line.size();
    int num_cfebs = 5;
    while(line[i] != '|'){
        ++i;
    }
    ++i;
    for(int j=0; j<num_cfebs; ++j){
      int n = 0;
      int byte = 0;
      while(line[i] != '|'){
          if(line[i] == '1')
              byte |= 0x1 << (8 - n);
          ++n;
          ++i;
      }
      ++i;
      std::cout << byte << "\n";
    }
}

void convert_file(std::istream& is) {
  while(is) {
    conversion(is);
  }
}

int main(int argc, char * argv[]) {

    if(argc <= 1) {
        std::cout << "Error! No filename specified!" << std::endl;
        return -1;
    }

    std::fstream text_file(argv[1], std::ios_base::in);

    std::string text = "01001100";

    int n = 0;
    int n_bits = text.size();
    
    for(int i=0; i<n_bits; ++i) {
        if(text[i] == '1') {
            n |= 0x1 << (n_bits-1 - i);
        }
    }


    std::cout << "this is the start of the conversion \n";
    //std::string org_file_name = avg
    std::cout << n << std::endl;
    //for(int i = 0 )
    convert_file(text_file);




    return 0;
}
