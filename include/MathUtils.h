#pragma once

#define PI 3.14159265358979323846264338327950288

#define degreesToRadians(angleDegrees) ((angleDegrees) * PI / 180.0)
#define radiansToDegrees(angleRadians) ((angleRadians) * 180.0 / PI)

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

};

typedef Vec2<float> Vector2;
typedef Vec2<double> Vector2_d;

template <class T>
class Vec3 {
private:
	T _xyz[3];
public:
	Vec3() : _xyz{ 0.0, 0.0, 0.0 } {}
	Vec3(T x, T y, T z) : _xyz{ x, y, z } {}
	Vec3(const Vec3& vec) : _xyz{ vec._xyz[0], vec._xyz[1], vec._xyz[2] } {}

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
			*this /= len
			return *this;
	}
	T length() const {
		return(std::sqrt(_xyz[0] * _xyz[0] + _xyz[1] * _xyz[1] + _xyz[2] * _xyz[2]));
	}
	T dot(const Vec3& vec) const {
		return _xyz[0] * vec._xyz[0] + _xyz[1] * vec._xyz[1] + _xyz[2] * vec._xyz[2];
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

	void rotate(const Vec3& rot) {
		float roll = rot.getX();
		float pitch = rot.getY();
		float yaw = rot.getZ();

		rotateX(roll);
		rotateY(pitch);
		rotateZ(yaw);
	}

	void rotateZ(const float& angle) {
		float rad_angle = degreesToRadians(angle);
		float x = _xyz[0];
		float y = _xyz[1];
		_xyz[0] = x * cos(rad_angle) - y * sin(rad_angle);
		_xyz[1] = x * sin(rad_angle) + y * cos(rad_angle);

	}

	void rotateY(const float& angle) {
		float rad_angle = degreesToRadians(angle);
		float x = _xyz[0];
		float z = _xyz[2];
		_xyz[0] = x * cos(rad_angle) - z * sin(rad_angle);
		_xyz[2] = x * sin(rad_angle) + z * cos(rad_angle);

	}

	void rotateX(const float& angle) {
		float rad_angle = degreesToRadians(angle);
		float y = _xyz[1];
		float z = _xyz[2];
		_xyz[1] = y * cos(rad_angle) - z * sin(rad_angle);
		_xyz[2] = y * sin(rad_angle) + z * cos(rad_angle);

	}

};

typedef Vec3<float> Vector3;
typedef Vec3<double> Vector3_d;