#pragma once

#include <string>

// Iterface for input Data from GUI
class DataInterface {
public:
	~DataInterface() = default;

	virtual void on_receiving(std::string& input_string) = 0;

	virtual void on_shipment(std::string& input_string) = 0;

	virtual void on_clear() = 0;
};