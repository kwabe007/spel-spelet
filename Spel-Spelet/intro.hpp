#ifndef INTRO_HPP
#define INTRO_HPP

#include <vector>


namespace intro {
	int load_splashes(std::vector<std::string>& tgt_vec);
	void present_splashes(const std::vector<std::string>& src_vec);
	void load_intro();
}

#endif