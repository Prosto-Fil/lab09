// Copyright 2018 Your Name <your_email>

#include <PageDownloader.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

namespace utils {

PageDownloader::PageDownloader(const std::string& host_new,
                               const std::string& port_new)
    : host{host_new}, port{port_new} {
  sslContext.set_default_verify_paths();
  sslContext.set_verify_mode(ssl::verify_peer);
  tcp::resolver resolver{ioContext};
  if (!SSL_set_tlsext_host_name(stream.native_handle(),
                                host.c_str())) {
    beast::error_code ec{static_cast<int>(ERR_get_error()),
                         net::error::get_ssl_category()};
    throw beast::system_error{ec};
  }
  resolverResults = resolver.resolve(host, port);
}

auto PageDownloader::download(const std::string& target, int httpVersion)
    -> std::string {
  beast::get_lowest_layer(stream).connect(resolverResults);
  stream.handshake(ssl::stream_base::client);

  // set up http get request
  http::request<http::string_body> req{http::verb::get,
                                       target, httpVersion};
  req.set(http::field::host, host);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  http::write(stream, req);

  beast::flat_buffer buffer;

  http::response<http::dynamic_body> response;

  http::read(stream, buffer, response);

  return beast::buffers_to_string(response.body().data());
}

}
