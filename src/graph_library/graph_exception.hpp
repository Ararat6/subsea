#ifndef _GRAPH_EXCEPTION_HPP_
#define _GRAPH_EXCEPTION_HPP_

#include <exception>
#include <string>

class graph_exception: public std::exception
{
private:
	std::string m_error_msg;
	int m_line;
public:
	const char* what() throw();
public:
	/**Constructor*/
	graph_exception(const std::string& msg);
	graph_exception(const std::string& msg, int line);
	/**Destructor*/	
	~graph_exception() throw();
};

#endif// _GRAPH_EXCEPTION_HPP_
