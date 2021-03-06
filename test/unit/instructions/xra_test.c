#include "attounit.h"
#include "i8080.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(instruction_xra);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

// Individual opcode tests
TEST_CASE(xra_b) {
  i8080_write_byte(cpu, 0, 0xA8); // XRA B
  cpu->B = 0xFF; cpu->A = 0xF0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(xra_c) {
  i8080_write_byte(cpu, 0, 0xA9); // XRA C
  cpu->C = 0xFF; cpu->A = 0xF0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(xra_d) {
  i8080_write_byte(cpu, 0, 0xAA); // XRA D
  cpu->D = 0xFF; cpu->A = 0xF0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(xra_e) {
  i8080_write_byte(cpu, 0, 0xAB); // XRA E
  cpu->E = 0xFF; cpu->A = 0xF0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(xra_h) {
  i8080_write_byte(cpu, 0, 0xAC); // XRA H
  cpu->H = 0xFF; cpu->A = 0xF0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(xra_l) {
  i8080_write_byte(cpu, 0, 0xAD); // XRA L
  cpu->L = 0xFF; cpu->A = 0xF0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

TEST_CASE(xra_m) {
  i8080_write_byte(cpu, 0, 0xAE); // XRA M
  i8080_write_byte(cpu, 0x05, 0xFF);
  cpu->A = 0xF0; cpu->H = 0x00; cpu->L = 0x05;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 7);
}

TEST_CASE(xra_a) {
  i8080_write_byte(cpu, 0, 0xAF); // XRA A
  cpu->A = 0xF0;

  i8080_step(cpu);

  ASSERT_EQUAL(cpu->A, 0x00);
  ASSERT_EQUAL(cpu->PC, 1);
  ASSERT_EQUAL(cpu->cyc, 4);
}

// Bit flag tests
TEST_CASE(xra_clears_flag_c_and_a) {
  i8080_write_byte(cpu, 0, 0xA8); // XRA B
  i8080_set_flag(cpu, FLAG_C, 1);
  i8080_set_flag(cpu, FLAG_A, 1);

  i8080_step(cpu);

  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_C));
  ASSERT_FALSE(i8080_get_flag(cpu, FLAG_A));
}

TEST_CASE(xra_sets_flag_z) {
  i8080_write_byte(cpu, 0, 0xA8); // XRA B
  cpu->A = 0xFF; cpu->B = 0xFF;
  i8080_set_flag(cpu, FLAG_Z, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_Z));
}

TEST_CASE(xra_sets_flag_s) {
  i8080_write_byte(cpu, 0, 0xA8); // XRA B
  cpu->A = 0x7F; cpu->B = 0xFF;
  i8080_set_flag(cpu, FLAG_S, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_S));
}

TEST_CASE(xra_sets_flag_p) {
  i8080_write_byte(cpu, 0, 0xA8); // XRA B
  cpu->A = 0x04; cpu->B = 0x07;
  i8080_set_flag(cpu, FLAG_P, 0);

  i8080_step(cpu);

  ASSERT_TRUE(i8080_get_flag(cpu, FLAG_P));
}