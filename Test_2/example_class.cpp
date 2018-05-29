#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Pet {

public:
	// Constructor
	Pet(const std::string &name, const std::string &nick_name = "Sweet") : name(name), nick_name(nick_name) {}
	Pet() : Pet("My pet", "Sweet") {}
	
	// Set the name of a pet
	void setName(const std::string &name_) { name = name_; }
	// Get the name of a pet
	const std::string &getName() const { return name; }

	// Set the nick name of a pet
	void setNickName(const std::string &name_) { nick_name = name_; }
	// Get the nick name of a pet
	const std::string &getNickName() const { return nick_name; }

	// The name of the pet
	std::string name;

private:
	// The nick name of the pet
	std::string nick_name;

};

PYBIND11_MODULE(example_class, m) {
	py::class_<Pet>(m, "Pet")
		// Constructor
		.def(py::init<const std::string &, const std::string &>())
		.def(py::init<const std::string &>())
		.def(py::init<>())

		.def_readwrite("name", &Pet::name)
		.def("setName", &Pet::setName)
		.def("getName", &Pet::getName)

		.def_property("nick_name", &Pet::getNickName, &Pet::setNickName)
		.def("setNickName", &Pet::setNickName)
		.def("getNickName", &Pet::getNickName)

		.def("__repr__",
			[](const Pet &a) {
				return "<example_class.Pet named '" + a.name + "'>";
			}
		);
}
