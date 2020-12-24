// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_LINKDATA_HPP_
#define INCLUDE_LINKDATA_HPP_

#include <iostream>
#include <string>

namespace utils {

  struct LinkData {
    std::string host;
    std::string target;
  };

auto DivideIntoHostAndTarget(const std::string& url) -> LinkData;

}

#endif // INCLUDE_LINKDATA_HPP_
