#include "minunit.h"
#include "short_link.h"
#include <iostream>

void test_setup(void) {
  short_link::init();
  short_link::test_setup();
}

void test_teardown(void) {}

MU_TEST(test_encode_fail) {
  rapidjson::Value json = short_link::encode("");
  mu_check(json.ObjectEmpty());
}

MU_TEST(test_encode) {
  rapidjson::Value json = short_link::encode("abc");
  mu_check(!json.ObjectEmpty());
  auto it = json.MemberBegin();
  mu_check(it->name.IsString());
  mu_assert_string_eq("a", it->name.GetString());
  mu_check(it->value.IsString());
  mu_assert_string_eq("abc", it->value.GetString());
}

MU_TEST(test_decode_empty) {
  rapidjson::Value json = short_link::decode("");
  mu_check(json.ObjectEmpty());
}

MU_TEST(test_decode_not_found) {
  rapidjson::Value json = short_link::decode("Kevin");
  mu_check(json.ObjectEmpty());
}

MU_TEST(test_decode) {
  rapidjson::Value decoded = short_link::decode("b");
  mu_check(!decoded.ObjectEmpty());
  auto it = decoded.MemberBegin();
  mu_check(it->name.IsString());
  mu_assert_string_eq("b", it->name.GetString());
  mu_check(it->value.IsString());
  mu_assert_string_eq("ABC", it->value.GetString());
}

MU_TEST_SUITE(test_suite) {
  MU_SUITE_CONFIGURE(&test_setup, &test_teardown);
  MU_RUN_TEST(test_encode_fail);
  MU_RUN_TEST(test_encode);
  MU_RUN_TEST(test_decode_empty);
  MU_RUN_TEST(test_decode_not_found);
  MU_RUN_TEST(test_decode);
}

int main(int argc, char *argv[]) {
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
  return MU_EXIT_CODE;
}
