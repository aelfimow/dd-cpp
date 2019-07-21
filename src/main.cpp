#include <iostream>
#include <sstream>
#include <stdexcept>


int main(int argc, char *argv[])
try
{
    std::string if_name;
    {
        std::stringstream ss { argv[1] };
        ss >> if_name;
    }

    std::string of_name;
    {
        std::stringstream ss { argv[2] };
        ss >> of_name;
    }

    size_t bs { 0 };
    {
        std::stringstream ss { argv[3] };
        ss >> bs;
    }

    size_t count { 0 };
    {
        std::stringstream ss { argv[4] };
        ss >> count;
    }

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
