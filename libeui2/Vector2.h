#pragma once
namespace EUI2 {
	//�����࣬ӵ������ֵ��x,y������������ʾ���ꡢ��С��ֵ
	template<typename T>
	class Vector2 {
	public:
		T x, y;
		Vector2() :x(T()), y(T()) {}
		Vector2(const T& _x, const T& _y) :x(_x), y(_y) {}
		Vector2(const Vector2& vec) :x(vec.x), y(vec.y) {}
		~Vector2() = default;
		bool operator==(const Vector2& vec)const noexcept { return x == vec.x && y == vec.y; }
		bool operator!=(const Vector2& vec)const noexcept { return x != vec.x || y != vec.y; }
		const Vector2 operator=(const Vector2& vec)noexcept { x = vec.x, y = vec.y; return *this; }
		const Vector2 operator+(const Vector2& vec)const noexcept { return Vector2(x + vec.x, y + vec.y); }
		const Vector2 operator-(const Vector2& vec)const noexcept { return Vector2(x - vec.x, y - vec.y); }
		Vector2& operator+=(const Vector2& vec)noexcept { x += vec.x, y += vec.y; }
		Vector2& operator-=(const Vector2& vec)noexcept { x -= vec.x, y -= vec.y; }
	};
	typedef Vector2<int>		Vector2i;
	typedef Vector2<unsigned>	Vector2u;
	typedef Vector2<float>		Vector2f;
	typedef Vector2<long long>	Vector2ll;
	typedef Vector2<double>		Vector2d;
}