#ifndef CACTUS_HPP_
#define CACTUS_HPP_

enum environment {CONTRACT,	// a $contract$ keyword marked in the segment
		  DESCRIPTION,	// a $description$ keyword marked in the segment
		  TITLE,	// a $title$ keyword marked in the segment
		  AUTHOR,	// a $author$ keyword marked in the segment
		  ABOUT,	// a $about$ keyword marked in the segment
		  CODE,		// code segment (not empty and not ;;; comment)
		  NONE,		// empty or whitespace with newline
		  SAME};	// same environment than before

struct CodeSegment
{
    environment mode;
    std::list<std::string> content;
};

static std::string keywords[8] = {"*contract*", "*description*",
				  "*title*", "*author*",
				  "*about*", "*code*",
				  "*none*", "*same*"};

#endif	// CACTUS_HPP_
