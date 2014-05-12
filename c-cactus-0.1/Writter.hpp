#ifndef WRITTER_HPP_
#define WRITTER_HPP_

#include <iostream>
#include <fstream>
#include <list>

class Writter
{
    std::ofstream output_file;

    std::list<std::string> latex_buffer;

    std::string begin_tex;
    std::string end_tex;

public:
    Writter();
    ~Writter(){output_file.close();};

    void load_latex_buffer(std::list<std::string>);
    void save_to_file(std::string);
};

#endif	// WRITTER_HPP_
