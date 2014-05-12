#ifndef TRANSFORMER_HPP_
#define TRANSFORMER_HPP_

#include <iostream>
#include <list>

#include "Cactus.hpp"

class Transformer
{
    bool title_exist;
    bool author_exist;
    bool about_exist;
    std::string ignore_string;

    std::list<CodeSegment> scheme_structure;
    std::list<std::string> latex_buffer;

    void transform_title_content(std::list<std::string> &);
    void transform_author_content(std::list<std::string> &);
    void transform_about_content(std::list<std::string> &);
    void transform_contract_content(std::list<std::string> &);
    void transform_description_content(std::list<std::string> &);
    void transform_code_content(std::list<std::string> &);
    void dump_in_buffer(std::list<std::string> &);

public:
    Transformer(bool, bool, bool, std::string);

    void load_scheme_structure(std::list<CodeSegment>);
    void transform_structure();
    void print_buffer();

    std::list<std::string> get_latex_buffer(){return latex_buffer;};
};

#endif	// TRANSFORMER_HPP_
