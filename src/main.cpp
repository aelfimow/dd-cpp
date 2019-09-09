#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "argv_parser.h"


static constexpr size_t DefaultBlockSize = 512;


int main(int argc, char *argv[])
try
{
    argv_parser ap { argc, argv };

    auto if_name = ap.if_name();
    auto of_name = ap.of_name().value_or("");
    auto bs = ap.bs().value_or(DefaultBlockSize);
    auto count = ap.count();

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
    size_t bcount { 0 };

    while (bcount < count)
    {
        infile.read(buffer.data(), buffer.size());

        auto const gcount = infile.gcount();

        if (gcount <= 0)
        {
            break;
        }

        size_t bytes_read = static_cast<size_t>(gcount);

        outfile.write(buffer.data(), bytes_read);

        total_bytes += bytes_read;

        if (bytes_read != buffer.size())
        {
            break;
        }

        ++bcount;
    }

    std::cout << "Block size: " << bs << std::endl;
    std::cout << "Block count: " << bcount << std::endl;
    std::cout << "Total bytes: " << total_bytes << std::endl;

    return EXIT_SUCCESS;
}
catch (std::exception &exc)
{
    std::cerr << "Exception: " << exc.what() << std::endl;
    return EXIT_FAILURE;
}
catch (...)
{
    std::cerr << "Error: exception" << std::endl;
    return EXIT_FAILURE;
}
