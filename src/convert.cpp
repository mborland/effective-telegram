//  (C) Copyright Matt Borland 2022.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <include/convert.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <stdexcept>
#include <string_view>
#include <cstddef>
#include <cstdlib>
#include <cstdint>

static constexpr std::array<char, 64> base64_encode_table
{
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
    'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
    'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
    '3', '4', '5', '6', '7', '8', '9', '+', '/'
};

auto hex_to_bytes(const std::string& val) -> std::vector<std::byte>
{
    std::vector<std::byte> data {};
    data.reserve(val.size() / 2);

    for (std::size_t i {}; i < val.size(); i += 2)
    {
        std::string view {val.substr(i, 2)};
        std::byte data_point {static_cast<std::byte>(std::strtol(view.c_str(), nullptr, 16))};
        data.emplace_back(data_point);
    }

    return data;
}

auto bytes_to_base64(std::byte a, std::byte b, std::byte c) -> std::array<char, 4>
{
    constexpr std::uint8_t table_mask {0b0011'1111}; // 0b0011'1111 = 63

    const std::int32_t concat_bits {  (std::to_integer<std::uint8_t>(a) << 16) |
                                      (std::to_integer<std::uint8_t>(b) << 8) |
                                       std::to_integer<std::uint8_t>(c) };

    const auto b64_char1 = base64_encode_table[(concat_bits >> 18) & table_mask];
    const auto b64_char2 = base64_encode_table[(concat_bits >> 12) & table_mask];
    const auto b64_char3 = base64_encode_table[(concat_bits >> 6) & table_mask];
    const auto b64_char4 = base64_encode_table[concat_bits & table_mask];

    return {b64_char1, b64_char2, b64_char3, b64_char4};
}

converter::converter(const std::string& val, int base = 16)
{
    if (base == 16)
    {
        data_ = hex_to_bytes(val);
    }
    else
    {
        throw std::logic_error("Base is not implemented");
    }
}

converter::converter(const char* val, int base = 16)
{
    if (base == 16)
    {
        std::string string_val {val};
        data_ = hex_to_bytes(val);
    }
    else
    {
        throw std::logic_error("Base is not implemented");
    }
}

auto converter::get() const
{
    return data_;
}

auto converter::get_64_output() -> std::string
{
    if (output_val_.empty())
    {
        this->to_64_string();
    }

    return output_val_;
}

auto converter::size() const -> std::size_t
{
    return data_.size();
}

auto converter::to_64_string() -> std::string
{
    for (std::size_t i {}; i < data_.size(); i += 3)
    {
        auto char_array {bytes_to_base64(data_[i], data_[i+1], data_[i+2])};
        output_val_.push_back(char_array[0]);
        output_val_.push_back(char_array[1]);
        output_val_.push_back(char_array[2]);
        output_val_.push_back(char_array[3]);
    }

    return output_val_;
}

auto converter::operator[](std::size_t index) const -> std::byte
{
    return data_.at(index);
}

void converter::operator^(std::byte val)
{
    for (auto& i : data_)
    {
        i ^= val;
    }
}

void converter::xor_len(std::byte val, std::size_t len)
{
    if (len > data_.size())
    {
        throw std::out_of_range("len is longer than the data set");
    }

    for (std::size_t i {}; i < len; ++i)
    {
        data_[i] ^= val;
    }
}
