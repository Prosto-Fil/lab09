// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HTTP_DOWNLOADER_HPP_
#define INCLUDE_HTTP_DOWNLOADER_HPP_

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>

#include <string>

namespace utils {

class PageDownloader {
public:
 PageDownloader(const std::string& host_new, const std::string& port_new);
 auto download(const std::string& target, int httpVersion = 11) -> std::string;

private:
 boost::asio::io_context ioContext;
 boost::asio::ssl::context sslContext{boost::asio::ssl::context::tlsv12_client};
 boost::beast::ssl_stream<boost::beast::tcp_stream>
     stream{ioContext, sslContext};
 std::string host, port;
 boost::asio::ip::tcp::resolver::results_type resolverResults;
};

}

#endif // INCLUDE_HTTP_DOWNLOADER_HPP_
