#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "argv_parser.h"


int main(int argc, char *argv[])
try
{
    argv_parser ap { argc, argv };

    auto if_name = ap.if_name();
    auto of_name = ap.of_name();
    auto bs = ap.bs();
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

    for (size_t i = 0; i < count; ++i)
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
    }

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
