//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef EFFECTIVE_TELEGRAM_INCLUDE_CONVERT_HPP
#define EFFECTIVE_TELEGRAM_INCLUDE_CONVERT_HPP

#include <cstddef>
#include <vector>
#include <string>

class converter
{
public:
    converter(const std::string& val, int base);
    converter(const char* val, int base);

    auto get() const;
    auto get_64_output() -> std::string;
    auto to_64_string() -> std::string;
    auto size() const -> std::size_t;

private:
    std::vector<std::byte> data_;
    std::string output_val_;
};

#endif // EFFECTIVE_TELEGRAM_INCLUDE_CONVERT_HPP
