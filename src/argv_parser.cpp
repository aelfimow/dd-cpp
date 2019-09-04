#include <sstream>
#include <stdexcept>

#include "argv_parser.h"


argv_parser::argv_parser(int argc, char *argv[]) :
    m_argv { }
{
    for (auto i = 0; i < argc; ++i)
    {
        m_argv.push_back(argv[i]);
    }

    if (m_argv.size() < 5)
    {
        throw std::invalid_argument("Usage: dd-cpp if of bs count");
    }
}

argv_parser::~argv_parser()
{
}

std::string argv_parser::if_name() const
{
    std::string const keyword { "if=" };
    std::string if_name;

    for (auto &str: m_argv)
    {
        auto pos = str.find(keyword);

        bool const found = (pos == 0);

        if (found)
        {
            pos += keyword.length();
            std::string if_name = str.substr(pos);
        }
    }

    return if_name;
}

std::string argv_parser::of_name() const
{
    std::string of_name;
    std::stringstream ss { m_argv[2] };
    ss >> of_name;
    return of_name;
}

size_t argv_parser::bs() const
{
    size_t bs { 0 };
    std::stringstream ss { m_argv[3] };
    ss >> bs;
    return bs;
}

size_t argv_parser::count() const
{
    size_t count { 0 };
    std::stringstream ss { m_argv[4] };
    ss >> count;
    return count;
}
