// cactus.cpp
// 

// This file is part of the cactus program.
// 
// Eduardo Acuña Yeomans

// first version

#include "cactus.hpp"

std::string tex_first = "\\documentclass[letterpaper, 12pt]{article}\n\n\\usepackage[margin=1in]{geometry}\n\\usepackage[sc]{mathpazo}\n\\usepackage[T1]{fontenc}\n\\usepackage{bm}\n\n\\linespread{1.05}\n\\setlength{\\parindent}{0cm}\n\n\\begin{document}\n\n\n";

std::string tex_end = "\\end{document}\n";

std::string tex_bigskip = "\n\\bigskip\n\n";

std::string tex_begin_verbatim = "\n\\begin{verbatim}\n";

std::string tex_end_verbatim = "\\end{verbatim}\n";

int main()
{
    std::ifstream input_file;
    
    print_welcome_message();

    input_file.open(get_input_filename());
    while(input_file.fail()){
	std::cout << "  ERROR: file doesn't exist" << std::endl;
	input_file.open(get_input_filename());
    }
    std::cout << "  FILE LOADED" << std::endl;

    std::cout << "Cactus will now print the output content" << std::endl;

    std::cout << "-------------------------------------------------" << std::endl;

    bool verbatim_mode = false;
    std::string input_line;

    std::cout << tex_first;
    while(std::getline(input_file, input_line)){
	if(is_line_scm_comment(input_line)){
	    if(verbatim_mode == true){
	        std::cout << tex_end_verbatim;
		verbatim_mode = false;
	    }
	    std::cout << delete_start_comment(input_line) << std::endl;
	}else if(is_line_newline(input_line)){
	    if(verbatim_mode == true){
		std::cout << tex_end_verbatim;
		verbatim_mode = false;
	    }
	    std::cout << tex_bigskip;
	}else{
	    if(verbatim_mode == false){
		std::cout << tex_begin_verbatim;
		verbatim_mode = true;
	    }
	    std::cout << input_line << std::endl;
	}
    }

    if(verbatim_mode == true)
	std::cout << tex_end_verbatim;

    std::cout << tex_end;

    std::cout << "-------------------------------------------------" << std::endl;
    return 0;
}

// Front end
void print_welcome_message()
{
    std::cout << "Cactus version 1" << std::endl;
}

std::string get_input_filename()
{
    std::string filename;
    std::cout << "[input filename]>";
    std::cin >> filename;
    return filename;
}

// Back end
std::string delete_start_comment(std::string line)
{
    int i;
    for(i=0; i<line.length(); ++i){
	if(line[i] != ';' and line[i] != ' ')
	    break;
    }
    return line.erase(0,i);	    
}

bool is_line_scm_comment(std::string line)
{
    char c;
    for(int i=0; i<line.length(); ++i){
	c = line[i];
	if(c == ';')
	    return true;
	if(c != ' ')
	    return false;
    }
    return false;
}

bool is_line_newline(std::string line)
{
    return line.empty();
}
