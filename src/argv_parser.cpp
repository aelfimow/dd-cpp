#include "argv_parser.h"

argv_parser::argv_parser(int argc, char *argv[]) :
    m_argv { }
{
    for (auto i = 0; i < argc; ++i)
    {
        m_argv.push_back(argv[i]);
    }
}

argv_parser::~argv_parser()
{
}
