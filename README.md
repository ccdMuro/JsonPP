JsonPP
======

A C++ Library providing a `std::string` parser for JavaScript Object Notation aka JSON.
The STL containers are in favor to represent the Json entities: Object, Array and Value.

Requirements
------------
C++17 standard is required to compile the library. 
Also cmake is recommended for building and installation.

Build and Install
-----------------
Use the default cmake procedure to build and install the library on your system.
```sh
git clone https://github.com/ccdMuro/JsonPP.git
cmake -B bld_jsonpp -S JsonPP
cmake --build bld_jsonpp
sudo cmake --install bld_jsonpp
```

Use in your project
-------------------
Add these lines to your CMakeLists.txt (*maybe adjust the target signature*):
```cmake
find_package(ccdJsonpp 1.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC ccdJsonpp)
```

Code Example
------------
### Simple value access:
Serialisation into `std::iostream` build in.
```cpp
std::cout << jsonObject["userData"] << "\n";
```
---
Verify type.
```cpp
if ( jsonObject["userData"].type() == Ccd::Json::ValueType::Object)
{
	// ...
}
```
---
Access the object values with the subscript operator[],
with the access method or an explicit cast
```cpp
auto msgId_a = jsonObject["messageID"].toInt();
auto msgId_b = static_cast<int>(jsonObject["messageID"]);
```
---
Write/Assign values.
```cpp
jsonObject["timeStamp"] = secondsSinceEpoch;
```

### Array value access: 
STL container `std::vector` is used as Ccd::Json::Array backend.
Write loops as usual.
```cpp
for ( const auto& attribute : jsonObject["attributes"].toArray() ) {
	// ...
}
```

### Build Objects from scratch
```cpp
auto jsonObject = Ccd::Json::Object {};
jsonObject["colors"] = { "red", "green", "blue" };
jsonObject["user"] = Ccd::Json::Object{
	{"name","alice"},
	{"age",20},
	{"size",1.90},
	{"hobbies", { "reading", "rock music" }}
};
```

### Parse a `std::string`
```cpp
auto jsonObject = Ccd::Json::objectFromString(JSONstring);
```

### Example Code
Some working examples can be found in the `example` folder.

License
-------
This software is licensed under the [LGPL v3 license][lgpl].
© 2021 Karl Herbig

[lgpl]: https://www.gnu.org/licenses/lgpl-3.0.en.html

## == We're Using GitHub Under Protest ==

This project is currently hosted on GitHub.  This is not ideal; GitHub is a
proprietary, trade-secret system that is not Free and Open Souce Software
(FOSS).  We are deeply concerned about using a proprietary system like GitHub
to develop our FOSS project. 

This project has been migrated to [codeberg.org](https://codeberg.org/muro/JsonPP).

We urge you to read about the [Give up GitHub](https://GiveUpGitHub.org) campaign from
[the Software Freedom Conservancy](https://sfconservancy.org) to understand
some of the reasons why GitHub is not a good place to host FOSS projects.

Any use of this project's code by GitHub Copilot, past or present, is done
without our permission.  We do not consent to GitHub's use of this project's
code in Copilot.

![Logo of the GiveUpGitHub campaign](https://sfconservancy.org/img/GiveUpGitHub.png)
