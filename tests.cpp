#include "minunit.h"
#include "short_link.h"
#include <iostream>

void test_setup(void) { short_link::init(); }

void test_teardown(void) {}

MU_TEST(test_encode_fail) {
  rapidjson::Value json;
  try {
    json = short_link::encode("abc");
  } catch (insert_exception &e) {
    std::cerr << e.what() << std::endl;
  }
  try {
    json = short_link::encode("abc");
  } catch (insert_exception &e) {
    std::cerr << e.what() << std::endl;
  }
  mu_check(!json.ObjectEmpty());
  auto it = json.MemberBegin();
  mu_check(it->name.IsString());
  mu_assert_string_eq("3663726644998027833", it->name.GetString());
  mu_check(it->value.IsString());
  mu_assert_string_eq("abc", it->value.GetString());
}

MU_TEST(test_encode) {
  rapidjson::Value json;
  try {
    json = short_link::encode("abc");
  } catch (insert_exception &e) {
    std::cerr << e.what() << std::endl;
  }
  mu_check(!json.ObjectEmpty());
  auto it = json.MemberBegin();
  mu_check(it->name.IsString());
  mu_assert_string_eq("3663726644998027833", it->name.GetString());
  mu_check(it->value.IsString());
  mu_assert_string_eq("abc", it->value.GetString());
}

MU_TEST(test_decode_fail) {
  mu_assert_string_eq("", short_link::decode("abc").c_str());
}

MU_TEST(test_decode) {
  rapidjson::Value json;
  try {
    json = short_link::encode("abc");
  } catch (insert_exception &e) {
    std::cerr << e.what() << std::endl;
  }
  mu_check(!json.ObjectEmpty());
  auto it = json.MemberBegin();
  mu_check(it->name.IsString());
  mu_assert_string_eq("3663726644998027833", it->name.GetString());
  mu_check(it->value.IsString());
  mu_assert_string_eq("abc", it->value.GetString());
  mu_assert_string_eq("abc", short_link::decode("3663726644998027833").c_str());
}

MU_TEST_SUITE(test_suite) {
  MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
  MU_RUN_TEST(test_encode_fail);
  MU_RUN_TEST(test_encode);
  MU_RUN_TEST(test_decode_fail);
  MU_RUN_TEST(test_decode);
}

int main(int argc, char *argv[]) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return MU_EXIT_CODE;
}
