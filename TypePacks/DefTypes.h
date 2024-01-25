#pragma once

#include <string>
#include "TemplatedStructBuilder.h"

namespace def_types {

using my_special_type = templated_struct::special_type<int, float, std::string>;

}