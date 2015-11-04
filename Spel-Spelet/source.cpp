#include <string>
#include <iostream>
#include <stdlib.h>
#include "conf.hpp"
#include "parse.hpp"
#include "intro.hpp"
#include "debugmacro.hpp"

void fix_parser(tools::Parse& parser) {
	std::string name1("PLAYER_NAME");
	std::string name2("FRIEND_NAME1");
	std::string name3("FRIEND_NAME2");
	std::string val1("Bo");
	std::string val2("PundarJockepppppppppp");
	std::string val3("Stpskot");
	parser.add_value(name1, val1);
	parser.add_value(name2, val2);
	parser.add_value(name3, val3);
}


int main(int argc, char* argv[]) {
	if (argc == 2) GLOBAL_DEBUG_LEVEL = strtol(argv[1],argv,10);
	log_info("GLOBAL_DEBUG_LEVEL set to %d", GLOBAL_DEBUG_LEVEL);

	tools::Parse parser;
	intro::load_intro();
	fix_parser(parser);

	std::string text("Ditt namn är /#@PLAYER_NAME/#$. Du saknar jobb, pengar och har typ ingen framtid. Du bor tillsammans med dina två s.k. 'vänner' /#@FRIEND_NAME1/#$ och /#@FRIEND_NAME2/#$ i en");
	parser.insert_names(text);
	printf("Press any key to exit");
	getchar();


}
