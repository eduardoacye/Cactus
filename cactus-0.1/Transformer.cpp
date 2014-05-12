#include "Transformer.hpp"

Transformer::Transformer(bool has_title, bool has_author, bool has_about,
			 std::string doc_string)
{
    title_exist = has_title;
    author_exist = has_author;
    about_exist = has_about;
    ignore_string = doc_string += " ";
}

void Transformer::load_scheme_structure(std::list<CodeSegment> structure)
{
    scheme_structure = structure;
}
void Transformer::transform_structure()
{
    std::cout << "  WARNING: Entering compilation step"
	      << std::endl;
    // Apply rules of transformation for each segment in order and push
    // the strings of the transformed content into the latex_buffer.
    environment mode;
    for(std::list<CodeSegment>::iterator i = scheme_structure.begin();
	i != scheme_structure.end(); ++i){
	mode = (*i).mode;
	switch(mode){
	case TITLE:
	    //std::cout << "FOUND title" << std::endl;
	    transform_title_content((*i).content);
	    break;
	case AUTHOR:
	    //std::cout << "FOUND author" << std::endl;
	    transform_author_content((*i).content);
	    break;
	case ABOUT:
	    //std::cout << "FOUND about" << std::endl;
	    transform_about_content((*i).content);
	    break;
	case CONTRACT:
	    //std::cout << "FOUND contract" << std::endl;
	    transform_contract_content((*i).content);
	    break;
	case DESCRIPTION:
	    //std::cout << "FOUND description" << std::endl;
	    transform_description_content((*i).content);
	    break;
	case CODE:
	    //std::cout << "FOUND code" << std::endl;
	    transform_code_content((*i).content);
	    break;
	default:
	    std::cout << "  ERROR: This mode isn't found (MODE " << mode
		      << ")" << std::endl;
	    break;
	}
	dump_in_buffer((*i).content);
    }
    std::cout << "  DONE: file compiled" << std::endl;
    //print_buffer();
}
void Transformer::transform_title_content(std::list<std::string> &content)
{
    int index;
    // each line of the content starts with <ignore_string> and the first
    // line has a *title* keyword in it.

    // The ignore_string should be removed
    // as well as the keyword
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	// erase <ignore_string>
	(*i).erase(0, ignore_string.length());
	index = (*i).find(keywords[TITLE]);
	if(index != std::string::npos)
	    (*i).erase(index, keywords[TITLE].length()+1);
    }

    // Put the latex format in each line
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	(*i).insert(0, "\\hfill {\\LARGE \\textbf{");
	(*i).insert((*i).length(), "} }\n");
    }
    content.push_back("\\bigskip\n\n");
    /*
    std::cout << "  BEGIN TITLE CONTENT..." << std::endl;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	std::cout << *i << std::endl;
    }
    std::cout << "  END TITLE CONTENT..." << std::endl;
    */
}

void Transformer::transform_author_content(std::list<std::string> &content)
{
    int index;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	// erase <ignore_string>
	(*i).erase(0, ignore_string.length());
	index = (*i).find(keywords[AUTHOR]);
	if(index != std::string::npos)
	    (*i).erase(index, keywords[AUTHOR].length()+1);
    }

    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	(*i).insert(0, "\\hfill {\\large \\textbf{");
	(*i).insert((*i).length(), "} }\n");
    }
    content.push_back("\\bigskip\n\n");
    /*
    std::cout << "  BEGIN AUTHOR CONTENT..." << std::endl;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	std::cout << *i << std::endl;
    }
    std::cout << "  END AUTHOR CONTENT..." << std::endl;
    */
}

void Transformer::transform_about_content(std::list<std::string> &content)
{
    int index;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	// erase <ignore_string>
	(*i).erase(0, ignore_string.length());
	index = (*i).find(keywords[ABOUT]);
	if(index != std::string::npos)
	    (*i).erase(index, keywords[ABOUT].length()+1);
    }

    content.push_front("\\bigskip\n");
    content.push_back("\n\\bigskip\n\n");
    /*
    std::cout << "  BEGIN ABOUT CONTENT..." << std::endl;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	std::cout << *i << std::endl;
    }
    std::cout << "  END ABOUT CONTENT..." << std::endl;
    */
}

void Transformer::transform_contract_content(std::list<std::string> &content)
{
    int index;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	// erase <ignore_string>
	(*i).erase(0, ignore_string.length());
	index = (*i).find(keywords[CONTRACT]);
	if(index != std::string::npos)
	    (*i).erase(index, keywords[CONTRACT].length()+1);
    }

    
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	(*i).insert(0, "\\textbf{");
	index = (*i).find(":");
	(*i).insert(index+1, "}");

	index += 3;

	int arrow_start;
	int comma_start;
	int not_space_start;

	arrow_start = (*i).find_first_of("->", index);
	comma_start = (*i).find_first_of(",", index);
	not_space_start = (*i).find_first_not_of(" ", index);
	while(not_space_start != std::string::npos and
	      index < (*i).length()){
	    //std::cout << "  string is : " << (*i) << std::endl;
	    //std::cout << "  index = " << index << std::endl;
	    //std::cout << "  arrow_start = " << arrow_start << std::endl;
	    //std::cout << "  comma_start = " << comma_start << std::endl;
	    //std::cout << "  not_space_start = " << not_space_start
	    //<< std::endl << std::endl;
	    //std::cin.get();
	    
	    if(not_space_start != comma_start and
	       not_space_start != arrow_start){
		// a string was found at not_space_start
		(*i).insert(not_space_start, "\\emph{");
		index = (*i).find_first_of(" ", not_space_start);
	        if(index != std::string::npos){
		    (*i).insert(index, "}");
		    index++;
		}
	    }else{
		if(not_space_start == comma_start){
		    (*i).replace(comma_start, 1, "$\\times$");
		    index += 9;
		}else if(not_space_start == arrow_start){
		    (*i).replace(arrow_start, 2,
				 "$\\boldsymbol{\\rightarrow}$");
		    index += 27;
		}
	    }
	    arrow_start = (*i).find_first_of("->", index);
	    comma_start = (*i).find_first_of(",", index);
	    not_space_start = (*i).find_first_not_of(" ", index);
	}
	(*i).insert((*i).length(),"}");
	//std::cout << "final : " << (*i) << std::endl<<std::endl;
    }

    content.push_front("\\bigskip\n\n\\bigskip\n");
    /*
    std::cout << "  BEGIN CONTRACT CONTENT..." << std::endl;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	std::cout << *i << std::endl;
    }
    std::cout << "  END CONTRACT CONTENT..." << std::endl;
    */
}

void Transformer::transform_description_content(std::list<std::string> &content)
{
    int index;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	// erase <ignore_string>
	(*i).erase(0, ignore_string.length());
	index = (*i).find(keywords[DESCRIPTION]);
	if(index != std::string::npos)
	    (*i).erase(index, keywords[DESCRIPTION].length()+1);
    }
    content.push_front("\n");
    /*
    std::cout << "  BEGIN DESCRIPTION CONTENT..." << std::endl;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	std::cout << *i << std::endl;
    }
    std::cout << "  END DESCRIPTION CONTENT..." << std::endl;
    */
}

void Transformer::transform_code_content(std::list<std::string> &content)
{
    content.push_front("\\begin{verbatim}");
    content.push_back("\\end{verbatim}\n\n");

    /*
    std::cout << "  BEGIN CODE CONTENT..." << std::endl;
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	std::cout << *i << std::endl;
    }
    std::cout << "  END CODE CONTENT..." << std::endl;
    */
}

void Transformer::dump_in_buffer(std::list<std::string> & content)
{
    for(std::list<std::string>::iterator i = content.begin();
	i != content.end(); ++i){
	latex_buffer.push_back(*i);
    }
}

void Transformer::print_buffer()
{
    std::cout << "  WARNING: The latex buffer will be printed" << std::endl;
    std::cout << "===========================================" << std::endl;
    for(std::list<std::string>::iterator i = latex_buffer.begin();
	i != latex_buffer.end(); ++i){
	std::cout << *i << std::endl;
    }
    std::cout << "===========================================" << std::endl;
}
