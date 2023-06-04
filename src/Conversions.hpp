#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include <array>

class Conversions {
    public : 
    static std::string char_arr_to_string(std::array<char, 256> in) {
        std::cout << "CONVERT" << std::endl << std::endl;
        std::string str;
        for (int i = 0; i < in.size(); i++) {
            if (in[i] != 0) { //TODO: this is wrong, UTF fuckeries
                str.push_back(in[i]);
            }
        }
        std::cout << std::endl << "String for init: " << str << std::endl;
        return str; 
    }

};


#endif
