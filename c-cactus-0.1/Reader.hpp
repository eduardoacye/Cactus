#ifndef READER_HPP_
#define READER_HPP_

#include <iostream>
#include <fstream>
#include <list>

#include "Cactus.hpp"

class Reader
{
    std::ifstream input_file;

    bool title_exist;
    std::string title;

    bool author_exist;
    std::string author;

    bool about_exist;
    std::string about;

    std::list<CodeSegment> document_structure;

    std::string doc_string = "///";

public:
    Reader();
    ~Reader(){input_file.close();};

    void load_input_file(std::string);
    void parse_file();
    environment check_line_mode(std::string);
    void save_segment(CodeSegment &);
    void clear_segment(CodeSegment &);
    void save_line_in_segment(CodeSegment &, std::string);
    bool starts_doc_string(std::string);
    std::string doc_comment_get_keyword(std::string);
    bool whitespace_only(std::string);

    void print_structure();
    std::list<CodeSegment> get_document_structure();

    std::string get_doc_string(){return doc_string;};
};

#endif	// READER_HPP_
