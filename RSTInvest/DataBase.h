#pragma once
#include <map>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "DataInterface.h"


class DataBase : public DataInterface {
private:
	const std::map<std::string, std::string> _handbook;
	std::map<std::string, int> _products;

	std::string _delimiter = " ";

	std::string get_products_name(const std::string& id);

	int zero_check(const std::string& product_name);

	void add_product(std::string id);

	void delete_product(std::string id);
public:
	DataBase(std::map<std::string, std::string>& hb) : _handbook(hb) {};

	void on_receiving(std::string& input_string) override;

	void on_shipment(std::string& input_string) override;

	void on_clear() override;

	std::map<std::string, int> get_products() { return _products; };
};