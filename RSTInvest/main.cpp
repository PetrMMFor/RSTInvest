#include <map>
#include <memory>
#include "DataBase.h"

int main() {

	auto base = std::make_shared<DataBase>();

	std::string input_string_add_2 = "304DB75F196000180001C13A 304DB75F196000180001C13B";
	std::string input_string_add_1 = "304DB75F196000180001C13a";
	std::string input_string_del_1 = "304DB75F196000180001C13B";
	
	base->on_receiving(input_string_add_2);
	base->on_receiving(input_string_add_1);
	base->on_shipment(input_string_del_1);
	base->on_shipment(input_string_del_1);

	return 1;
}