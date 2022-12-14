#include "ParseArgs.h"
#include <vector>
#include <iostream>
#include <fstream>
namespace ParseArgs
{
  void SetDefualtOptions(Options & options_)
  {
    options_.isQuiet = false;
    options_.doDelete = false;
    options_.pathStr = ".";
  }
  void Parse(int argc, const char *argv[], Options &options_, ExitCode &exitcode_)
  {
    SetDefualtOptions(options_);
    if (argc > 1)
    {
      bool isHelp = false;
      std::vector<std::string> args(argv + 1, argv + argc);
      std::string newStr;
      for (std::string &string_ : args)
      {
        if (string_.substr(0, 2) == "--")
        {
          std::string switch_ = string_.substr(2);
          if (switch_.empty())
          {
            exitcode_.code = 190;
            exitcode_.what = "No switch provided with '--'.";
            try_catch_exit(exitcode_, options_.isQuiet);
          }
          const std::string lower = to_lower(switch_);
          isHelp = (lower == "help");
          options_.isQuiet = (lower == "quiet");
          options_.doDelete = (lower == "delete");
          continue;
        }
        if (string_.substr(0, 1) == "-")
        {
          std::string switch_ = string_.substr(1);
          if (switch_.empty())
          {
            exitcode_.code = 191;
            exitcode_.what = "No switch provided with '-'.";
            try_catch_exit(exitcode_, options_.isQuiet);
          }
          const std::string lower = to_lower(switch_);
          isHelp = (lower == "h");
          options_.isQuiet = (lower == "q");
          options_.doDelete = (lower == "d");
          continue;
        }
        if (!newStr.empty())
        {
          newStr.push_back(' ');
        }
        newStr.append(string_);
      }
      if (isHelp)
      {
        // TODO Work on help messsage
        std::cout << "HELP\n";
        std::exit(EXIT_SUCCESS);
      }
      options_.pathStr = (!newStr.empty()?newStr:options_.pathStr);
    }
  }
  std::string to_lower(std::string anyCaseString)
  {
    std::string lower;
    const int stringLength = anyCaseString.length();
    for (int index = 0; index < stringLength; index++)
    {
      lower[index] = tolower(anyCaseString[index]);
    }
    lower[stringLength] = '\0';
    return lower.c_str();
  }
  void try_catch_exit(ExitCode & exitcode_, bool isQuiet)
  {
    try
    {
      exitcode_.code = 190;
      exitcode_.what = "No switch provided with '--'.";
      throw exitcode_;
    }
    catch (ExitCode &ecode)
    {
      if (!isQuiet)
      {
        std::cerr << ecode.what << '\n';
      }
      std::exit(ecode.code);
    }
  }
};
namespace TryNomedia
{
  void try_create_nomedia(const std::filesystem::directory_entry & entry, Options & options)
  {
    try
    {
      if (std::filesystem::is_empty(entry.path()))
      {
        std::filesystem::path temp = entry;
        temp /= ".nomedia";
        std::ofstream tempStream(temp.native());
        if (tempStream.is_open())
        {
          tempStream.close();
          if (!options.isQuiet)
          {
            std::cout << temp << " created successfully." << std::endl;
          }
        }
        else
        {
          if (!options.isQuiet)
          {
            std::cerr << "Could not create " << temp << std::endl;
          }
        }
      }
    }
    catch (std::filesystem::filesystem_error &ferr)
    {
      if (!options.isQuiet)
      {
        std::cerr << "[" << ferr.code().value() << "] " << ferr.what() << '\n';
      }
    }
  }
  void try_delete_nomedia(const std::filesystem::directory_entry & entry, Options & options)
  {
    std::filesystem::path temp = entry;
    try
    {
      if (temp.filename() == ".nomedia")
      {
        try
        {
          std::filesystem::remove(temp);
          if (!options.isQuiet)
          {
            std::cout << temp << " deleted successfully.\n";
          }
        }
        catch (std::filesystem::filesystem_error &ferr)
        {
          if (!options.isQuiet)
          {
            std::cerr << "[" << ferr.code().value() << "] " << ferr.what() << '\n';
          }
        }
      }
    }
    catch (std::filesystem::filesystem_error &ferr)
    {
      if (!options.isQuiet)
      {
        std::cerr << "[" << ferr.code().value() << "] " << ferr.what() << '\n';
      }
    }
  }
};
