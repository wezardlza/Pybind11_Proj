#include <pybind11/pybind11.h>
#include <string>
#include <stdexcept>

namespace py = pybind11;
using std::out_of_range;


/*######################################################################################################################
C++ Classes
The pure virtual function should be reloaded with PYBIND11_OVERLOAD_PURE() method;
PYBIND11_OVERLOAD() should be used for functions which have a default implementation.
========================================================================================================================
Module Classes
----------------------------------------------------------------------------------------------------------------------*/

class Animal {
public:
	virtual ~Animal() { }
	virtual std::string go(int n_times) = 0;
	virtual std::string name() { return "unknown"; }

	// The constructor of the class Animal.
	Animal(double status_percenatge_ = 100) : hp(status_percenatge_) {
		if (status_percenatge_ > 100 || status_percenatge_ < 0) {
			throw out_of_range("The value of the status should be in the domain of [0, 100].");
		}
	}

	// Check the status of the animal based on the hit point range.
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
	
	Dog() : Animal() {}
	//A constructor based on a factory function.
	static Dog create(double status_percentage_ = 100) { return Dog(status_percentage_); }

	virtual std::string bark() { return "woof!"; }

	std::string go(int n_times) override {
		std::string result;
		for (int i = 0; i<n_times; ++i)
			result += bark() + " ";
		return result;
	}

private:

	Dog(double hp) : Animal(hp) {}
};

class Husky :public Dog {};

/*======================================================================================================================
Module Functions
----------------------------------------------------------------------------------------------------------------------*/

// Dymaic binding: When the function parameter, e.g., 'aminal' below, is a point or reference to a base class, it will
// trigger a dynamic bindng, under which, the argument can be the base class itself or any class inheriting the base
// class.
std::string call_go(Animal *animal) {
	return animal->go(3);
}


/*######################################################################################################################
Overloaded C++ Classes
======================================================================================================================*/

// When combining virtual methods with inheritance, you need to be sure to provide an override for each method
// for which you want to allow overrides from derived python classes. */

template <class AnimalBase = Animal> class PyAnimal : public AnimalBase {
public:
	using AnimalBase::AnimalBase; // inherit constructors
	std::string go(int n_times) override {
		PYBIND11_OVERLOAD_PURE(std::string, AnimalBase, go, n_times);
	}
	std::string name() override {
		PYBIND11_OVERLOAD(std::string, AnimalBase, name, );
	}
};

template <class DogBase = Dog> class PyDog : public PyAnimal<DogBase> {
public:
	using PyAnimal<DogBase>::PyAnimal; // inherit constructors
	PyExample(Dog &&base) : Dog(std::move(base)) {}

 // Override PyAnimal's pure virtual go() with a non-pure one:
	std::string go(int n_times) override {
		PYBIND11_OVERLOAD(std::string, DogBase, go, n_times);
	}
	std::string bark() override { PYBIND11_OVERLOAD(std::string, DogBase, bark, ); }
};

/*######################################################################################################################
Registered Python Classes
======================================================================================================================*/

PYBIND11_MODULE(chapter8_1, m) {
	// Declare the class of 'Animal'
	py::class_<Animal, PyAnimal<>> animal(m, "Animal"); 
	// Declare the class of 'Dog'. Note since the default template argument of 'PyDog' is 'Dog', we can use the below
	// command instead of "py::class_<Dog, PyDog<Dog>> dog(m, "Dog");"
	py::class_<Dog, Animal, PyDog<Dog>> dog(m, "Dog");
	// Declare the class of 'Husky'.
	py::class_<Husky, Dog, PyDog<Husky>> husky(m, "Husky");

	animal
		.def(py::init<double>())
		.def(py::init<>())
		.def("go", &Animal::go)
		.def("name", &Animal::name)
		.def("check_hp", &Animal::check_hp)
		.def_readwrite("hp", &Animal::hp);
		
	dog
		// The create function can be used as it is or transferred into a constructor.
		// Both the two definitions can construct an instance of <class 'Dog'>.
		.def(py::init(&Dog::create)) // a cosntrcutor defined by a factory function
		.def("create", &Dog::create) // a factory function

		.def(py::init<>())
		.def("bark", &Dog::bark);

	husky.def(py::init<>());
		
	m.def("call_go", &call_go);
}
