// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_IMAGEPASRER_HPP_
#define INCLUDE_IMAGEPASRER_HPP_

#include <Page.hpp>
#include <PageDownloader.hpp>
#include <LinkData.hpp>

#include <boost/asio/thread_pool.hpp>

#include <atomic>
#include <condition_variable>
#include <cstring>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <exception>

class ImgParser {
public:
 explicit ImgParser(const std::string& url, std::size_t depth,
                    std::size_t network_threads, std::size_t parser_threads,
                    const std::string& output);
 void Research();

private:
 void Download(const std::string& downloader, std::size_t depth);
 void Parse(const std::string& data, std::size_t depth);

private:
 boost::asio::thread_pool downloaders, parsers, writer;
 std::ofstream out;
 std::string url;
 std::size_t depth;
 std::condition_variable cond_var;
 bool ready;
 std::atomic_size_t parse_count;
 std::mutex download_mutex;
};

#endif // INCLUDE_IMAGEPASRER_HPP_
