#include <pybind11/pybind11.h>

namespace py = pybind11;

struct Response
{
	int status;
	std::string reason;
	std::string text;
	
	Response(int status,
		std::string reason,
		std::string text = ""):
		status(status), reason(std::move(reason)), text(std::move(text))
	{}
	
	Response() : Response(status = 200, reason = "OK") 
	{}

	bool ok() const {
		return status >= 200 && status < 400;
	}

	friend bool operator==(const Response & r1,
		const Response & r2) {
		return r1.status == r2.status
			&& r1.reason == r2.reason
			&& r1.text == r2.text;
	}
};

PYBIND11_MODULE(example_class, m) {
	py::class_<Response>(m, "Response")
		.def(py::init<>())
		.def(py::init<int, std::string>())
		.def(py::init<int, std::string, std::string>())
		.def_readonly("status", &Response::status)
		.def_readonly("reason", &Response::reason)
		.def_readonly("text", &Response::text)
		.def_property_readonly("ok", &Response::ok)
		.def("__repr__", [](const Response & self) {
			return std::string() 
				+ "<" + std::to_string(self.status) 
				+ ": " + self.reason + ">"; })
		//.def(py::self == py::self);
		//can be the substitute of the below for simplicity*/
		.def("__eq__", [](const Response & self,
		const Response & other) {return self == other; }, 
		py::is_operator());
}