// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_PAGE_HPP_
#define INCLUDE_PAGE_HPP_

#include <string>
#include <vector>

#include <gumbo.h>

class Page {
public:
 Page(const std::string& src);
 std::vector<std::string> GetLinks(const std::string& attribute, int tag);
 virtual ~Page() noexcept;

private:
 void GetLinksImpl(GumboNode* node, std::vector<std::string>& links,
                   const std::string& attribute, int tag);

private:
 GumboOutput* output;
};

#endif // INCLUDE_PAGE_HPP_
