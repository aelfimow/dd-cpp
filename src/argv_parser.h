#ifdef ARGV_PARSER_H
#error Already included
#else
#define ARGV_PARSER_H

#include <list>
#include <string>

class argv_parser
{
    public:
        explicit argv_parser(int argc, char *argv[]);
        ~argv_parser();

    private:
        std::list<std::string> m_argv;
};

#endif
