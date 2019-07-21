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
