#ifndef TEXT_HPP
#define TEXT_HPP
#include <string>

enum PrintPattern {
    PRINT_PATTERN_LTR_TTB,
    PRINT_PATTERN_LTR_TAB
};

class Text {

private:
    std::string text = "none";
    std::string subtitle = "nosub";
    unsigned int time_print = 0;

public:
    Text();
    Text(const std::string& filename);
    bool is_time_printed() const;
    std::string get_text() const;



};

#endif
