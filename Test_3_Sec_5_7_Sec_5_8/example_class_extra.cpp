#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

struct Pet {
	Pet(const std::string &name, int age) : name(name), age(age) { }
	void set(int age_) { age = age_; }
	void set(const std::string &name_) { name = name_; }
	std::string name;
	int age;
};

// 'm' represent the module
PYBIND11_MODULE(example_class_extra, m) {
	py::class_<Pet>(m, "Pet")
		.def(py::init<const std::string &, int>())
		.def("set", (void (Pet::*)(int)) &Pet::set, "Set the pet's age")
		.def("set", (void (Pet::*)(const std::string &)) &Pet::set, "Set the pet's name");
}
