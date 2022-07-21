//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <iostream>
#include "../include/convert.hpp"

int main(void)
{
    const std::string test_val {"49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"};
    const std::string result {"SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"};

    converter hex_to_64 (test_val, 16);

    if (hex_to_64.get_64_output() == result)
    {
        std::cout << "Correct\n";
    }
    else
    {
        std::cout << "Incorrect\n";
        std::cout << hex_to_64.get_64_output() << "\n";
        std::cout << "size: " << hex_to_64.size() << '\n';
    }

    return 0;
}
