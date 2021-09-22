#include "short_link.h"
#include <algorithm>

rapidjson::Document short_link::document;
std::unordered_map<std::string, std::string> short_link::db = {};

void short_link::init() { short_link::db.clear(); }

rapidjson::Value short_link::encode(std::string url) {
  rapidjson::Value json(rapidjson::kObjectType);

  std::string short_url = std::to_string(std::hash<std::string>{}(url));
  auto res = short_link::db.insert({short_url, url});
  if (!res.second) {
    throw insert_exception();
  }

  rapidjson::Value key(short_url.c_str(), short_link::document.GetAllocator());
  rapidjson::Value value(url.c_str(), short_link::document.GetAllocator());
  json.AddMember(key, value, short_link::document.GetAllocator());

  return json;
}

rapidjson::Value short_link::decode(std::string short_url) {
  rapidjson::Value json(rapidjson::kObjectType);

  auto res = short_link::db.find(short_url);
  if (short_link::db.end() != res) {
    std::string url = res->second;
    rapidjson::Value key(short_url.c_str(),
                         short_link::document.GetAllocator());
    rapidjson::Value value(url.c_str(), short_link::document.GetAllocator());
    json.AddMember(key, value, short_link::document.GetAllocator());
  }

  return json;
}

// private

std::string short_link::id_to_short_url(long long id) {
  // 62 alphanumerical characters
  std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDE"
                         "FGHIJKLMNOPQRSTUVWXYZ0123456789";

  std::string short_url;

  // Convert given integer ID to a base 62 number
  while (id) {
    short_url.push_back(alphabet[id % 62]);
    id /= 62;
  }

  // Reverse short URL to complete base conversion
  reverse(short_url.begin(), short_url.end());

  return short_url;
}

long long short_link::short_url_to_id(std::string short_url) {
  long long id = 0;

  for (auto it = short_url.begin(); it != short_url.end(); ++it) {
    if ('a' <= *it && *it <= 'z') {
      id = id * 62 + *it - 'a';
    } else if ('A' <= *it && *it <= 'A') {
      id = id * 62 + *it - 'A' + 26;
    } else if ('0' <= *it && *it <= '9') {
      id = id * 62 + *it - '0' + 52;
    }
  }

  return id;
}