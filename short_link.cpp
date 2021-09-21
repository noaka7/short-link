#include "short_link.h"
#include <iostream>

std::unordered_map<std::string, std::string> short_link::db = {};

std::string short_link::encode(std::string url) {
  std::string short_url;
  short_url = std::to_string(std::hash<std::string>{}(url));
  //   std::cout << "encode short_url: " << short_url << std::endl;
  auto res = short_link::db.insert({short_url, url});
  std::cout << "encode insert: " << res.second << std::endl;
  if (!res.second) {
    throw insert_exception();
  }
  return short_url;
}

std::string short_link::decode(std::string short_url) {
  std::string ans = "";
  auto res = short_link::db.find(short_url);
  if (short_link::db.end() == res) {
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
  std::string short_url;
  try {
    short_url = short_link::encode(url);
  } catch (insert_exception &e) {
    std::cout << "main insertion exception: " << e.what() << std::endl;
  }
  std::cout << "main encode: " << short_url << std::endl;

  // expected failure
  try {
    short_url = short_link::encode(url);
  } catch (insert_exception &e) {
    std::cout << "main insertion exception: " << e.what() << std::endl;
  }

  // auto res = short_link::db.find(short_url);
  // if (short_link::db.end() == res) {
  //   std::cout << "main not found" << std::endl;
  // } else {
  //   std::cout << "main found: " << res->second << std::endl;
  // }

  std::string decoded = short_link::decode(short_url);
  std::cout << "main decoded == url: " << (decoded == url) << std::endl;

  return 0;
}