#ifdef ARGV_PARSER_H
#error Already included
#else
#define ARGV_PARSER_H

#include <vector>
#include <string>

class argv_parser
{
    public:
        explicit argv_parser(int argc, char *argv[]);
        ~argv_parser();

        std::string if_name() const;
        std::string of_name() const;
        size_t bs() const;
        size_t count() const;

    private:
        std::vector<std::string> m_argv;
};

#endif
