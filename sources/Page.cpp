// Copyright 2018 Your Name <your_email>

#include <Page.hpp>

Page::Page(const std::string& src) : output(gumbo_parse(src.c_str())) {}

Page::~Page() noexcept {
  gumbo_destroy_output(&kGumboDefaultOptions, output);
}

auto Page::GetLinks(const std::string& attribute, int tag)
    -> std::vector<std::string> {
  std::vector<std::string> result;
  GetLinksImpl(output->root, result, attribute, tag);
  return result;
}

void Page::GetLinksImpl(GumboNode* node, std::vector<std::string>& links,
                        const std::string& attribute, int tag) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }

  GumboAttribute* href;
  if (node->v.element.tag == tag && (href = gumbo_get_attribute
                                     (&node->v.element.attributes,
                                      attribute.c_str()))) {
    links.emplace_back(href->value);
  }

  GumboVector* children = &node->v.element.children;
  for (std::size_t i = 0; i < children->length; ++i) {
    GetLinksImpl(static_cast<GumboNode*>(children->data[i]), links,
                 attribute, tag);
  }
}
