// Copyright 2018 Your Name <your_email>

#include <ImageParser.hpp>
#include <ImageParserData.hpp>

int main(int argc, char** argv) {
  auto data = utils::SetupProgramOptions(argc, argv);
  ImgParser parser(data.url, data.depth, data.network_threads,
                   data.parser_threads, data.output);
  parser.Research();
  return 0;
}
