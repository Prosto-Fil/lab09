// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <LinkData.hpp>
#include <Page.hpp>

TEST(LinkData, DivideIntoHostAndTarget) {
  auto data1 = utils::DivideIntoHostAndTarget
      ("https://github.com/Prosto-Fil/");
  EXPECT_EQ(data1.host, "github.com");
  EXPECT_EQ(data1.target, "/Prosto-Fil/");

  auto data2 = utils::DivideIntoHostAndTarget("https://github.com/");
  EXPECT_EQ(data2.host, "github.com");
  EXPECT_EQ(data2.target, "/");

  auto data3 = utils::DivideIntoHostAndTarget
      ("http://ebooks.bmstu.ru/catalog/197/page1.html");
  EXPECT_EQ(data3.host, "ebooks.bmstu.ru");
  EXPECT_EQ(data3.target, "/catalog/197/page1.html");

  auto data4 = utils::DivideIntoHostAndTarget("http://ebooks.bmstu.ru/");
  EXPECT_EQ(data4.host, "ebooks.bmstu.ru");
  EXPECT_EQ(data4.target, "/");
}

TEST(Page, GetLinks) {
  Page page{"<p><img src=\"https://site.with.images.net/documents"
            "/171120/pub_5hy543u5h238g346g88g5hj7_5hy56g53gj457j5hf5h45gd4/"
            "scale_600\" alt=\"\" width=\"1200\" height=\"675\" /></p>"};
  auto links = page.GetLinks("src", GUMBO_TAG_IMG);
  std::vector<std::string> expected = { "https://site.with.images.net"
                               "/documents/171120/pub_5hy543u5h238g346g88g5hj7"
                               "_5hy56g53gj457j5hf5h45gd4/scale_600" };
  EXPECT_FALSE(links.empty());
  EXPECT_TRUE(std::equal(links.begin(), links.end(), expected.begin()));
}
