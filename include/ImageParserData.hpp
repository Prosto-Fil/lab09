// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_IMAGEPASRERDATA_HPP_
#define INCLUDE_IMAGEPASRERDATA_HPP_

#include <iostream>

#include <boost/program_options.hpp>

namespace utils {

struct ImageParserData {
  std::string url;
  std::size_t depth;
  std::size_t network_threads;
  std::size_t parser_threads;
  std::string output;

  ImageParserData() : depth(0), network_threads(0), parser_threads(0) {}
  ImageParserData(const std::string& url_new, size_t depth_new,
                  size_t network_threads_new, size_t parser_threads_new,
                  const std::string& output_new)
      : url(url_new), depth(depth_new), network_threads(network_threads_new),
        parser_threads(parser_threads_new), output(output_new) {}

};

auto SetupProgramOptions(int  argc, char** argv) -> ImageParserData;

}

#endif // INCLUDE_IMAGEPASRERDATA_HPP_
