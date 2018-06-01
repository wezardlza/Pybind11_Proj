#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

struct Pet {
	enum Kind {
		Dog = 0, Cat
	};
	Pet(const std::string &name, int age, Kind type) : name(name), age(age), type(type) { }
	void set(int age_) { age = age_; }
	void set(const std::string &name_) { name = name_; }
	std::string name;
	Kind type;
	int age;
};

// 'm' represent the module
PYBIND11_MODULE(example_class_extra, m) {
	py::class_<Pet> pet(m, "Pet")
		.def(py::init<const std::string &, int>())
		.def("set", (void (Pet::*)(int)) &Pet::set, "Set the pet's age")
		.def("set", (void (Pet::*)(const std::string &)) &Pet::set, "Set the pet's name")
		.def_readwrite("name", &Pet:name)
		.def_readwrite("age", &Pet::age)
		.def_readwrite("type", &Pet::type);

	py::enum_<Pet::Kind>(pet, "Kind")
		.value("Dog", Pet::Kind::Dog)
		.value("Cat", Pet::Kind::Cat)
		.export_value();
}
