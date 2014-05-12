Cactus
======

Cactus is a program that generates a .tex and a .pdf file from a Scheme file. It follows some rules for declaring different parts of the document. It treats every line that starts different than ';;;' as verbatim code and some flags that identify the title, authors, description of the source code.

C-Cactus is the exact same program but for C or C++ code, the only difference is that treats '///' as a documentation string instead of ';;;'.

Flags
-----
If the document has no flags, the program will treat everything as source code.

- '*title*' signals the title of the source code.
- '*author*' signals one author of the source code.
- '*about*' signals an about section for the document.
- '*description*' signals a text segment for describing the code.
- '*contract*' signals a contract for a procedure or function (formatted in the style of EOPL).

The text in the doc strings that have flags accept LaTeX formatting code (like $...$ for maths, \textbf{...} for bold text, etc.).

Examples
--------
There is an example of a Scheme source code in the examples directory with the corresponding pdf file generated after running Cactus on it. It is an exercise from SICP.

Contact
-------
You can contact me at eduardo.acye@gmail.com
