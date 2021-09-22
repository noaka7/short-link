#include "short_link.h"

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

std::string short_link::decode(std::string short_url) {
  std::string ans = "";
  auto res = short_link::db.find(short_url);
  if (short_link::db.end() != res) {
    ans = res->second;
  }
  return ans;
}