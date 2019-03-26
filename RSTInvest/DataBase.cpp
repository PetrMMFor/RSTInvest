#include "DataBase.h"

//Method returns the name of the product on the basis of ID
std::string DataBase::get_products_name(const std::string& id) {
	auto handbook_it = _handbook.find(id);
	return (handbook_it != _handbook.end()) ? handbook_it->second : "";
}

//Method delete product from the map if product number = 0
//and returns info for GUI 
int DataBase::zero_check(const std::string& product_name)
{
	auto it = _products.find(product_name);
	if (it->second == 0) {
		_products.erase(it);
		return 0;
	}
	return it->second;
}

//Method converts letters to uppercase,
//add product in to map, if product already exist
//its parameter is increased by 1
//after zero_check() must be fuction, whitch sends info to GUI
//0 - need delete from receiving product,
// > 0 - update product on receiving field
void DataBase::add_product(std::string id) {
	assert(id.size() == 24);
	assert(!_handbook.empty());

	std::transform(id.begin(), id.end(), id.begin(), ::towupper);
	auto product_name = get_products_name(id);
	if (!product_name.empty()) {
		_products[product_name]++;
	}
	zero_check(product_name);
}

//Method converts letters to uppercase,
//add product in to map, if product already exist
//its parameter is reduced by 1
//after zero_check() must be fuction, whitch sends info to GUI
//0 - need delete from receiving product,
// < 0 - update product on shipment field
void DataBase::delete_product(std::string id) {
	assert(id.size() == 24);
	assert(!_handbook.empty());

	std::transform(id.begin(), id.end(), id.begin(), ::towupper);
	auto product_name = get_products_name(id);
	if (!product_name.empty()) {
		_products[product_name]--;
	}
	zero_check(product_name);
}

//Method splits the string inti ID whith using a delimiter
void DataBase::on_receiving(std::string& input_string) {
	if (!input_string.empty()) {
		size_t position = 0;
		while ((position = input_string.find(_delimiter)) != std::string::npos) {
			auto id = input_string.substr(0, position);
			add_product(id);
			input_string.erase(0, position + _delimiter.length());
		}
		add_product(input_string);
	}
}

//Method splits the string inti ID whith using a delimiter
void DataBase::on_shipment(std::string& input_string) {
	if (!input_string.empty()) {
		size_t position = 0;
		while ((position = input_string.find(_delimiter)) != std::string::npos) {
			auto id = input_string.substr(0, position);
			delete_product(id);
			input_string.erase(0, position + _delimiter.length());
		}
		delete_product(input_string);
	}
}

//Method clear map of products
void DataBase::on_clear() {
	_products.clear();
}
