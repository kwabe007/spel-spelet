#ifndef my_stripper_h
#define my_stripper_h

#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::ostream;

template <class T>
class Stripper {
public:
    stringstream stripped;
    const Stripper & operator<<(const lab2::Calendar<T> & cal) {
        stringstream ss;
        ss << "STRIPPER" << endl;
        ss << cal;
        string row;
        while (getline(ss, row)) {
            std::size_t found = row.find("DTSTART:");
            if (found == 0) {
                found = row.find("T", 7);
                if (found != string::npos) {  // T in DTSTART:991212T180001
                    stripped << row.substr(found - 6, 6) << endl;
                } else {                      // use last 6
                    stripped << row.substr(row.size()-6, 6) << endl;
                }
            }
            if (row.find("SUMMARY:") == 0 && row.size() > 8) {
                stripped << row.substr(8, row.size()) << endl;
            }
            if (row.find("DESCRIPTION:") == 0 && row.size() > 12)
                stripped << row.substr(12, row.size()) << endl;
        }
        return *this;
    }
};

template <class T>
ostream & operator<<(ostream & os, const Stripper<T>& s)
{
    os << s.stripped.str();
    return os;
}
#endif
