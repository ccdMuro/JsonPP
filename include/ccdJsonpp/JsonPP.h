#pragma once

#include "Value.h"

#include <string>
#include <memory>

namespace Ccd {
namespace Json {

class JsonPP
{
public:
	static Value objectFromString(const std::string& jsonString);
	static Value arrayFromString(const std::string& jsonString);
	static std::string stringFromObject (const Object& jsonObject );
	static std::string stringFromArray (const Array& jsonArray );
};

}
}
