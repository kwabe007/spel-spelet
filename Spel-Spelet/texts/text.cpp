#include "text.hpp"
#include <fstream>

Text::Text(const std::string& filename) {
    std::ifstream fs_text(filename);
    text.assign((std::istreambuf_iterator<char>(fs_text)),
                    (std::istreambuf_iterator<char>())); // This should not give error due to most vexing parse
}

bool Text::is_time_printed() const {
    if (time_print == 0) return false;
    return true;
}

std::string Text::get_text() const {
    return text;
}
