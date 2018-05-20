#include "attounit.h"
#include "cpu.h"
#include "memory.h"
#include "cpu_test_helpers.h"

TEST_SUITE(immediate_addressing_instructions);

struct i8080 *cpu;

BEFORE_EACH() {
  cpu = setup_cpu_test_env();
}
AFTER_EACH() {
  teardown_cpu_test_env(cpu);
}

TEST_CASE(mvi_b_d8) {
  write_byte(cpu, 0, 0x06); // MVI B
  write_byte(cpu, 1, 0x01); // d8
  cpu->B = 0;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->B, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_c_d8) {
  write_byte(cpu, 0, 0x0E); // MVI C
  write_byte(cpu, 1, 0x01); // d8
  cpu->C = 0;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->C, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_d_d8) {
  write_byte(cpu, 0, 0x16); // MVI D
  write_byte(cpu, 1, 0x01); // d8
  cpu->D = 0;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->D, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_e_d8) {
  write_byte(cpu, 0, 0x1E); // MVI E
  write_byte(cpu, 1, 0x01); // d8
  cpu->E = 0;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->E, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_h_d8) {
  write_byte(cpu, 0, 0x26); // MVI H
  write_byte(cpu, 1, 0x01); // d8
  cpu->H = 0;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->H, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_l_d8) {
  write_byte(cpu, 0, 0x2E); // MVI L
  write_byte(cpu, 1, 0x01); // d8
  cpu->L = 0;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->L, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_m_d8) {
  write_byte(cpu, 0, 0x36); // MVI M
  write_byte(cpu, 1, 0x01); // d8
  cpu->H = 0x00; cpu->L = 0x08;

  step_cpu(cpu);

  ASSERT_EQUAL(read_byte(cpu, 8), 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(mvi_a_d8) {
  write_byte(cpu, 0, 0x3E); // MVI A
  write_byte(cpu, 1, 0x01); // d8
  cpu->A = 0;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(lxi_b_d16) {
  write_byte(cpu, 0, 0x01); // LXI B
  write_word(cpu, 1, 0xABCD); // d16
  cpu->B = 0x00; cpu->C = 0x00;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->B, 0xAB);
  ASSERT_EQUAL(cpu->C, 0xCD);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(lxi_d_d16) {
  write_byte(cpu, 0, 0x11); // LXI D
  write_word(cpu, 1, 0xABCD); // d16
  cpu->D = 0x00; cpu->E = 0x00;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->D, 0xAB);
  ASSERT_EQUAL(cpu->E, 0xCD);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(lxi_h_d16) {
  write_byte(cpu, 0, 0x21); // LXI H
  write_word(cpu, 1, 0xABCD); // d16
  cpu->H = 0x00; cpu->L = 0x00;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->H, 0xAB);
  ASSERT_EQUAL(cpu->L, 0xCD);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(lxi_sp_d16) {
  write_byte(cpu, 0, 0x31); // LXI B
  write_word(cpu, 1, 0xABCD); // d16
  cpu->SP = 0x0000;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->SP, 0xABCD);
  ASSERT_EQUAL(cpu->PC, 3);
}

TEST_CASE(adi) {
  write_byte(cpu, 0, 0xC6); // ADI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 1);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(adi_sets_c_flag) {
  write_byte(cpu, 0, 0xC6); // ADI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0xFF;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
}

TEST_CASE(adi_sets_z_flag) {
  write_byte(cpu, 0, 0xC6); // ADI
  write_byte(cpu, 1, 0); // d8

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(adi_sets_p_flag) {
  write_byte(cpu, 0, 0xC6); // ADI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 2;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(adi_sets_s_flag) {
  write_byte(cpu, 0, 0xC6); // ADI B
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x7F;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(adi_sets_a_flag) {
  write_byte(cpu, 0, 0xC6); // ADI
  write_byte(cpu, 1, 1);
  cpu->A = 0x0F;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

TEST_CASE(aci) {
  write_byte(cpu, 0, 0xCE); // ACI
  write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xFF;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xFF);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(aci_unsets_c_flag) {
  write_byte(cpu, 0, 0xCE); // ACI B
  write_byte(cpu, 1, 1); // d8
  cpu->A = 2;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(aci_sets_z_flag) {
  write_byte(cpu, 0, 0xCE); // ACI
  write_byte(cpu, 1, 0); // d8
  cpu->A = 0x00;
  set_flag(cpu, FLAG_Z, 0);

  step_cpu(cpu);
  
  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(aci_sets_p_flag) {
  write_byte(cpu, 0, 0xCE); // ACI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x02;
  set_flag(cpu, FLAG_P, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(aci_sets_s_flag) {
  write_byte(cpu, 0, 0xCE); // ACI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x7F;
  set_flag(cpu, FLAG_S, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(aci_sets_a_flag) {
  write_byte(cpu, 0, 0xCE); // ACI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x0F;
  set_flag(cpu, FLAG_A, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

TEST_CASE(sui) {
  write_byte(cpu, 0, 0xD6); // SUI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 1;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(sui_sets_c_flag) {
  write_byte(cpu, 0, 0xD6); // SUI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x00;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sui_resets_c_flag) {
  write_byte(cpu, 0, 0xD6); // SUI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x01;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sui_sets_a_flag) {
  write_byte(cpu, 0, 0xD6); // SUI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x01;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

TEST_CASE(sui_sets_z_flag) {
  write_byte(cpu, 0, 0xD6); // SUI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(sui_sets_p_flag) {
  write_byte(cpu, 0, 0xD6); // SUI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x04;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(sui_sets_s_flag) {
  write_byte(cpu, 0, 0xD6); // SUI
  write_byte(cpu, 1, 1);
  cpu->A = 0xFF;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(sbi) {
  write_byte(cpu, 0, 0xDE); // SBI
  write_byte(cpu, 1, 0x0F); // d8
  cpu->A = 0xF0;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xE0);
  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(sbi_sets_z_flag) {
  write_byte(cpu, 0, 0xDE); // SBI
  write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xFF;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(sbi_sets_p_flag) {
  write_byte(cpu, 0, 0xDE); // SBI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 4;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(sbi_sets_s_flag) {
  write_byte(cpu, 0, 0xDE); // SBI
  write_byte(cpu, 1, 1);
  cpu->A = 0xFF;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(sbi_sets_a_flag) {
  write_byte(cpu, 0, 0xDE); // SBI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x01;
  set_flag(cpu, FLAG_A, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

TEST_CASE(sbi_subtrahend_0xFF_with_borrow) {
  write_byte(cpu, 0, 0xDE); // SBI
  write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xAB;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0xAB);
  ASSERT_TRUE(get_flag(cpu, FLAG_C));
  ASSERT_FALSE(get_flag(cpu, FLAG_A));
}


TEST_CASE(ani) {
  write_byte(cpu, 0, 0xE6); // ANI
  write_byte(cpu, 1, 6); // d8
  cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 2);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(ani_resets_c_flag) {
  write_byte(cpu, 0, 0xE6); // ANI
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(ani_sets_z_flag) {
  write_byte(cpu, 0, 0xE6); // ANI
  write_byte(cpu, 1, 0); // d8
  cpu->A = 0xFF;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(ani_sets_p_flag) {
  write_byte(cpu, 0, 0xE6); // ANI
  write_byte(cpu, 1, 3); // d8
  cpu->A = 7;
  set_flag(cpu, FLAG_P, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(ani_sets_s_flag) {
  write_byte(cpu, 0, 0xE6); // ANI
  write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xFF;
  set_flag(cpu, FLAG_S, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

// On the 8080, logical and instructions set the aux carry flag to the logical
// or of bit 3 of the values involved in the operation
TEST_CASE(ani_sets_a_flag) {
  write_byte(cpu, 0, 0xE6); // ANI
  write_byte(cpu, 1, 0xF0); // d8
  cpu->A = 0x08;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

TEST_CASE(ani_resets_a_flag) {
  write_byte(cpu, 0, 0xE6); // ANI
  write_byte(cpu, 1, 0x07); // d8
  cpu->A = 0xF0;

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_A));
}

TEST_CASE(ori) {
  write_byte(cpu, 0, 0xF6); // ORI
  write_byte(cpu, 1, 6); // d8
  cpu->A = 10;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 14);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(ori_resets_c_flag) {
  write_byte(cpu, 0, 0xF6); // ORI
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(ori_sets_z_flag) {
  write_byte(cpu, 0, 0xF6); // ORI
  write_byte(cpu, 1, 0); // d8
  cpu->A = 0x00;
  set_flag(cpu, FLAG_Z, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(ori_sets_s_flag) {
  write_byte(cpu, 0, 0xF6); // ORI
  write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0x00;
  set_flag(cpu, FLAG_S, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(ori_sets_p_flag) {
  write_byte(cpu, 0, 0xF6); // ORI
  write_byte(cpu, 1, 3); // d8
  cpu->A = 0x00;
  set_flag(cpu, FLAG_P, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(xri) {
  write_byte(cpu, 0, 0xEE); // XRI
  write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xF0;

  step_cpu(cpu);

  ASSERT_EQUAL(cpu->A, 0x0F);
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(xri_resets_flag_c) {
  write_byte(cpu, 0, 0xEE); // XRI
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(xri_sets_flag_z) {
  write_byte(cpu, 0, 0xEE); // XRI
  write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0xFF;
  set_flag(cpu, FLAG_Z, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(xri_sets_flag_s) {
  write_byte(cpu, 0, 0xEE); // XRI
  write_byte(cpu, 1, 0xFF); // d8
  cpu->A = 0x7F;
  set_flag(cpu, FLAG_S, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(xri_sets_flag_p) {
  write_byte(cpu, 0, 0xEE); // XRI
  write_byte(cpu, 1, 7); // d8
  cpu->A = 0x04;
  set_flag(cpu, FLAG_P, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(cpi) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 1;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
  ASSERT_EQUAL(cpu->PC, 2);
}

TEST_CASE(cpi_less) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 0x05); // d8
  cpu->A = 0x0A;

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(cpi_greater) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 0x05); // d8
  cpu->A = 0x02;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
}

TEST_CASE(cpi_not_equal) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 0x05); // d8
  cpu->A = 0xFF;

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
  ASSERT_FALSE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(cpi_equal) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 0x0A); // d8
  cpu->A = 0x0A;

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
  ASSERT_TRUE(get_flag(cpu, FLAG_Z));
}

TEST_CASE(cpi_sets_s_flag) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0xFF;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_S));
}

TEST_CASE(cpi_sets_p_flag) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x04;

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_P));
}

TEST_CASE(cpi_sets_c_flag) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 0x01); // d8
  cpu->A = 0x00;
  set_flag(cpu, FLAG_C, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_C));
}

TEST_CASE(cpi_resets_c_flag) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 0x01); // d8
  cpu->A = 0x01;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}

TEST_CASE(cpi_sets_a_flag) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 1); // d8
  cpu->A = 0x01;
  set_flag(cpu, FLAG_A, 0);

  step_cpu(cpu);

  ASSERT_TRUE(get_flag(cpu, FLAG_A));
}

// Comparisons with 0 are tricky
// https://retrocomputing.stackexchange.com/questions/6407/intel-8080-behaviour-of-the-carry-bit-when-comparing-a-value-with-0
TEST_CASE(cpi_compare_with_0) {
  write_byte(cpu, 0, 0xFE); // CPI
  write_byte(cpu, 1, 0); // d8
  cpu->A = 0x01;
  set_flag(cpu, FLAG_C, 1);

  step_cpu(cpu);

  ASSERT_FALSE(get_flag(cpu, FLAG_C));
}