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

class Husky : public Dog {};

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

template <class AnimalBase = Animal> class PyAnimal : public AnimalBase {
public:
	using AnimalBase::AnimalBase; // Inherit constructors
	std::string go(int n_times) override {
		PYBIND11_OVERLOAD_PURE(std::string, AnimalBase, go, n_times);
	}
	std::string name() override {
		PYBIND11_OVERLOAD(std::string, AnimalBase, name, );
	}
};

template <class DogBase = Dog> class PyDog : public PyAnimal<DogBase> {
public:
	using PyAnimal<DogBase>::PyAnimal; // Inherit constructors
									   // Override PyAnimal's pure virtual go() with a non-pure one:
	std::string go(int n_times) override {
		PYBIND11_OVERLOAD(std::string, DogBase, go, n_times);
	}
	std::string bark() override { PYBIND11_OVERLOAD(std::string, DogBase, bark, ); }
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

	py::class_<>

	m.def("call_go", &call_go);
}