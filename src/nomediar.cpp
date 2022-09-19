// -----------------------------------------------
// 'nomediar' - recursively create .nomedia files
// in empty directories.
// Copyright © 2022
// Ian Pride @ New Pride Software/Services
// Sun 18 Sep 2022 19:12:00 CST
// -----------------------------------------------
#include <iostream>
#include <filesystem>
#include <fstream>
#include "ParseArgs.h"
int main(int argc, const char *argv[])
{
  // TODO Parse arguments, finish HELP message
  Options options;
  ExitCode exitcode;
  ParseArgs::Parse(argc, argv, options, exitcode);
  try
  {
    for (const auto &entry : std::filesystem::recursive_directory_iterator(options.pathStr))
    {
      if (!options.doDelete)
      {
        try
        {
          if (entry.is_directory())
          {
            TryNomedia::try_create_nomedia(entry, options);
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
      else
      {
        try
        {
          if (entry.is_regular_file())
          {
            try
            {
              if (std::filesystem::is_empty(entry.path()))
              {
                TryNomedia::try_delete_nomedia(entry, options);
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
    }
  }
  catch (std::filesystem::filesystem_error &ferr)
  {
    if (!options.isQuiet)
    {
      std::cerr << "[" << ferr.code().value() << "] " << ferr.what() << '\n';
    }
  }
  return EXIT_SUCCESS;
}