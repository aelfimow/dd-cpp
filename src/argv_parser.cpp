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
            if_name = str.substr(pos);
            break;
        }
    }

    return if_name;
}

std::string argv_parser::of_name() const
{
    std::string const keyword { "of=" };
    std::string of_name;

    for (auto &str: m_argv)
    {
        auto pos = str.find(keyword);

        bool const found = (pos == 0);

        if (found)
        {
            pos += keyword.length();
            of_name = str.substr(pos);
            break;
        }
    }

    return of_name;
}

size_t argv_parser::bs() const
{
    std::string const keyword { "bs=" };
    std::string bs_str;

    for (auto &str: m_argv)
    {
        auto pos = str.find(keyword);

        bool const found = (pos == 0);

        if (found)
        {
            pos += keyword.length();
            bs_str = str.substr(pos);
            break;
        }
    }

    size_t bs { 0 };
    std::stringstream ss { bs_str };
    ss >> bs;

    return bs;
}

size_t argv_parser::count() const
{
    std::string const keyword { "count=" };
    std::string count_str;

    for (auto &str: m_argv)
    {
        auto pos = str.find(keyword);

        bool const found = (pos == 0);

        if (found)
        {
            pos += keyword.length();
            count_str = str.substr(pos);
            break;
        }
    }

    size_t count { 0 };
    std::stringstream ss { count_str };
    ss >> count;

    return count;
}
