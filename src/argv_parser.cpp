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

std::optional<std::string> argv_parser::if_name() const
try
{
    return parse("if=");
}
catch (...)
{
    return std::nullopt;
}

std::optional<std::string> argv_parser::of_name() const
try
{
    return parse("of=");
}
catch (...)
{
    return std::nullopt;
}

std::optional<size_t> argv_parser::bs() const
try
{
    std::string bs_str = parse("bs=");

    size_t value { 0 };
    std::stringstream ss { bs_str };
    ss >> value;

    if (value == 0)
    {
        return std::nullopt;
    }

    return value;
}
catch (...)
{
    return std::nullopt;
}

size_t argv_parser::count() const
{
    std::string bs_str = parse("count=");
    size_t value { 0 };
    std::stringstream ss { bs_str };
    ss >> value;
    return value;
}

std::string argv_parser::parse(std::string const &keyword) const
{
    std::string parsed_str;

    for (auto const &str: m_argv)
    {
        auto pos = str.find(keyword);

        bool const found = (pos == 0);

        if (found)
        {
            pos += keyword.length();
            parsed_str = str.substr(pos);
            break;
        }
    }

    return parsed_str;
}
