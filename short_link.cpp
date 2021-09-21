#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> db;

/**
 * Encodes a URL to a shortened URL
 * @param url URL
 * @return Shortened URL
 */

std::string encode(std::string url) {
  std::string short_url;
  short_url = std::to_string(std::hash<std::string>{}(url));
  //   std::cout << "encode short_url: " << short_url << std::endl;
  auto res = db.insert({short_url, url});
  std::cout << "encode insert: " << res.second << std::endl;
  if (!res.second) {
    short_url = "";
  }
  return short_url;
}

/**
 * Decodes a shortened URL to its original URL
 * @param url URL
 * @return Original URL
 */

std::string decode(std::string short_url) { return ""; }

int main() {
  std::string url = "abc";
  std::cout << "main url: " << url << std::endl;
  std::string short_url = encode(url);
  std::cout << "main encode: " << short_url << std::endl;

  auto res = db.find(short_url);
  if (db.end() == res) {
    std::cout << "main not found" << std::endl;
  } else {
    std::cout << "main found: " << res->second << std::endl;
  }

  return 0;
}