#include <string>
#include <iostream>
#include <chrono>
#include <thread> 
#include "ui.hpp"
#include "parse.hpp"
#include "debugmacro.hpp"


#ifdef _WIN32
#include <windows.h>
namespace UI {
void sleep(const std::size_t milliseconds)
{
	Sleep(milliseconds);
}
}
#else
#include <unistd.h>
namespace UI {
void sleep(const std::size_t milliseconds)
{
	usleep(milliseconds * 1000); // takes microseconds
}
}
#endif

namespace UI {
	void print(const std::string& text) {
		std::string out_text = tools::replace_coding(text);
		std::cout << text << std::endl;
	}

	void time_print(const std::string& text, const size_t time) {
		/*std::chrono::milliseconds timespan(10); //No support for thread operations in MinGW :( 
		std::this_thread::sleep_for(timespan);*/
		std::string out_text = tools::replace_coding(text);
		std::string::const_iterator it;
		debug(2, "String to time_print is %s", out_text.c_str());
		for (it = out_text.begin(); it != out_text.end(); ++it) {
			std::cout << *it;
			sleep(time);
		}
		std::cout << std::endl;
	}
}