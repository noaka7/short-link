#include "short_link.h"

std::unordered_map<std::string, std::string> short_link::db = {};

void short_link::init() { short_link::db.clear(); }

std::string short_link::encode(std::string url) {
  std::string short_url;
  short_url = std::to_string(std::hash<std::string>{}(url));
  auto res = short_link::db.insert({short_url, url});
  if (!res.second) {
    throw insert_exception();
  }
  return short_url;
}

std::string short_link::decode(std::string short_url) {
  std::string ans = "";
  auto res = short_link::db.find(short_url);
  if (short_link::db.end() != res) {
    ans = res->second;
  }
  return ans;
}