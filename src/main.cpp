#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "argv_parser.h"

static constexpr size_t DefaultBlockSize = 512;
static constexpr size_t DefaultBlockCount = 1;

int main(int argc, char *argv[])
try
{
    argv_parser ap { argc, argv };

    auto const opt_if = ap.if_name();
    if (!opt_if)
    {
        throw std::runtime_error("Missing required input file (if=<path>)");
    }

    auto const opt_of = ap.of_name();
    if (!opt_of)
    {
        throw std::runtime_error("Missing required output file (of=<path>)");
    }

    std::string const if_name { *opt_if };
    std::string const of_name { *opt_of };
    auto const bs = ap.bs().value_or(DefaultBlockSize);
    auto const count = ap.count().value_or(DefaultBlockCount);

    std::ifstream infile { if_name, std::ifstream::binary };
    if (!infile.good())
    {
        throw std::runtime_error("Failed to open input file: " + if_name);
    }

    std::ofstream outfile { of_name, std::ofstream::binary };
    if (!outfile.good())
    {
        throw std::runtime_error("Failed to open output file: " + of_name);
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

        partial_blocks_in += is_partial ? 1 : 0;
        full_blocks_in += is_partial ? 0 : 1;

        outfile.write(buffer.data(), static_cast<std::streamsize>(bytes_read));
        if (!outfile.good())
        {
            throw std::runtime_error("Write error on output file: " + of_name);
        }

        partial_blocks_out += is_partial ? 1 : 0;
        full_blocks_out += is_partial ? 0 : 1;

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
catch (std::exception const &exc)
{
    std::cerr << "Exception: " << exc.what() << "\n";
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "Error: unknown exception\n";
    return EXIT_FAILURE;
}
