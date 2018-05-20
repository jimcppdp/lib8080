#include "i8080.h"
#include "attounit.h"
#include "cpu_test_helpers.h"

TEST_SUITE(status_flags)

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(set_flag_c) {
  reset_cpu(cpu);
  set_flag(cpu, FLAG_C, 1);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->flags, 0x3);
}

TEST_CASE(set_flag_p) {
  reset_cpu(cpu);
  set_flag(cpu, FLAG_P, 1);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
  ASSERT_EQUAL(cpu->flags, 0x6);
}

TEST_CASE(set_flag_a) {
  reset_cpu(cpu);
  set_flag(cpu, FLAG_A, 1);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
  ASSERT_EQUAL(cpu->flags, 0x12);
}

TEST_CASE(set_flag_z) {
  reset_cpu(cpu);
  set_flag(cpu, FLAG_Z, 1);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->flags, 0x42);
}

TEST_CASE(set_flag_s) {
  reset_cpu(cpu);
  set_flag(cpu, FLAG_S, 1);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
  ASSERT_EQUAL(cpu->flags, 0x82);
}