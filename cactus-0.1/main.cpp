#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Reader.hpp"
#include "Transformer.hpp"
#include "Writter.hpp"

void print_welcome_message();
void print_load_success();
void print_save_success();
std::string open_input_by_filename();
std::string open_output_by_filename();

int main()
{
    Reader reader;

    print_welcome_message();

    reader.load_input_file(open_input_by_filename());

    print_load_success();
    
    reader.parse_file();

    Transformer transformer(true,true,true, reader.get_doc_string());

    transformer.load_scheme_structure(reader.get_document_structure());

    transformer.transform_structure();

    Writter writter;

    writter.load_latex_buffer(transformer.get_latex_buffer());

    std::string output_name = open_output_by_filename();
    writter.save_to_file(output_name);

    print_save_success();

    std::string convert = "pdflatex -interaction batchmode ";
    //std::string convert = "pdflatex ";
    convert += output_name;
    
    system(convert.data());

    system("rm *.log *.aux");
    
    return 1;
}

void print_welcome_message()
{
    std::cout << " _____            _             \n";
    std::cout << "/  __ \\          | |            \n";
    std::cout << "| /  \\/ __ _  ___| |_ _   _ ___ \n";
    std::cout << "| |    / _` |/ __| __| | | / __|\n";
    std::cout << "| \\__/\\ (_| | (__| |_| |_| \\__ \\\n";
    std::cout << " \\____/\\__,_|\\___|\\__|\\__,_|___/\n";
    std::cout << "    Scheme src -> LaTex doc \n\n";
}
std::string open_input_by_filename()
{
    std::ifstream input;
    std::string filename;
    bool bad_file = false;
    do{
	std::cout << "[input filename]>";
	std::cin >> filename;
	input.open(filename);
	if(input.fail()){
	    bad_file = true;
	    std::cout << "  ERROR: file doesn't exist" << std::endl;
	}else{
	    bad_file = false;
	}
    }while(bad_file);
    
    return filename;
}
bool overwrite_is_no(std::string str)
{
    return str == "No" or str == "NO" or str == "no"
	or str == "n" or str == "N";
}
bool overwrite_is_yes(std::string str)
{
    return str == "Yes" or str == "YES" or str == "yes"
	or str == "y" or str == "Y";
}
std::string open_output_by_filename()
{
    std::ifstream input;
    std::string filename;
    std::string overwrite;
    bool bad_file;
    do{
	input.close();
	bad_file = false;
	std::cout << "[output filename]>";
	std::cin >> filename;
	input.open(filename);
	if(input.fail()){
	    bad_file = false;
	}else{
	    std::cout << "  ERROR: file already exist" << std::endl;
	    do{
		std::cout << "do you wish to overwrite it? >";
		std::cin >> overwrite;
	    }while(!overwrite_is_no(overwrite) and
		   !overwrite_is_yes(overwrite));
	    if(overwrite_is_yes(overwrite))
		bad_file = false;
	    else
		bad_file = true;
	}
    }while(bad_file);
    
    return filename;
}
void print_load_success()
{
    std::cout << "  DONE: file loaded" << std::endl;
}
void print_save_success()
{
    std::cout << "  DONE: file generated" << std::endl;
}
