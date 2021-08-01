#ifndef DEF_INPUT_HPP
#define DEF_INPUT_HPP

#include <stdexcept>
#include <iostream>

template<typename Type>
Type SecureInput() {

    Type result;

    while (!(std::cin >> result)) {

        if (std::cin.eof()) {

            throw std::runtime_error("Error : Flux close");

        } else if (std::cin.fail()) {

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        }

    }

    return result;

}

#endif // DEF_INPUT_HPP