#include <pybind11/pybind11.h>
#include <string>
#include <stdexcept>

namespace py = pybind11;
using std::out_of_range;


/*######################################################################################################################
C++ Classes
The pure virtual function should be reloaded with PYBIND11_OVERLOAD_PURE() method;
PYBIND11_OVERLOAD() should be used for functions which have a default implementation.
######################################################################################################################*/

class Animal {
public:
	virtual ~Animal() { }
	virtual std::string go(int n_times) = 0;
	virtual std::string name() { return "unknown"; }
	
	/*The constructor of the class Animal.*/
	Animal(double status_percenatge_=100): hp(status_percenatge_){
		if (status_percenatge_ > 100 || status_percenatge_ < 0) {
			throw out_of_range("The value of the status should be in the domain of [0, 100].");
		}
	}

	/*Check the status of the animal based on the hit point range.*/
	std::string check_hp() {
		if (hp >= 0 && hp <= 30)
			return "Sleepy.";
		else if (hp > 30 && hp <= 65)
			return "Normal.";
		else
			return "Excited.";
	}
	double hp;
};


class Dog : public Animal {
public:
	Dog(double hp) : Animal(hp) {}
	Dog() : Animal() {}
	std::string go(int n_times) override {
		std::string result;
		for (int i = 0; i<n_times; ++i)
			result += bark() + " ";
		return result;
	}
	virtual std::string bark() { return "woof!"; }
};

/*====================================================================================================================*/
/*Dymaic binding: When the function parameter, e.g., 'aminal' below, is a point or reference to a base class, it will
trigger a dynamic bindng, under which, the argument can be the base class itself or any class inheriting the base
class.*/
std::string call_go(Animal *animal) {
	return animal->go(3);
}


/*######################################################################################################################
Overloaded C++ Classes
######################################################################################################################*/

/*When combining virtual methods with inheritance, you need to be sure to provide an override for each method
for which you want to allow overrides from derived python classes. */
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
	std::string name() override {
		PYBIND11_OVERLOAD_PURE(std::string, Animal, name, );
	}
};

class PyDog : public Dog {
public:
	using Dog::Dog; // Inherit constructors
	std::string go(int n_times) override {
		PYBIND11_OVERLOAD_PURE(std::string, Dog, go, n_times);
	}
	std::string name() override { PYBIND11_OVERLOAD(std::string, Dog, name, ); }
	std::string bark() override { PYBIND11_OVERLOAD(std::string, Dog, bark, ); }
};


/*######################################################################################################################
Registered Python Classes
######################################################################################################################*/

PYBIND11_MODULE(chapter8, m) {
	py::class_<Animal, PyAnimal /* <--- trampoline*/>(m, "Animal")
		.def(py::init<double>())
		.def(py::init<>())
		.def("go", &Animal::go)
		.def("name", &Animal::name)
		.def("check_hp", &Animal::check_hp)
		.def_readwrite("hp", &Animal::hp);

	py::class_<Dog, Animal>(m, "Dog")
		.def(py::init<double>())
		.def(py::init<>())
		.def("bark", &Dog::bark);

	m.def("call_go", &call_go);
}