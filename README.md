JsonPP
======

A C++ Library providing a 'std::string' parser for JavaScript Object Notation. The STL container are in favor to represent the Json entities: Object, Array and Value.

Requirements
------------
C++11/14 standard is required to compile the library.

Code Example
------------

Json:
```json
{
	"user_name":"ccdMuro"
	"user_data":{
		"hobbys":["hacking", "gaming"],
		"age":99
	}
}
```

C++:
```cpp
#include <JsonPP.h>
using namespace Ccd::Json;

...
/* get your Json somehow and store it into the std::string */
...

auto jsonObject = JsonPP::objectFromString(myJsonString);

/* now access the object values with the subscript operator[] */
auto userName = jsonObject["user_name"].toString();
auto userAge = jsonObject["user_data"]["age"].toInt();
auto hobbys = std::vector{};
for ( auto item : jsonObject["user_data"]["hobbys"]){
	hobbys = item.toString();
}
```