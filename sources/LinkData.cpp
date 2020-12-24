

#include <LinkData.hpp>

namespace utils {
auto DivideIntoHostAndTarget(const std::string& url) -> LinkData {
  LinkData result;

  if (url.find("http") == 0 || url.find("https") == 0) {
    size_t iterator_counter = 0;
    size_t found2 = 0;
    for (size_t i = 0; i < url.size(); i++) {
      if (url[i] == '/') {
        found2 = i;
        iterator_counter++;
        if (iterator_counter == 3) {
          break;
        }
      }
    }
    std::string host;

    if (url.find("https") == 0) {
      host = url.substr(8, url.size() - (url.size() - found2) - 8);
    } else {
      host = url.substr(7, url.size() - (url.size() - found2) - 7);
    }
    std::string target = url.substr(found2, url.size() - found2);
    result.host = host;
    result.target = target;
  }

  return result;
}
}
