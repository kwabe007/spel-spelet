#ifndef UI_HPP
#define UI_HPP

#include <string>

/*Class for*/
namespace UI  {
	
	void sleep(const std::size_t milliseconds);

	/*Prints input string (text)*/
	void print(const std::string& text);

	/*Prints input string (text) with delay (time) between the characters; delay is in milliseconds.
	If time is not specified, it defaults to 10*/
	void time_print(const std::string& text, const size_t = 10);


	//show_menu();
};

#endif // !UI_HPP
