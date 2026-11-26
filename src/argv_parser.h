#ifdef ARGV_PARSER_H
#error Already included
#else
#define ARGV_PARSER_H

#include <cstddef>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

class argv_parser
{
    public:
        explicit argv_parser(int argc, char *argv[]);
        ~argv_parser() = default;

        std::optional<std::string_view> if_name() const;
        std::optional<std::string_view> of_name() const;
        std::optional<size_t> bs() const;
        std::optional<size_t> count() const;

    private:
        std::vector<std::string> m_argv;

        std::optional<std::string_view> parse(std::string_view keyword) const;
        static std::optional<size_t> parse_positive_size(std::string_view sv);
};

#endif
