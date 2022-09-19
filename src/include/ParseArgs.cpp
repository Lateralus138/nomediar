#include "ParseArgs.h"
#include <vector>
#include <iostream>
namespace ParseArgs
{
  void Parse(int argc, const char *argv[], Options &options_, ExitCode &exitcode_)
  {
    options_.isQuiet = false;
    options_.doDelete = false;
    options_.pathStr = ".";
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
            try
            {
              exitcode_.code = 190;
              exitcode_.what = "No switch provided with '--'.";
              throw exitcode_;
            }
            catch (ExitCode &ecode)
            {
              if (!options_.isQuiet)
              {
                std::cerr << ecode.what << '\n';
              }
              std::exit(ecode.code);
            }
          }
          const std::string lower = to_lower(switch_);
          if (lower == "help")
          {
            isHelp = true;
          }
          if (lower == "quiet")
          {
            options_.isQuiet = true;
          }
          if (lower == "delete")
          {
            options_.doDelete = true;
          }
        }
        else if (string_.substr(0, 1) == "-")
        {
          std::string switch_ = string_.substr(1);
          if (switch_.empty())
          {
            try
            {
              exitcode_.code = 191;
              exitcode_.what = "No switch provided with '-'.";
              throw exitcode_;
            }
            catch (ExitCode &ecode)
            {
              if (!options_.isQuiet)
              {
                std::cerr << ecode.what << '\n';
              }
              std::exit(ecode.code);
            }
          }
          const std::string lower = to_lower(switch_);
          if (lower == "h")
          {
            isHelp = true;
          }
          if (lower == "q")
          {
            options_.isQuiet = true;
          }
          if (lower == "d")
          {
            options_.doDelete = true;
          }
        }
        else
        {
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
      }
      if (!newStr.empty())
      {
        options_.pathStr = newStr;
      }
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
};