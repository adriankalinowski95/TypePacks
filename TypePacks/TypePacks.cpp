// TypePacks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <variant>
#include <string>
#include "DefTypes.h"

using my_special_variant = templated_struct::builder<std::variant, def_types::my_special_type>::type;

int main() {
	my_special_variant templatedVariant{ 123 };
	if (!std::holds_alternative<int>(templatedVariant)) {
		return 0;
	}

	const auto valueInside = std::get_if<int>(&templatedVariant);
	if (!valueInside) {
		return 0;
	}

	std::cout << "Value inside a templated variant: " << std::to_string(*valueInside) << std::endl;

	return 1;
}