#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include <stdio.h>
#include "parse.hpp"
#include "conf.hpp"
#include "exceptions/fileexcept.hpp"
#include "entities/human.hpp"
#include "debug/debugmacro.h"
#include "items/weapon.hpp"


namespace tools{

    Parse::Parse(){
		strncpy(esc_seq, "/#@", 10);
		strncpy(end_seq, "/#$", 10);
		esc_seq_len = strlen(esc_seq);
		end_seq_len = strlen(end_seq);
	}
    int Parse::set_esc_seq(const char* seq){
		if (strlen(seq) > 9) {						// the literal int here directly depends on size of esc_seq array
			return 1;
		}
		strncpy(esc_seq, seq, 10);
		esc_seq_len = strlen(esc_seq);
		return 0;
	}

    int Parse::set_end_seq(const char* seq){
		if (strlen(seq) > 9) {						// the literal int here directly depends on size of esc_seq array
			return 1;
		}
		strncpy(end_seq, seq, 10);
		esc_seq_len = strlen(end_seq);
		return 0;
	}

    int Parse::add_value(const std::string key, const std::string value) {
		if (translate.find(key) != translate.end()) return 1;
		translate[key] = value;
		return 0;
	}

    int Parse::remove_value(const std::string key) {
		if (translate.find(key) == translate.end()) return 1;
		translate.erase(key);
		return 0;
	}

    std::string Parse::read_code(const std::string& text, const unsigned int pos)const {
		std::string::iterator it;
		std::string code;
		int end = text.find(end_seq, pos);
		code = text.substr(pos, end - pos);
		return code;
	}

    int Parse::insert_names(std::string& text)const {
		std::string code;					//the code that follows escape sequence
		std::string::iterator it;
		std::string::iterator beg_it;
		std::string::iterator end_it;
		std::string word;					//word

		unsigned int i = 0;
		int count = 0;

		i = text.find(esc_seq);				//i becomes the position of first found string B in string A
		while (i != std::string::npos) {
			++count;
			code = read_code(text, i + esc_seq_len);	//get the code
			word = translate.at(code);
			text.replace(i, esc_seq_len + code.length() + end_seq_len, word);
			i = text.find(esc_seq);
		}
		return count;
	}

    std::string read_resource(const std::string& resource) {
        debug_print(BIT4, "Reading resource '" << resource << "'... ");
        return read_file(CONF.get_path_resource(resource));
    }

    std::string read_file(const std::string& filename) {
        debug_print(BIT4, "Reading file '" << filename << "'... ");
		std::string text;
        std::ifstream file(filename);

        if (!file.good()) {
            throw FileException("File '" + filename + "' not found or is empty");
        }
		else {
            text.assign((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
            file.close();
		}
        debug_println(BIT4, "read complete");
		return text;
	}

    std::string read_line(const std::string& filename) {
        std::string text;
        std::ifstream file(CONF.get_path_resource() + filename);

        if (!file.good()) {
            throw FileException("File '" + filename + "' not found or is empty");
        }
        else {
            std::getline(file,text);
            if (text.back()=='\n')
                text.pop_back();
            file.close();
        }
        return text;
    }

	std::string replace_coding(const std::string& subject) {
		
		size_t pos = 0;
		char letter[2] = " ";
		std::string copy(subject);
		std::string replace;
		while ((pos = copy.find((unsigned char)195, pos)) != std::string::npos) {
			letter[0] = unicode[copy[pos+1]];
			replace = letter;
			copy.replace(pos, 2, replace);
			pos += replace.length();
		}
		return copy;
	}

    void* parse_entity_from_file(const std::string& filename) {
        std::string contents = read_resource(filename);
        std::stringstream ss(contents);
        std::string type;
        std::getline(ss,type);
        Entity* ent;
        if (type == "HMN") {
            ent = new Human(ss);
        } else {
            throw FileException("First token '" + type + "' in entity file '" + filename + "' does not correspond to a known entity type");
        }
        return ent;
    }

    void* parse_item_from_file(const std::string& filename) {
        std::string contents = read_resource(filename);
        std::stringstream ss(contents);
        std::string type;
        std::getline(ss,type);
        Item* item_ptr;
        if (type == "WPN") {
            item_ptr = new Weapon(ss);
        } else {
            throw FileException("First token '" + type + "' in item file '" + filename + "' does not correspond to a known item type");
        }
        return item_ptr;
    }

    int parse_int(const std::string& str) {
        int result = 0;
        try {
            result = std::stoi(str);
        } catch(const std::invalid_argument& e) {
            throw std::invalid_argument("String '" + str + "' is an invalid argument for converting to int");
        } catch(const std::out_of_range& e) {
            throw std::out_of_range("String '" + str + "' gives a value which is out of range when converting to int");
        }
        return result;
    }
}

