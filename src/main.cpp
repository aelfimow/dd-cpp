#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "argv_parser.h"


static constexpr size_t DefaultBlockSize = 512;
static constexpr size_t DefaultBlockCount = 1;


int main(int argc, char *argv[])
try
{
    argv_parser ap { argc, argv };

    auto if_name = ap.if_name().value_or("No input file name");
    auto of_name = ap.of_name().value_or("No output file name");
    auto bs = ap.bs().value_or(DefaultBlockSize);
    auto count = ap.count().value_or(DefaultBlockCount);

    std::ifstream infile { if_name, std::ifstream::binary };

    if (!infile.good())
    {
        throw std::runtime_error(if_name + " is not good");
    }

    std::ofstream outfile { of_name, std::ofstream::binary };

    if (!outfile.good())
    {
        throw std::runtime_error(of_name + " is not good");
    }

    std::vector<char> buffer(bs);

    size_t total_bytes { 0 };
    size_t full_blocks_in { 0 };
    size_t partial_blocks_in { 0 };
    size_t full_blocks_out { 0 };
    size_t partial_blocks_out { 0 };

    while ((full_blocks_in + partial_blocks_in) < count)
    {
        infile.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));

        auto const gcount = infile.gcount();

        if (gcount <= 0)
        {
            break;
        }

        size_t const bytes_read = static_cast<size_t>(gcount);
        bool const is_partial = (bytes_read != buffer.size());

        if (is_partial)
        {
            ++partial_blocks_in;
        }
        else
        {
            ++full_blocks_in;
        }

        outfile.write(buffer.data(), static_cast<std::streamsize>(bytes_read));

        if (!outfile.good())
        {
            throw std::runtime_error("Write error on " + of_name);
        }

        if (is_partial)
        {
            ++partial_blocks_out;
        }
        else
        {
            ++full_blocks_out;
        }

        total_bytes += bytes_read;

        if (is_partial)
        {
            break;
        }
    }

    std::cout << full_blocks_in << "+" << partial_blocks_in << " records in\n";
    std::cout << full_blocks_out << "+" << partial_blocks_out << " records out\n";
    std::cout << total_bytes << " bytes copied\n";
    std::cout << "Block size: " << bs << "\n";

    return EXIT_SUCCESS;
}
catch (std::exception &exc)
{
    std::cerr << "Exception: " << exc.what() << "\n";
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "Error: exception\n";
    return EXIT_FAILURE;
}
