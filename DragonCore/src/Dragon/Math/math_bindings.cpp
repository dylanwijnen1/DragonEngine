#include <pybind11/embed.h>
#include <pybind11/operators.h>

namespace py = pybind11;

#include <Dragon/Math/Math.h>

void init_math(py::module& m)
{
	//using RectF = mathfu::Rect<float>;
	//using Rect = mathfu::Rect<int>;

	//using Vector2f = mathfu::Vector<float, 2>;
	//using Vector3f = mathfu::Vector<float, 3>;
	//using Vector4f = mathfu::Vector<float, 4>;

	//using Vector2 = mathfu::Vector<int, 2>;
	//using Vector3 = mathfu::Vector<int, 3>;
	//using Vector4 = mathfu::Vector<int, 4>;

	//using Matrix3 = mathfu::Matrix<float, 3, 3>;
	//using Matrix4 = mathfu::Matrix<float, 4, 4>;

	//using Transform = mathfu::AffineTransform;

	//template<int Rows, int Columns>
	//using Matrix = mathfu::Matrix<float, Rows, Columns>;

	py::class_<Vector2f> v2f(m, "Vector2f");
	v2f
		.def(py::init<>())
		.def(py::init<float, float>())
		.def(py::self + py::self)
		.def(py::self += py::self)
		.def(py::self *= float())
		.def(float() * py::self)
		.def(py::self * float())

		.def_readwrite("x", &Vector2f::x)
		.def_readwrite("y", &Vector2f::x)

		.def("normalize", &Vector2f::Normalize)

		.def_static("lerp", &Vector2f::Lerp)
		.def_static("distanceSquared", &Vector2f::DistanceSquared)
		.def_static("distance", &Vector2f::Distance)
		.def_static("dot", &Vector2f::DotProduct)
		.def_static("angle", &Vector2f::Angle)

		.def("__repr__", [] (const Vector2f & vec) {
			return "<dragon.Vector2f x=" + std::to_string(vec.x) + ", y=" + std::to_string(vec.y) + " >";
		});
}