#include "Reader.hpp"

Reader::Reader()
{
    // First we initialize the flags for the title author and about
    // This are usefull because the transformer has to put the title
    // and authors before anything else.
    title_exist = false;
    author_exist = false;
    about_exist = false;
}

void Reader::load_input_file(std::string filename)
{
    // Load the file <filename> to the ifstream <input_file>
    input_file.open(filename);
}

void Reader::parse_file()
{
    CodeSegment segment;
    environment current_mode;
    std::string input_line;
    bool first_line = true;

    segment.mode = CODE;
    current_mode;
    while(std::getline(input_file, input_line)){
        // Check the mode of the line
	current_mode = check_line_mode(input_line);
	//std::cout << "   CURRENT MODE = " << current_mode << std::endl;
	if(first_line){
	    segment.mode = current_mode;
	    first_line = false;
	}
	
	// If the mode changed save the segment, clear segment, and assign mode
	if(segment.mode != current_mode and current_mode != SAME){
	    save_segment(segment);
	    clear_segment(segment);
	    segment.mode = current_mode;
	}

	// Save line in segment if is not whitespaces
	if(segment.mode != NONE)
	    save_line_in_segment(segment, input_line);
    }
    
    save_segment(segment);
    clear_segment(segment);
    segment.mode = current_mode;
}

environment Reader::check_line_mode(std::string line)
{
    // The cases are:
    // * Documentation
    // ** contract
    // ** description
    // ** title
    // ** author
    // ** about
    // ** same
    // * Code
    // * Whitespaces only
    if(starts_doc_string(line)){
	
	std::string keyword;
	keyword = doc_comment_get_keyword(line);

	if(keyword == keywords[CONTRACT])
	    return CONTRACT;
	else if(keyword == keywords[DESCRIPTION])
	    return DESCRIPTION;
	else if(keyword == keywords[TITLE])
	    return TITLE;
	else if(keyword == keywords[AUTHOR])
	    return AUTHOR;
	else if(keyword == keywords[ABOUT])
	    return ABOUT;
	else
	    return SAME;
	
    }else if(whitespace_only(line)){
	
	return NONE;
	
    }else{
	
	return CODE;
	
    }
}

void Reader::save_segment(CodeSegment &segment)
{
    if(segment.mode != NONE)
	document_structure.push_back(segment);
}

void Reader::clear_segment(CodeSegment &segment)
{
    segment.mode = NONE;
    segment.content.clear();
}

void Reader::save_line_in_segment(CodeSegment &segment, std::string line)
{
    segment.content.push_back(line);
}

bool Reader::starts_doc_string(std::string line)
{
    return line.substr(0,doc_string.length()) == doc_string;
}

std::string Reader::doc_comment_get_keyword(std::string line)
{
    int start;
    int end;
    bool has_keyword = false;

    start = line.find("*",doc_string.length());
    if(start == std::string::npos){
	return "";
    }else{
	end = line.find("*",start+1);
	if(end == std::string::npos)
	    return "";
	else
	    return line.substr(start, end-start+1);
    }
}

bool Reader::whitespace_only(std::string line)
{
    bool just_whitespace = true;
    for(int i=0; i<line.length(); ++i){
	if(line[i] != '\n' and line[i] != ' ' and line[i] != '\t'){
	    just_whitespace = false;
	}
    }
    return just_whitespace;
}

void print_outer_separator()
{
    std::cout << "= = = = = = = = = = = = = = = = = = = =" << std::endl;
}
void print_inner_separator()
{
    std::cout << "- - - - - - - - - - - - - - - - - - - -" << std::endl;
}
void Reader::print_structure()
{
    if(document_structure.empty()){
        print_outer_separator();
	std::cout << "The structure of the Scheme code is empty" << std::endl;
	print_outer_separator();
    }else{
	std::cout << "  WARNING: The structure of the document will"
		  << " be printed..." << std::endl << std::endl;
        for(std::list<CodeSegment>::iterator i = document_structure.begin();
	    i != document_structure.end(); ++i){
	    print_outer_separator();
	    std::cout << "MODE " << keywords[(*i).mode] << std::endl;
	    print_inner_separator();
	    for(std::list<std::string>::iterator j = (*i).content.begin();
		j != (*i).content.end(); ++j){
		std::cout << *j << std::endl;
	    }
	    print_outer_separator();
	    std::cout << std::endl;
	}
    }
}
std::list<CodeSegment> Reader::get_document_structure()
{
    return document_structure;
}
