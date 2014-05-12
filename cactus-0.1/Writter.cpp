#include "Writter.hpp"

Writter::Writter()
{
    begin_tex = "\\documentclass[letterpaper, 12pt]{article}\n\n\\usepackage[spanish]{babel}\n\\usepackage[utf8]{inputenc}\n\n\\usepackage[margin=1in]{geometry}\n\\usepackage[sc]{mathpazo}\n\\usepackage[T1]{fontenc}\n\\usepackage{bm}\n\n\\linespread{1.05}\n\\setlength{\\parindent}{0cm}\n\n\\begin{document}\n\n";

    end_tex = "\n\n\\end{document}";
}

void Writter::load_latex_buffer(std::list<std::string> buffer)
{
    latex_buffer = buffer;
}

void Writter::save_to_file(std::string file_name)
{
    output_file.open(file_name);
    output_file << begin_tex;
    for(std::list<std::string>::iterator i = latex_buffer.begin();
	i != latex_buffer.end(); ++i){
	output_file << *i << std::endl;
    }
    output_file << end_tex;
    output_file.close();
}

