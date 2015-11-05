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

    modes MODE = UNKNOWN;

    void print(const std::string& text) {
        std::cout << text;
    }
    void println(const std::string& text) {
        std::cout << text << std::endl << "\r";
	}
    std::string** create_str_matrix(int n, int m) {
        std::string** out_ptr = new std::string*[n];
        for (int i = 0; i < n; ++i) {
            *(out_ptr + i) = new std::string[m];
        }
        return out_ptr;
    }

    void deallocate_str_matrix(std::string** out_ptr, int n) {
        for (int i = 0; i < n; ++i) {
            delete[] *(out_ptr + i);
        }
        delete[] out_ptr;
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

    void present_menu(const Menu& menu) {
        unsigned int n = menu.get_size();
        unsigned int m = ITEM_REPR_STR_COUNT;
        std::string** mtx = create_str_matrix(n, m);
        menu.fill_matrix(mtx);
        println(menu.get_name());
        println("-----------------------------");
        //int curs_pos = 0;

        std::string* inner;
        for (unsigned int i = 0; i < n; ++i) {
            inner = *(mtx + i);
            for (unsigned int j = 0; j < m; ++j) {
                print("  " + *(inner + j));
            }
            print("\n\r");
        }
        // How to get a single char.
        char myChar  = {0};


        while (true) {
          std::cout << "Please enter 1 char: ";
          myChar = std::cin.get();

          if (myChar == 's') {
            break;
          }
        }
        std::cout << "You entered: " << myChar << std::endl;
    }

    void set_buffer_mode(int i) {
        if (i == 0) {
            system ("/bin/stty raw");
            MODE = BUFFERED;
        }


        else if (i == 1) {
            system ("/bin/stty cooked");
            MODE = UNBUFFERED;
        }
    }

}
