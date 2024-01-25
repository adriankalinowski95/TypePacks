#pragma once

#include <string>
#include "TemplatedStructBuilder.h"

namespace def_types {

using my_special_type = templated_struct::special_type<std::string, int, float, bool>;

}