#include "transport.h"
#include "unity.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_parse_TLV() {
  char *data = malloc(4);
  data[0] = 0x00;
  data[1] = 0x02;
  data[2] = 0xAA;
  data[3] = 0xAA;
  tlv8 result = read_tlv8(data);
  TEST_ASSERT_EQUAL(2, result.length);
}

int main(int argc, char **argv) {
  UNITY_BEGIN();
  RUN_TEST(test_parse_TLV);
  return UNITY_END();
}
