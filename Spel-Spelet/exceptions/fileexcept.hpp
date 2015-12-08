#ifndef FILEEXCEPT_HPP
#define FILEEXCEPT_HPP

#include <string>
#include <stdexcept>

class FileException : public std::runtime_error
{
  public:
    FileException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif
