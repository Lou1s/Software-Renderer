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

template <class T>
class Vec3 {
private:
	T _xyz[3];
public:
	Vec3() : _xyz{ 0.0, 0.0, 0.0 } {}
	Vec3(T x, T y, T z) : _xyz{ x, y, z } {}
	Vec3(const Vec3<T>& vec) : _xyz{ vec.getX(), vec.getY(), vec.getZ() } {}

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
};


template <class T>
class Matrix3 {
private:
	T _data[9];
public:
	Matrix3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22) : _data{ m00, m01, m02, m10, m11, m12, m20, m21, m22 } {}
	Matrix3() { 
		for (size_t i = 0; i < 9; i++) { _data[i] = 0.0; }
	}
	T& operator()(const int& row, const int& col) { return _data[row * 3 + col]; }
	T operator()(const int& row, const int& col) const { return _data[row * 3 + col]; }
	Matrix3 operator*(const Matrix3& rhs) const {
		Matrix3 result;
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3; j++) {
				for (size_t k = 0; k < 3; k++) {
					result(i, j) += (*this)(i, k) * rhs(k, j);
				}
			}
		}
		return result;
	}

	friend std::ostream& operator<< (std::ostream& out, const Matrix3<T>& mat) {
		out << mat._data[0] << ", " << mat._data[1] << ", " << mat._data[2] << "," << std::endl << mat._data[3] << ", " << mat._data[4] << ", " << mat._data[5] << std::endl << mat._data[6] << ", " << mat._data[7] << ", " << mat._data[8] << std::endl;
		return out;
	}

	
};


typedef Matrix3<float> Mat3;
typedef Matrix2<float> Mat2;
typedef Vec3<float> Vector3;
typedef Vec3<double> Vector3_d;