// Copyright 2018 Your Name <your_email>

#include <ImageParserData.hpp>

namespace utils {

auto SetupProgramOptions(int  argc, char** argv) -> ImageParserData {
  std::string url, output;
  std::size_t depth, network_threads, parser_threads;
  boost::program_options::options_description desc
      ("Usage: ImageParser <options>\n<options>");
  desc.add_options()
      ("url", boost::program_options::value<std::string>(&url),
          "url to be parsed")
      ("depth", boost::program_options::value<std::size_t>(&depth),
          "depth of a parsing")
      ("network_threads",
                   boost::program_options::value<std::size_t>(&network_threads),
                       "amount of downloaders' threads")
      ("parser_threads",
                       boost::program_options::value<std::size_t>
                           (&parser_threads), "amount of parsers' threads")
      ("output", boost::program_options::value<std::string>(&output),
          "output file");
  boost::program_options::variables_map vm;
  boost::program_options::store(boost::program_options::
                                    parse_command_line(argc, argv, desc),vm);
  boost::program_options::notify(vm);
  if (!(vm.count("url") && vm.count("depth") && vm.count("output"))) {
    std::cout << desc << std::endl;
    exit(1);
  }
  return ImageParserData(url, depth, network_threads, parser_threads, output);
}

}
