
#include <gtest/gtest.h>

#include <bitset>
#include <fstream>

#include "../src/assembler.hpp"
#include "../src/utility.hpp"

using namespace std;

class AssemblerTest : public ::testing::Test {
   protected:
    virtual void SetUp() { assembler_ptr = new Assembler{true}; }
    virtual void TearDown() { delete assembler_ptr; }

    std::vector<uint32_t> get_results(vector<string> input_data) {
        std::vector<uint32_t> ret;
        for (auto asmcode : input_data) {
            if (asmcode == "") break;
            asmcode = unit_space(strip(asmcode));
            ret.emplace_back(assembler_ptr->convert(asmcode));
        }
        return ret;
    }

    void assert_vec_eq(vector<uint32_t> actual_data, vector<string> expected_data) {
        for (auto [actual, expected] : zip(actual_data, expected_data)) {
            ASSERT_EQ(actual, std::stoul(expected, nullptr, 2));
        }
    }

    Assembler *assembler_ptr;
};

void normalize(vector<string> &data) {
    auto f = [](string x) { return unit_space(strip(x)); };
    transform(data.begin(), data.end(), data.begin(), f);
}

void preprocess(vector<string> &data) {
    auto f = [](string x) { return replace_all(x, "_", ""); };
    transform(data.begin(), data.end(), data.begin(), f);
}

TEST_F(AssemblerTest, correct_type1_input_test) {
    auto input_data = loadtxt("input/input_field_type_1.txt");
    auto expected_data = loadtxt("input/input_field_type_1_ans.txt");
    normalize(input_data);
    preprocess(expected_data);
    auto actual_data = get_results(input_data);
    assert_vec_eq(actual_data, expected_data);
}

TEST_F(AssemblerTest, correct_type2_input_test) {
    auto input_data = loadtxt("input/input_field_type_2.txt");
    auto expected_data = loadtxt("input/input_field_type_2_ans.txt");
    normalize(input_data);
    preprocess(expected_data);
    auto actual_data = get_results(input_data);
    assert_vec_eq(actual_data, expected_data);
}

TEST_F(AssemblerTest, correct_type3_input_test) {
    auto input_data = loadtxt("input/input_field_type_3.txt");
    auto expected_data = loadtxt("input/input_field_type_3_ans.txt");
    normalize(input_data);
    preprocess(expected_data);
    auto actual_data = get_results(input_data);
    assert_vec_eq(actual_data, expected_data);
}

TEST_F(AssemblerTest, correct_type4_input_test) {
    auto input_data = loadtxt("input/input_field_type_4.txt");
    auto expected_data = loadtxt("input/input_field_type_4_ans.txt");
    normalize(input_data);
    preprocess(expected_data);
    auto actual_data = get_results(input_data);
    assert_vec_eq(actual_data, expected_data);
}

TEST_F(AssemblerTest, correct_type5_input_test) {
    auto input_data = loadtxt("input/input_field_type_5.txt");
    auto expected_data = loadtxt("input/input_field_type_5_ans.txt");
    normalize(input_data);
    preprocess(expected_data);
    auto actual_data = get_results(input_data);
    assert_vec_eq(actual_data, expected_data);
}

TEST_F(AssemblerTest, correct_type6_input_test) {
    auto input_data = loadtxt("input/input_field_type_6.txt");
    auto expected_data = loadtxt("input/input_field_type_6_ans.txt");
    normalize(input_data);
    preprocess(expected_data);
    auto actual_data = get_results(input_data);
    assert_vec_eq(actual_data, expected_data);
}

TEST_F(AssemblerTest, correct_type7_input_test) {
    auto input_data = loadtxt("input/input_field_type_7.txt");
    auto expected_data = loadtxt("input/input_field_type_7_ans.txt");
    normalize(input_data);
    preprocess(expected_data);
    auto actual_data = get_results(input_data);
    assert_vec_eq(actual_data, expected_data);
}

TEST_F(AssemblerTest, correct_type8_input_test) {
    auto input_data = loadtxt("input/input_field_type_8.txt");
    auto expected_data = loadtxt("input/input_field_type_8_ans.txt");
    normalize(input_data);
    preprocess(expected_data);
    auto actual_data = get_results(input_data);
    assert_vec_eq(actual_data, expected_data);
}

TEST_F(AssemblerTest, correct_input_testcode) {
    auto input_data = loadtxt("input/input_testcode.txt");
    auto expected_data = loadtxt("input/input_testcode_ans.txt");
    normalize(input_data);
    preprocess(expected_data);
    Assembler assembler{input_data, true};
    auto actual_data = assembler.convert_all();
    assert_vec_eq(actual_data, expected_data);
}
