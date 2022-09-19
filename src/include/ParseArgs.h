#pragma once
#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <filesystem>
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
  extern void try_catch_exit(ExitCode &exitcode_, bool isQuiet);
};
namespace TryNomedia
{
  extern void try_create_nomedia(const std::filesystem::directory_entry &entry, Options &options);
  extern void try_delete_nomedia(const std::filesystem::directory_entry &entry, Options &options);
};
#endif
