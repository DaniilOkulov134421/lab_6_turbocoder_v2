#include <iostream>
#include "turbo_coder.h"


int main()
{
    std::vector<Bit_t> input{ 1,0,0,0,1,1,0,1,1,1,0,0,1,0,1,1 };
    std::vector<Bit_t> output;
    TurboEncoder encoder;

    encoder.Encode(input, output);

    std::cout << "Input bits: \n";
    for (auto& bit : input) {
        std::cout << static_cast<unsigned int>(bit);
    }
    std::cout << " : : " << input .size() << std::endl;

    std::cout << "Output bits: \n";
    for (auto& bit : output) {
        std::cout << static_cast<unsigned int>(bit);
    }
    std::cout << " : : " <<  output.size();

    return 0;
}



