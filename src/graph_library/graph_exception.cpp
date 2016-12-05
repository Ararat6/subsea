#include "graph_exception.hpp"
#include "sstream"

const char* graph_exception::what() throw()
{
	std::string error_line = "";
	if (0 != m_line) {
		std::stringstream ss;
		ss << m_line;
		error_line = "\ninput file:";
		error_line += ss.str();
	}
	std::string text_color = ":\033[1;31merror: \033[0m";
	std::string temp = error_line + text_color + m_error_msg;	
	return temp.c_str();
}

graph_exception::graph_exception(const std::string& msg)
	:m_error_msg(msg)
	 ,m_line(0)
{}


graph_exception::graph_exception(const std::string& msg, int line)
	:m_error_msg(msg)
	 ,m_line(line)
{}

graph_exception::~graph_exception() throw()
{}
