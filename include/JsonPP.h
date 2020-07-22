#pragma once

#include "Value.h"

#include <string>
#include <memory>

namespace Ccd {
namespace Json {

class JsonPP
{
public:
	static Value objectFromString(std::string jsonString);
	static Value arrayFromString(std::string jsonArrayString);
	static std::string stringFromObject (const Object& jsonObject );
	static std::string stringFromArray (const Array& jsonArray );
};

}
}
