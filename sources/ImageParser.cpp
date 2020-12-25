// Copyright 2018 Your Name <your_email>

#include <ImageParser.hpp>

ImgParser::ImgParser(const std::string& url_new, std::size_t depth_new,
                     std::size_t network_threads_new,
                     std::size_t parser_threads_new,
                     const std::string& output_new)
    : downloaders{network_threads_new}, parsers{parser_threads_new}, writer{1},
      out{output_new}, url{url_new}, depth{depth_new},
      ready{false}, parse_count{0} {}

void ImgParser::Research() {
  boost::asio::post(downloaders,[this, capture0 = std::cref(url)]
                    { Download(capture0, depth); });
  std::unique_lock<std::mutex> lock(download_mutex);
  cond_var.wait(lock, [this]() { return ready; });
  parsers.join();
  writer.join();
  std::cout << "Successfully downloaded" << std::endl;
}

void ImgParser::Download(const std::string& url_new, std::size_t depth_new) {
  try {
    if (depth) {
      auto data = utils::DivideIntoHostAndTarget(url_new);
      utils::PageDownloader downloader{data.host, "443"};
      auto received = downloader.download(data.target);
      std::cout << "Downloaded and received: " << received << std::endl;
      std::cout << "New depth: " << depth_new << std::endl;
      boost::asio::post(parsers,
                        [this, capture0 = std::cref(received), depth_new]
                        { Parse(capture0, depth_new); });
    } else if (parse_count == 0) {
      if (!ready) {
        std::unique_lock<std::mutex> lock(download_mutex);
        ready = true;
        cond_var.notify_one();
      }
    }
  } catch (const std::exception& ex) {}
}

void ImgParser::Parse(const std::string& received, std::size_t depth_new) {
  Page page{received};
  auto links = page.GetLinks("href", GUMBO_TAG_A),
       images = page.GetLinks("src", GUMBO_TAG_IMG);
  std::cout << "Found links: " << links.size() << std::endl;
  parse_count.fetch_add(links.size());
  for (const auto& image : images) {
    boost::asio::post(writer, [this, &image]() {
      out << image << std::endl;
    });
    std::cout << "Wrote image " << image << std::endl;
  }
  for (const auto& link : links) {
    std::cout << "Moving to new link" << link << std::endl;
    --parse_count;
    boost::asio::post(downloaders,
                      [this, capture0 = std::cref(link),
                       capture1 = depth_new - 1]
                      { Download(capture0, capture1); });
  }
}
