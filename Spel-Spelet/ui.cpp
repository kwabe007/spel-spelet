#include <string>
#include <iostream>
#include <chrono>
#include <thread> 
#include "ui.hpp"
#include "parse.hpp"
#include "debugmacro.hpp"
#include "canvas.hpp"


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

    Canvas cvs(TERMINAL_COLS, TERMINAL_ROWS);
    modes MODE = UNKNOWN;

    void setup() {
        for (unsigned int i = 0; i < cvs.get_rows(); ++i) {
            std::cout << std::endl << "\r";
        }
    }

    void finished(unsigned int x) {
        for (unsigned int i = 0; i < x; ++i)
        std::cout << ANSI_MOVE_UP;
    }

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
        std::cout << std::endl << "\r";
	}

    void present_menu(const Menu& menu) {
        char choice;


        while (true){
            cvs.apply_menu(menu);
            print_canvas();
            choice = std::cin.get();
            switch(choice){
                case COMMAND_UP:
                    menu.move_up();
                    break; //optional
                case COMMAND_DOWN:
                    menu.move_down();
                    break; //optional
                case COMMAND_ENTER:
                    goto EndWhile;
                    break; //optional
                case COMMAND_RIGHT:
                    goto EndWhile;
                    break; //optional
                default : //Optional
                ;
            }
        }
        EndWhile:
        //std::cout << "choice " << menu.get_selected();
        ;
    }

    void print_canvas() {
        reset_output_marker();
        for (unsigned int i = 0; i < cvs.get_rows(); ++i) {
            std::cout << cvs[i];
            if(i < cvs.get_rows()-1) std::cout << std::endl << "\r";
        }
        std::cout << ANSI_MOVE_UP;
    }

    void reset_output_marker() {
        for (unsigned int i = 0; i < cvs.get_rows(); ++i) {
            std::cout << ANSI_MOVE_UP;
        }
    }

    void set_buffer_mode(int i) {
        if (i == 0) {
            system ("/bin/stty raw -echo");
            MODE = UNBUFFERED;
        }

        else if (i == 1) {
            system ("/bin/stty cooked echo");
            MODE = BUFFERED;
        }
    }

}
