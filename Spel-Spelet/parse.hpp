#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>
#include <map>
#include <iostream>

namespace tools {
	class Parse{
	private:
		char esc_seq[10];
		char end_seq[10];
		int esc_seq_len;
		int end_seq_len;

		std::map<std::string, std::string> translate;

	public:

		Parse();

		int set_esc_seq(const char* seq);

		int set_end_seq(const char* seq);

		int add_value(const std::string key, const std::string value);

		int remove_value(const std::string key);

		std::string read_code(const std::string& text, const unsigned int pos)const;

		/*Parses input string for predefined escape characters and replaces such characters with a string of choice*/
		int insert_names(std::string& text)const;
	};

    std::string read_resource(const std::string& resource);
	
    std::string read_file(const std::string& filename);

    std::string read_line(const std::string& filename);

	std::string replace_coding(const std::string& subject);

    void* parse_entity_from_file(const std::string& filename);

    int parse_int(const std::string& str);

	static std::map<char, char> unicode{
			{ 133, 143 },
			{ 132, 142 },
			{ 150, 153 },
			{ 165, 134 },
			{ 164, 132 },
			{ 182, 148 },
	};
}
#endif
