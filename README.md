JsonPP
======


A C++ Library providing a `std::string` parser for JavaScript Object Notation. The STL container are in favor to represent the Json entities: Object, Array and Value.

Requirements
------------
C++17 standard is required to compile the library.

Code Example
------------

Json:
```json
{
	"user_name":"ccdMuro",
	"user_data":{
		"hobbies":["coding", "gaming"],
		"age":1337
	}
}
```

C++:
```cpp
#include <JsonPP.h>
using namespace Ccd::Json;

...
// get your Json somehow and store it into the std::string
...

// create Ccd::Json::Object from string
auto jsonObject = JsonPP::objectFromString(myJsonString);

// now access the object values with the subscript operator[]
auto userName = jsonObject["user_name"].toString();

// instead of the access method you can use an explicit cast
auto userAge = stati_cast<int>(jsonObject["user_data"]["age"]);

// STL container std::vector as Ccd::Json::Array backend 
for ( auto hobby : jsonObject["user_data"]["hobbies"].toArray()){
	// with stream operator<< support for std::iostream
	std::cout << hobby;
}

// create your own data from scratch
auto newObj = Ccd::Json::Object {
		{"user_name","newUser"},
		{"user_data", 
			Ccd::Json::Object {
				{"age", 42},
				{"hobbies", { "reading", "painting" } }
			}
		}
	};

// and turn it into a std::string
auto newJsonString = JsonPP::stringFromObject(newObj);

```

License
-------

This software is licensed under the [LGPL v3 license][lgpl].
© 2021 Karl Herbig

[lgpl]: https://www.gnu.org/licenses/lgpl-3.0.en.html
