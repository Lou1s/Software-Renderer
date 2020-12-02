#pragma once

#include <cmath>

template <class T>
class Vec2 {
private:
	T _xy[2];
public:
	Vec2() : _xy[0](0), _xy[1](0) {}
	Vec2(T x, T y) : _xy[0](x), _xy[1](y) {}
	Vec2(const Vec2& vec) : _xy[0](vec._xy[0]), _xy[1](vec._xy[1]) {}

	T getX() const { return _xy[0]; }
	T getY() const { return _xy[1]; }

	void SetX(const T x) { _xy[0] = x; }
	void SetY(const T y) { _xy[1] = y; }
	
	Vec2 operator+ (const Vec2& vec) const {
		return Vec3(
			_xy[0] + vec._xy[0],
			_xy[1] + vec._xy[1],
			);
	}
	Vec2 operator- (const Vec2& vec) const {
		return Vec2(
			_xy[0] - vec._xy[0],
			_xy[1] - vec._xy[1],
			);
	}
	Vec2 operator* (T n) const {
		return Vec2(
			_xy[0] * n,
			_xy[1] * n,
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

	Vec2& Normalise() {
		T ln = Length();
		if (ln > 0)
			*this /= len
			return *this;
	}
	T Length() const {
		return(std::sqrt(_xy[0] * _xy[0] + _xy[1] * _xy[1]));
	}
	T Dot(const Vec2& vec) {
		return _xy[0] * vec._xy[0] + _xy[1] * vec._xy[1];
	}
	T Distance(const Vec2& vec) const {
		dist_x = _xy[0] - vec._xy[0];
		dist_y = _xy[1] - vec._xy[1];
		return std::sqrt(dist_x * dist_x + dist_y * dist_y);
	}
	T Cross(const Vec2& vec) const {
		return _xy[0] * vec._xy[1] - _xy[1] * vec._xy[0];
	}
	
};

typedef Vec2<float> Vector2;
typedef Vec2<double> Vector2_d;

template <class T>
class Vec3 {
private:
	T _xyz[3];
public:
	Vec3() : _xy[0](0), _xy[1](0), _xyz[2](3) {}
	Vec3(T x, T y, T z) : _xyz[0](x), _xyz[1](y), _xyz[2](z) {}
	Vec3(const Vec2& vec) : _xyz[0](vec._xyz[0]), _xyz[1](vec._xyz[1]), _xyz[2](vec._xyz[2]) {}

	T getX() const { return _xyz[0]; }
	T getY() const { return _xyz[1]; }
	T getZ() const { return _xyz[2]; }

	void SetX(const T x) { _xyz[0] = x; }
	void SetY(const T y) { _xyz[1] = y; }
	void SetZ(const T z) { _xyz[2] = z; }

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
			_xyz[2] - vec._xyz[2],
			);
	}
	Vec3 operator* (T n) const {
		return Vec3(
			_xyz[0] * n,
			_xyz[1] * n,
			_xyz[2] * n
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

	Vec3& Normalise() {
		T ln = Length();
		if (ln > 0)
			*this /= len
			return *this;
	}
	T Length() const {
		return(std::sqrt(_xyz[0] * _xyz[0] + _xyz[1] * _xyz[1] + _xyz[2] * _xyz[2]));
	}
	T Dot(const Vec3& vec) const {
		return _xyz[0] * vec._xyz[0] + _xyz[1] * vec._xyz[1] + _xyz[2] * vec._xyz[2];
	}
	T Distance(const Vec3& vec) const {
		dist_x = _xyz[0] - vec._xyz[0];
		dist_y = _xyz[1] - vec._xyz[1];
		dist_z = _xyz[2] - vec._xyz[2];
		return std::sqrt(dist_x * dist_x + dist_y * dist_y + dist_z + dist_z);
	}
	Vec3 Cross(const Vec3& vec) const {
		return Vec3(
			_xyz[1] * vec._xyz[2] - _xyz[2] * vec._xyz[1],
			_xyz[3] * vec._xyz[1] - _xyz[1] * vec._xyz[3],
			_xyz[1] * vec._xyz[2] - _xyz[2] * vec._xyz[1]
		);
	}


};

typedef Vec3<float> Vector3;
typedef Vec3<double> Vector3_d;