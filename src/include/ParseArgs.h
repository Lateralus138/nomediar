#pragma once
#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <string>
struct Options
{
  bool isQuiet;
  bool doDelete;
  std::string pathStr;
};
struct ExitCode
{
  int code;
  std::string what;
};

namespace ParseArgs
{
  extern void Parse(int argc, const char *argv[], Options &options_, ExitCode & exitcode_);
  extern std::string to_lower(std::string anyCaseString);
};
#endif
