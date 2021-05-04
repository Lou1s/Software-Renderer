#pragma once

#define PI 3.14159265358979323846264338327950288

#define degreesToRadians(angleDegrees) ((angleDegrees) * PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / PI)

#include <array>
#include <iostream>
template <class T>
class Vec2 {
private:
	T _xy[2];
public:
	Vec2() : _xy{ 0.0, 0.0 } {}
	Vec2(T x, T y) : _xy{ x, y } {}
	Vec2(const Vec2& vec) : _xy{ vec._xy[0] , vec._xy[1] } {}

	T getX() const { return _xy[0]; }
	T getY() const { return _xy[1]; }

	void setX(const T x) { _xy[0] = x; }
	void setY(const T y) { _xy[1] = y; }

	Vec2 operator+ (const Vec2& vec) const {
		return Vec3(
			_xy[0] + vec._xy[0],
			_xy[1] + vec._xy[1]
			);
	}
	Vec2 operator- (const Vec2& vec) const {
		return Vec2(
			_xy[0] - vec._xy[0],
			_xy[1] - vec._xy[1]
			);
	}
	Vec2 operator* (T n) const {
		return Vec2(
			_xy[0] * n,
			_xy[1] * n
			);
	}
		Vec2 operator/ (T n) const {
		return Vec2(
			_xy[0] / n,
			_xy[1] / n
		);
	}

	void operator/= (T n) {
		_xy[0] /= n;
		_xy[1] /= n;
	}
	void operator*= (T n) {
		_xy[0] *= n;
		_xy[1] *= n;
	}
	void operator-= (const Vec2& vec) {
		_xy[0] -= vec._xy[0];
		_xy[1] -= vec._xy[1];
	}
	void operator+= (const Vec2& vec) {
		_xy[0] += vec._xy[0];
		_xy[1] += vec._xy[1];
	}
	bool operator == (const Vec2& vec) const {
		return _xy == vec._xy;
	}

	Vec2& normalise() {
		T ln = length();
		if (ln > 0)
			*this /= len
			return *this;
	}
	T length() const {
		return(std::sqrt(_xy[0] * _xy[0] + _xy[1] * _xy[1]));
	}
	T dot(const Vec2& vec) {
		return _xy[0] * vec._xy[0] + _xy[1] * vec._xy[1];
	}
	T distance(const Vec2& vec) const {
		dist_x = _xy[0] - vec._xy[0];
		dist_y = _xy[1] - vec._xy[1];
		return std::sqrt(dist_x * dist_x + dist_y * dist_y);
	}
	T cross(const Vec2& vec) const {
		return _xy[0] * vec._xy[1] - _xy[1] * vec._xy[0];
	}
	void rotate(const double& angle) {
		float rad_angle = degreesToRadians(angle);
		float x = _xy[0];
		float y = _xy[1];
		_xy[0] = x * cos(rad_angle) - y * sin(rad_angle);
		_xy[1] = x * sin(rad_angle) + y * cos(rad_angle);

	}

	void integise() {
		_xy[0] = int(_xy[0]);
		_xy[1] = int(_xy[1]);
	}

};

typedef Vec2<float> Vector2;
typedef Vec2<double> Vector2_d;
typedef Vec2<int> Vector2_I;

//forward declaration of vec4 for use in a vec3 constructor
template <class T>
class Vec4;

template <class T>
class Vec3 {
private:
	T _xyz[3];
public:
	Vec3() : _xyz{ 0.0, 0.0, 0.0 } {}
	Vec3(T x, T y, T z) : _xyz{ x, y, z } {}
	Vec3(const Vec3<T>& vec) : _xyz{ vec.getX(), vec.getY(), vec.getZ() } {}
	Vec3(const Vec4<T>& vec) : _xyz{ vec.getX(), vec.getY(), vec.getZ() } {}

	T getX() const { return _xyz[0]; }
	T getY() const { return _xyz[1]; }
	T getZ() const { return _xyz[2]; }

	void setX(const T x) { _xyz[0] = x; }
	void setY(const T y) { _xyz[1] = y; }
	void setZ(const T z) { _xyz[2] = z; }

	void set(const float& x, const float& y, const float& z) { setX(x); setY(y); setZ(z); }

	Vec3 operator+ (const Vec3& vec) const {
		return Vec3(
			_xyz[0] + vec._xyz[0],
			_xyz[1] + vec._xyz[1],
			_xyz[2] + vec._xyz[2],
			);
	}
	Vec3 operator- (const Vec3& vec) const {
		return Vec3(
			_xyz[0] - vec._xyz[0],
			_xyz[1] - vec._xyz[1],
			_xyz[2] - vec._xyz[2]
			);
	}
	Vec3 operator* (T n) const {
		return Vec3(
			_xyz[0] * n,
			_xyz[1] * n,
			_xyz[2] * n
		);
	}

	Vec3 operator/ (T n) const {
		return Vec3(
			_xyz[0] / n,
			_xyz[1] / n,
			_xyz[2] / n
		);
	}

	void operator/= (T n) {
		_xyz[0] /= n;
		_xyz[1] /= n;
		_xyz[2] /= n;
	}
	void operator*= (T n) {
		_xyz[0] *= n;
		_xyz[1] *= n;
		_xyz[2] *= n;
	}
	void operator-= (const Vec3& vec) {
		_xyz[0] -= vec._xyz[0];
		_xyz[1] -= vec._xyz[1];
		_xyz[2] -= vec._xyz[2];
	}
	void operator+= (const Vec3& vec) {
		_xyz[0] += vec._xyz[0];
		_xyz[1] += vec._xyz[1];
		_xyz[2] += vec._xyz[2];
	}
	bool operator == (const Vec3& vec) const {
		return _xyz == vec._xyz;
	}

	Vec3& normalise() {
		T ln = length();
		if (ln > 0)
			*this /= ln;
			return *this;
	}
	T length() const {
		return(std::sqrt(_xyz[0] * _xyz[0] + _xyz[1] * _xyz[1] + _xyz[2] * _xyz[2]));
	}
	T dot(const Vec3& vec) const {
		return (_xyz[0] * vec._xyz[0]) + (_xyz[1] * vec._xyz[1]) + (_xyz[2] * vec._xyz[2]);
	}
	T distance(const Vec3& vec) const {
		dist_x = _xyz[0] - vec._xyz[0];
		dist_y = _xyz[1] - vec._xyz[1];
		dist_z = _xyz[2] - vec._xyz[2];
		return std::sqrt(dist_x * dist_x + dist_y * dist_y + dist_z + dist_z);
	}
	Vec3 cross(const Vec3& vec) const {
		return Vec3(
			_xyz[1] * vec._xyz[2] - _xyz[2] * vec._xyz[1],
			_xyz[2] * vec._xyz[0] - _xyz[0] * vec._xyz[2],
			_xyz[0] * vec._xyz[1] - _xyz[1] * vec._xyz[0]
		);
	}

	void rotateInPlace(const Vec3& rot) {
		float roll = rot.getX();
		float pitch = rot.getY();
		float yaw = rot.getZ();

		rotateXInPlace(roll);
		rotateYInPlace(pitch);
		rotateZInPlace(yaw);
	}

	Vec3 rotate(const Vec3& rot) {
		Vec3<T> result(*this);
		result.rotateInPlace(rot);
		return result;
	}

	void rotateZInPlace(const float& angle) {
		float rad_angle = degreesToRadians(angle);
		float x = _xyz[0];
		float y = _xyz[1];
		_xyz[0] = x * cos(rad_angle) - y * sin(rad_angle);
		_xyz[1] = x * sin(rad_angle) + y * cos(rad_angle);

	}
	Vec3 rotateZ(const float& rot) {
		Vec3 result(*this);
		result.rotateZInPlace(rot);
		return result;
	}

	void rotateYInPlace(const float& angle) {
		float rad_angle = degreesToRadians(angle);
		float x = _xyz[0];
		float z = _xyz[2];
		_xyz[0] = x * cos(rad_angle) - z * sin(rad_angle);
		_xyz[2] = x * sin(rad_angle) + z * cos(rad_angle);

	}
	Vec3 rotateY(const float& rot) {
		Vec3 result(*this);
		result.rotateYInPlace(rot);
		return result;
	}

	void rotateXInPlace(const float& angle) {
		float rad_angle = degreesToRadians(angle);
		float y = _xyz[1];
		float z = _xyz[2];
		_xyz[1] = y * cos(rad_angle) - z * sin(rad_angle);
		_xyz[2] = y * sin(rad_angle) + z * cos(rad_angle);

	}
	Vec3 rotateX(const float &rot) {
		Vec3 result(*this);
		result.rotateXInPlace(rot);
		return result;
	}

};

template <class T>
class Matrix2 {
private:
	T _data[4];
public:
	Matrix2() { for (size_t i = 0; i < 4; i++) { _data[i] = 0.0; } }
	Matrix2(T m00, T m01, T m10, T m11) : _data{ m00, m01, m10, m11 } {}
	T& operator()(const int& row, const int& col) { return _data[row * 2 + col]; }
	
	Matrix2 operator*(const Matrix2& rhs) const {
		Matrix2 result;
		for (size_t i = 0; i < 2; i++) {
			for (size_t j = 0; j < 2; j++) {
				for (size_t k = 0; k < 2; k++) {
					result(i, j) += *this(i, k) * rhs(k, j);
				}
			}
		}
	}
	friend std::ostream& operator<< (std::ostream& out, const Matrix2<T>& mat) {
		out << mat._data[0] << ", " << mat._data[1] << std::endl << mat._data[2] << "," << mat._data[3] << std::endl;
		return out;
	}

	Vec2<T> operator*(const Vec2& rhs) const {
		Vec2<T> result;
		result.set(rhs.getX() * _data[0] + rhs.getY() * _data[1], rhs.getX() * _data[2] + rhs.getY() * _data[3])
			return result;
	}

	void setRot(const T& angle) {
		T ang = degreesToRadians(angle);
		_data[0] = cos(ang);
		_data[1] = -sin(ang);
		_data[2] = sin(ang);
		_data[3] = cos(ang);
	}
};
template <class T>
class Vec4 {
private:
	T _xyzw[4];
public:
	//this whole class needs to be fixed up to diff between points and vectors.
	Vec4() : _xyzw{ 0.0, 0.0, 0.0, 1.0 } {}
	Vec4(T x, T y, T z, T w) : _xyzw{ x, y, z, w } {}
	Vec4(const Vec4<T>& vec) : _xyzw{ vec.getX(), vec.getY(), vec.getZ(), vec.getW() } {}
	Vec4(const Vec3<T>& vec) : _xyzw{ vec.getX(), vec.getY(), vec.getZ(), 1.0 } {}

	T getX() const { return _xyzw[0]; }
	T getY() const { return _xyzw[1]; }
	T getZ() const { return _xyzw[2]; }
	T getW() const { return _xyzw[2]; }

	void setX(const T x) { _xyzw[0] = x; }
	void setY(const T y) { _xyzw[1] = y; }
	void setZ(const T z) { _xyzw[2] = z; }
	void setW(const T w) { _xyzw[2] = w; }

	void set(const float& x, const float& y, const float& z) { setX(x); setY(y); setZ(z); setW(w); }

	Vec4 operator+ (const Vec4& vec) const {
		return Vec4(
			_xyzw[0] + vec._xyzw[0],
			_xyzw[1] + vec._xyzw[1],
			_xyzw[2] + vec._xyzw[2],
			_xyzw[3] + vec._xyzw[3]
			);
	}
	Vec4 operator- (const Vec4& vec) const {
		return Vec4(
			_xyzw[0] - vec._xyzw[0],
			_xyzw[1] - vec._xyzw[1],
			_xyzw[2] - vec._xyzw[2],
			_xyzw[3] - vec._xyzw[3]
		);
	}
	Vec4 operator* (T n) const {
		return Vec4(
			_xyzw[0] * n,
			_xyzw[1] * n,
			_xyzw[2] * n,
			_xyzw[3]
		);
	}

	Vec4 operator/ (T n) const {
		return Vec4(
			_xyzw[0] / n,
			_xyzw[1] / n,
			_xyzw[2] / n,
			_xyzw[3]
		);
	}

	void operator/= (T n) {
		_xyzw[0] /= n;
		_xyzw[1] /= n;
		_xyzw[2] /= n;
	}
	void operator*= (T n) {
		_xyzw[0] *= n;
		_xyzw[1] *= n;
		_xyzw[2] *= n;
	}
	void operator-= (const Vec4& vec) {
		_xyzw[0] -= vec._xyzw[0];
		_xyzw[1] -= vec._xyzw[1];
		_xyzw[2] -= vec._xyzw[2];
	}
	void operator+= (const Vec4& vec) {
		_xyzw[0] += vec._xyzw[0];
		_xyzw[1] += vec._xyzw[1];
		_xyzw[2] += vec._xyzw[2];
	}
	bool operator == (const Vec4& vec) const {
		return _xyz == vec._xyz;
	}

	Vec4& normalise() {
		T ln = length();
		if (ln > 0)
			*this /= ln;
		return *this;
	}
	T length() const {
		return(std::sqrt(_xyz[0] * _xyz[0] + _xyz[1] * _xyz[1] + _xyz[2] * _xyz[2]));
	}
	T dot(const Vec4& vec) const {
		return (_xyz[0] * vec._xyz[0]) + (_xyz[1] * vec._xyz[1]) + (_xyz[2] * vec._xyz[2]);
	}
	T distance(const Vec4& vec) const {
		dist_x = _xyz[0] - vec._xyz[0];
		dist_y = _xyz[1] - vec._xyz[1];
		dist_z = _xyz[2] - vec._xyz[2];
		return std::sqrt(dist_x * dist_x + dist_y * dist_y + dist_z + dist_z);
	}
	Vec3<T> cross(const Vec4& vec) const {
		return Vec3<T>(
			_xyzw[1] * vec._xyzw[2] - _xyzw[2] * vec._xyzw[1],
			_xyzw[2] * vec._xyzw[0] - _xyzw[0] * vec._xyzw[2],
			_xyzw[0] * vec._xyzw[1] - _xyzw[1] * vec._xyzw[0]
			);
	}

	T& operator[](const int& i) { return _xyzw[i]; }
	T operator[](const int& i) const { return _xyzw[i]; }

};

template <class T>
class Matrix4 {
private:
	T _data[16];
public:
	Matrix4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33) : _data{ m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33 } {}
	Matrix4() { 
		makeIdentity();
	}
	void makeIdentity() {
		for (size_t i = 0; i < 16; i++) {
			_data[i] = 0.0;
		}
		(*this)(0, 0) = 1.0;
		(*this)(1, 1) = 1.0;
		(*this)(2, 2) = 1.0;
		(*this)(3, 3) = 1.0;
	}
	T& operator()(const int& row, const int& col) { return _data[row * 4 + col]; }
	T operator()(const int& row, const int& col) const { return _data[row * 4 + col]; }
	
	Matrix4 operator*(const Matrix4& rhs) {
		Matrix4 result;
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				for (size_t k = 0; k < 4; k++) {
					result(i, j) += (*this)(i, k) * rhs(k, j);
				}
			}
		}
		return result;
	}

	friend std::ostream& operator<< (std::ostream& out, const Matrix4<T>& mat) {
		for (size_t i = 0; i < 4; i++) {
			for (size_t j = 0; j < 4; j++) {
				out << mat._data[i + j] << " ";
			}
			out << std::endl;
		}
		return out;
	}

	friend Vec4<T> operator*(const Matrix4& mat, const Vec4<T>& vec) {
		Vec4<T> result;
		for (size_t i = 0; i < 4; i++) {
			result[i] = 0.0;
			for (size_t j = 0; j < 4; j++) {
				result[i] += mat(i, j) * vec[j];
			}
		}
		return result;
	}
	
	void setScale(T x, T y, T z) {
		(*this)(0,0) = x;
		(*this)(1,1) = y;
		(*this)(2,2) = z;
	}

	void addScale(T x, T y, T z) {
		(*this)(0, 0) *= x;
		(*this)(1, 1) *= y;
		(*this)(2, 2) *= z;
	}

	void setTranslation(T x, T y, T z) {
		(*this)(0, 3) = x;
		(*this)(1, 3) = y;
		(*this)(2, 3) = z;
	}

	void addTranslation(T x, T y, T z) {
		(*this)(0, 3) += x;
		(*this)(1, 3) += y;
		(*this)(2, 3) += z;
		std::cout << (*this) << std::endl;
	}

	void setRotation(T x, T y, T z) {
		T x_ang, y_ang, z_ang;
		x_ang = degreesToRadians(x);
		y_ang = degreesToRadians(y);
		z_ang = degreesToRadians(z);
	}

	void addRotation(T x, T y, T z) {
		T x_ang, y_ang, z_ang;
		x_ang = degreesToRadians(x);
		y_ang = degreesToRadians(y);
		z_ang = degreesToRadians(z);
	}

};



typedef Vec4<float> Vector4;
typedef Matrix4<float> Mat4;
typedef Matrix2<float> Mat2;
typedef Vec3<float> Vector3;
typedef Vec3<double> Vector3_d;