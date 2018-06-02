#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

class Animal {
public:
	virtual ~Animal() { }
	virtual std::string go(int n_times) = 0;
};

std::string call_go(Animal *animal) {
	return animal->go(3);
}

class Dog : public Animal {
public:
	std::string go(int n_times) override {
		std::string result;
		for (int i = 0; i<n_times; ++i)
			result += "woof! ";
		return result;
	}
};

class PyAnimal : public Animal {
public:
	/* Inherit the constructors */
	using Animal::Animal;
	/* Trampoline (need one for each virtual function) */
	std::string go(int n_times) override {
		PYBIND11_OVERLOAD_PURE(
			std::string, /* Return type */
			Animal, /* Parent class */
			go, /* Name of function in C++ (must match Python name) */
			n_times /* Argument(s) */
		);
	}
};

PYBIND11_MODULE(chapter8, m) {
	py::class_<Animal, PyAnimal /* <--- trampoline*/>(m, "Animal")
		.def(py::init<>())
		.def("go", &Animal::go);
	py::class_<Dog, Animal>(m, "Dog")
		.def(py::init<>());
	m.def("call_go", &call_go);
}