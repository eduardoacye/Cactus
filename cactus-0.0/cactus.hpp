// cactus.hpp
//

// This file is part of the cactus program
// 
// Eduardo Acuña Yeomans

// first version

#ifndef CACTUS_HPP_
#define CACTUS_HPP_

#include <iostream>
#include <fstream>

void print_welcome_message();
std::string get_input_filename();

std::string delete_start_comment(std::string);
bool is_line_scm_comment(std::string);
bool is_line_newline(std::string);
#endif	// CACTUS_HPP_
