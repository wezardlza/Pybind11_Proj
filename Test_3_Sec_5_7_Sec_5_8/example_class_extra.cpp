#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

struct PetN {
	enum Kind {
		Dog = 0, Cat
	};
	PetN(const std::string &name, int age, Kind type) : name(name), age(age), type(type) { }
	void set(int age_) { age = age_; }
	void set(const std::string &name_) { name = name_; }
	std::string name;
	Kind type;
	int age;
};

// 'm' represent the module
PYBIND11_MODULE(example_class_extra, m) {
	py::class_<PetN> pet(m, "PetN"); pet
		.def(py::init<const std::string &, int, PetN::Kind>())
		.def("set", (void (PetN::*)(int)) &PetN::set, "Set the pet's age")
		.def("set", (void (PetN::*)(const std::string &)) &PetN::set, "Set the pet's name")
		.def_readwrite("name", &PetN::name)
		.def_readwrite("age", &PetN::age)
		.def_readwrite("type", &PetN::type);

	py::enum_<PetN::Kind>(pet, "Kind")
		.value("Dog", PetN::Kind::Dog)
		.value("Cat", PetN::Kind::Cat);
}
