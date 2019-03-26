#pragma once
#include <map>
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <string>
#include "DataInterface.h"
#include "pugixml.hpp"
#include "pugiconfig.hpp"


class DataBase : public DataInterface {
private:
	std::map<std::string, std::string> _handbook;
	std::map<std::string, int> _products;

	std::string _delimiter = " ";

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("Base.xml");

	std::string get_products_name(const std::string& id);

	int zero_check(const std::string& product_name);

	void add_product(std::string id);

	void delete_product(std::string id);
public:
	DataBase(){
		pugi::xml_document doc;

		if (!doc.load_file("DataBase.xml")) {
			std::cout << "Can't open or find file DataBase.xml check it" << std::endl;
		}

		pugi::xml_node product = doc.child("base");

		for (pugi::xml_node tool = product.child("Product"); tool; tool = tool.next_sibling("Product"))
		{
			_handbook[tool.attribute("Id").value()] = tool.attribute("Name").value();
		}
	};

	void on_receiving(std::string& input_string) override;

	void on_shipment(std::string& input_string) override;

	void on_clear() override;

	std::map<std::string, int> get_products() override { return _products; };
};