#include "text.hpp"
#include <fstream>
#include <sstream>
#include "../debug/debugmacro.h"
#include "../parse.hpp"


Text::Text(const std::string& resource) {
    debug_println(BIT0, "Constructing text from resource '" << resource << "'...");
    std::string contents = tools::read_resource(resource);
    std::stringstream ss_contents(contents);
    std::getline(ss_contents, text);
    std::getline(ss_contents, subtitle);
    debug_println(BIT0, "Text successfully constructed from resource '" << resource);
}

Text::Text(const std::string& str, const std::string& sub) {
    text = str;
    subtitle = sub;
}

bool Text::is_time_printed() const {
    if (time_print == 0) return false;
    return true;
}

std::string Text::get_text() const {
    return text;
}

std::string Text::get_subtitle() const {
    return subtitle;
}

