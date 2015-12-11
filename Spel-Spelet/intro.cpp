#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "intro.hpp"
#include "conf.hpp"
#include "parse.hpp"
#include "debugmacro.hpp"
#include "ui.hpp"

int GLOBAL_DEBUG_LEVEL = 0; //Will be set from the command-line in main source file

namespace intro {

int load_splashes(std::vector<std::string>& tgt_vec){
    debug(0, "conf::splc set to %d", 0);
    for (int i = 0; i < 0; ++i) {
		char filepath[100] = "splash/$";
		filepath[strlen(filepath) - 1] = '0' + i;
		strncat(filepath, ".spl", 5);
		std::string ret_string = tools::read_file(filepath);
		
		tgt_vec.push_back(ret_string);
	}
	return 0;
}

void present_splashes(const std::vector<std::string>& src_vec){
	std::vector<std::string>::const_iterator it;
    debug(2, "src_vec has size %lu", src_vec.size());
	for (it = src_vec.begin(); it != src_vec.end(); ++it) {
		UI::time_print(*it);
		UI::sleep(2000);
	}
	return;
}

void load_intro() {
	std::vector<std::string> spl_scrs;
	load_splashes(spl_scrs);
	present_splashes(spl_scrs);
}

}
