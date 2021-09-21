#ifndef SHORT_LINK_H
#define SHORT_LINK_H

#include <string>
#include <unordered_map>

class short_link {
public:
  /**
   * Encodes a URL to a shortened URL
   * @param url URL
   * @return Shortened URL
   */
  static std::string encode(std::string);

  /**
   * Decodes a shortened URL to its original URL
   * @param url URL
   * @return Original URL
   */
  static std::string decode(std::string);

private:
  static std::unordered_map<std::string, std::string> db;
};

#endif /* SHORT_LINK_H */