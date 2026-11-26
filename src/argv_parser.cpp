#include "argv_parser.h"

#include <charconv>
#include <system_error>

argv_parser::argv_parser(int argc, char *argv[])
    : m_argv {}
{
    if (argc > 0 && argv != nullptr)
    {
        m_argv.reserve(static_cast<size_t>(argc));
        for (int i = 0; i < argc; ++i)
        {
            if (argv[i] != nullptr)
            {
                m_argv.emplace_back(argv[i]);
            }
        }
    }
}

std::optional<std::string_view> argv_parser::if_name() const
{
    return parse("if=");
}

std::optional<std::string_view> argv_parser::of_name() const
{
    return parse("of=");
}

std::optional<size_t> argv_parser::bs() const
{
    auto const val = parse("bs=");
    if (!val)
    {
        return std::nullopt;
    }
    return parse_positive_size(*val);
}

std::optional<size_t> argv_parser::count() const
{
    auto const val = parse("count=");
    if (!val)
    {
        return std::nullopt;
    }
    return parse_positive_size(*val);
}

std::optional<std::string_view> argv_parser::parse(std::string_view keyword) const
{
    for (auto const &arg : m_argv)
    {
        std::string_view sv { arg };
        if (sv.substr(0, keyword.size()) == keyword)
        {
            auto const value = sv.substr(keyword.size());
            if (!value.empty())
            {
                return value;
            }
            return std::nullopt;
        }
    }

    return std::nullopt;
}

std::optional<size_t> argv_parser::parse_positive_size(std::string_view sv)
{
    if (sv.empty())
    {
        return std::nullopt;
    }

    size_t value { 0 };
    auto const [ptr, ec] = std::from_chars(sv.data(), sv.data() + sv.size(), value);

    if (ec != std::errc{} || ptr != sv.data() + sv.size() || value == 0)
    {
        return std::nullopt;
    }

    return value;
}
