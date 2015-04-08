#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


// Expects next char to be beginning of byte
unsigned int get_next(std::istream & is, char sep = '|') {
    unsigned int n = 0;
    char c;
    bool next;
    while(is) {
        if(!is.get(c))
            break;
        if(c == '0')
            next = false;
        else if(c == '1')
            next = true;
        else if(c == sep)
            break;
        else
            continue;
        n = (n << 1) | next;
    }
    return n;
}

bool clear_until(std::istream & is, char b_char) {
    char c = 0;
    while(is) {
        if(!is.get(c) || c == b_char)
            break;
    }
    return is;
}

void convert(std::istream & is, std::string prefix = "", char sep = '|') {
    std::vector<std::fstream *> oss;
    int l;
    int n = 0;
    int layers = 0;
    char c = 0;

    is >> l >> l;
    clear_until(is, sep);
    std::stringstream ss;
    ss << "CFEB_" << n << ".pat";
    oss.push_back(new std::fstream(ss.str().c_str(), std::ios_base::out));
    while(is) {
        c = get_next(is, sep);
        if(!is)
            break;
        (*(oss[n])) << c;
        ++layers;
        if(is.peek() == '\n' || is.peek() == '\r')
            break;
    }
    ++n;

    while(is) {
        is >> l >> l;
        clear_until(is, sep);
        if(l == n) {
            std::stringstream ss;
            ss << prefix << "CFEB_" << n << ".pat";
            oss.push_back(new std::fstream(ss.str().c_str(), std::ios_base::out));
            ++n;
        }
        while(is) {
            c = get_next(is, sep);
            if(!is)
                break;
            (*(oss[l])) << c;
            if(is.peek() == '\n' || is.peek() == '\r')
                break;
        }
    }

    for(int i=0; i<n; ++i) {
        (*(oss[i])) << std::flush;
    }

}

int main(int argc, char * argv[]) {

    if(argc <= 1) {
        std::cout << "Error! No filename specified!" << std::endl;
        return -1;
    }

    std::fstream text_file(argv[1], std::ios_base::in);
    std::string file_name(argv[1]);
    for(int i=file_name.size() - 1; i>=0; --i) {
        if(file_name[i] == '.') {
            file_name = file_name.substr(0, i);
            if(file_name != "")
                file_name = file_name + ".";
            break;
        }
    }
    std::cout << file_name << std::endl;
    


    convert(text_file, file_name);

    return 0;
}
