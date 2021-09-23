#ifndef SHORT_LINK_H
#define SHORT_LINK_H

#include "rapidjson/document.h"
#include <string>
#include <utility>
#include <vector>

class short_link {
public:
  /**
   * Initializes module short link
   */
  static void init();

  /**
   * Encodes a URL to a shortened URL
   * @param url URL
   * @return JSON with shortened URL and URL as key-value pair
   *          Empty if url is not valid
   */
  static rapidjson::Value encode(std::string);

  /**
   * Decodes a shortened URL to its original URL
   * @param url URL
   * @return JSON with shortened URL and original URL as key-value pair
   *          Empty if not found
   */
  static rapidjson::Value decode(std::string);

  /**
   * Insert {"a", "abc"}, {"B", "ABC"} and {"3", "123"} in db
   */
  static void test_setup();

private:
  static rapidjson::Document document;
  static std::vector<std::pair<std::string, std::string>> db;
  static long long id;

  /**
   * Generates a short URL from integer ID
   * @param id ID
   * @return Short URL
   */
  static std::string id_to_short_url(long long);

  /**
   * Get integer ID from a short URL
   * @param short_url Short URL
   * @return Integer ID. Return -1 if short_url is empty
   */
  static long long short_url_to_id(std::string);
};

#endif /* SHORT_LINK_H */