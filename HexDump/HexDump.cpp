#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

void dump_row(std::vector<unsigned char>& d, int idx) 
{
    static std::vector<unsigned char> prv{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    static bool peq = false;
    static int neq = 0;
    bool eq = std::equal(d.begin() + idx, d.begin() + idx + 16, prv.begin());
    if (eq) {
        if (peq != eq) {
            std::cout << "*";
            neq = 1;
        }
        else neq++;
        peq = eq;
        return;
    }
    else {
        if (peq != eq) {
            std::cout << " " << std::dec << neq << "\n";
        }
    }
    peq = eq;
    int n = (int)d.size();
    std::cout << std::setw(8) << std::setfill('0') << std::hex << idx << "  ";
    for (int i = 0; i < 16; i++) {
        if (idx + i < n) {
            std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)d[(size_t)idx + i] << " ";
        }
        else {
            std::cout << "   ";
        }
        if (i == 7) std::cout << " ";
    }
    std::cout << " |";
    for (int i = 0; i < 16; i++) {
        if (idx + i < n) {
            auto c = d[(size_t)idx + i];
            if (c < 33) c = '.';
            else if (c > 127) c = '.';
            std::cout << c;
        }
        else {
            std::cout << " ";
        }
    }
    std::cout << "|\n";
    prv.clear();
    prv.resize(16);
    std::copy(d.begin() + idx, d.begin() + idx + 16, prv.begin());
    //std::cout << "prv: " << prv.size() << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "RE Hex Dump 0.1\nSyntax: hexdump file.bin\n";
    }
    else {
        std::ifstream file(argv[1], std::ios::binary);
        std::vector<unsigned char> data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        int i = 0;
        size_t n = data.size();
        while (i < n) {
            dump_row(data, i);
            i += 16;
        }
        // data now contains the contents of the binary file
    }
    return 0;
}
