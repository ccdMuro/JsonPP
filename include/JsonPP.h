#pragma once

#include "Value.h"

#include <string>
#include <memory>

namespace Ccd {
namespace Json {

class JsonPP
{
	static Value arrayFromString(std::string jsonArrayString);
public:
	static Value objectFromString(std::string jsonString);
	static std::string stringFromObject ( Object& jsonObject );
};

}
}