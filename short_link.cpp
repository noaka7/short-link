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

std::string decode(std::string short_url) {
  std::string ans = "";
  auto res = db.find(short_url);
  if (db.end() == res) {
    std::cout << "decode: not found" << std::endl;
  } else {
    ans = res->second;
    std::cout << "decode: found " << ans << std::endl;
  }
  return ans;
}

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

  std::string decoded = decode(short_url);
  std::cout << "main decoded == url: " << (decoded == url) << std::endl;

  return 0;
}