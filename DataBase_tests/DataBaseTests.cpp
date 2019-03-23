#include "gtest\gtest.h"
#include "DataBase.h"
#include <map>

struct TestInputData : public testing::Test
{
	std::map<std::string, std::string> handbook;

	void SetUp() {
		handbook["304DB75F196000180001C13A"] = "product_1";
		handbook["304DB75F196000180001C13B"] = "product_2";
	}

	std::string input_string_add_2_params = "304DB75F196000180001C13A 304DB75F196000180001C13B";
	std::string input_string_add_1_param_whith_litle_letter = "304DB75F196000180001C13a";
	std::string input_string_del_1_param = "304DB75F196000180001C13B";

	std::string input_empty_string = "";
	std::string input_string_whith_size_25 = "304DB75F196000180001C13BC";
};

TEST_F(TestInputData, 2_params_add_test) {
	std::map<std::string, int> test_map;
	test_map["product_1"] = 1;
	test_map["product_2"] = 1;

	DataBase database(handbook);
	database.on_receiving(input_string_add_2_params);

	EXPECT_EQ(test_map, database.get_products());
}

TEST_F(TestInputData, 1_param_add_test) {
	std::map<std::string, int> test_map;
	test_map["product_2"] = 1;

	DataBase database(handbook);
	database.on_receiving(input_string_add_1_param_whith_litle_letter);

	EXPECT_EQ(test_map, database.get_products());
}

TEST_F(TestInputData, 1_param_del_test) {
	std::map<std::string, int> test_map;
	test_map["product_1"] = 1;

	DataBase database(handbook);
	database.on_receiving(input_string_add_2_params);
	database.on_shipment(input_string_del_1_param);

	EXPECT_EQ(test_map, database.get_products());
}

TEST_F(TestInputData, 1_param_ship_test) {
	std::map<std::string, int> test_map;
	test_map["product_2"] = -1;

	DataBase database(handbook);
	database.on_shipment(input_string_del_1_param);

	EXPECT_EQ(test_map, database.get_products());
}

TEST_F(TestInputData, empty_input_string) {
	DataBase database(handbook);

	EXPECT_TRUE(database.get_products().empty());
}

TEST_F(TestInputData, size_test) {
	DataBase database(handbook);
	ASSERT_ANY_THROW(database.on_receiving(input_string_whith_size_25));
	ASSERT_ANY_THROW(database.on_shipment(input_string_whith_size_25));
}