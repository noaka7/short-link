#include "short_link.h"
#include <algorithm>
#include <iostream>

rapidjson::Document short_link::document;
std::vector<std::pair<std::string, std::string>> short_link::db = {};
long long short_link::id = 0;

void short_link::init() {
  short_link::db.clear();
  short_link::id = 0;
}

rapidjson::Value short_link::encode(std::string url) {
  rapidjson::Value json(rapidjson::kObjectType);

  if (!url.empty()) {
    std::string short_url = short_link::id_to_short_url(short_link::id);
    auto it = short_link::db.begin();
    short_link::db.insert(it + short_link::id, {short_url, url});
    short_link::id++;

    rapidjson::Value key(short_url.c_str(),
                         short_link::document.GetAllocator());
    rapidjson::Value value(url.c_str(), short_link::document.GetAllocator());
    json.AddMember(key, value, short_link::document.GetAllocator());
  }

  return json;
}

rapidjson::Value short_link::decode(std::string short_url) {
  rapidjson::Value json(rapidjson::kObjectType);

  long long id = short_link::short_url_to_id(short_url);
  std::pair<std::string, std::string> res;
  try {
    res = short_link::db.at(id);
  } catch (std::out_of_range &oor) {
    std::cerr << oor.what() << std::endl;
  }
  std::string url = res.second;

  if (!url.empty()) {
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
  do {
    short_url.push_back(alphabet[id % 62]);
    id /= 62;
  } while (id);

  // Reverse short URL to complete base conversion
  reverse(short_url.begin(), short_url.end());

  return short_url;
}

long long short_link::short_url_to_id(std::string short_url) {
  if (short_url.empty()) {
    return -1;
  }

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

void short_link::test_setup() {
  short_link::db.push_back({"a", "xyz"});
  short_link::db.push_back({"b", "ABC"});
  short_link::db.push_back({"c", "123"});
}