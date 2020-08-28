#pragma once
#include <functional>

enum class PropertyMode { Read, Write, ReadWrite };

template <typename T, PropertyMode Mode>
class Property {
	Property() = delete;
	Property(Property&) = delete;
	Property(Property&&) = delete;
	Property& operator=(Property&) = delete;
};

template <typename T>
class Property<T, PropertyMode::Read> {
   private:
	std::function<T()> m_getter;

   public:
	Property() = default;
	void Init(T& value) {
		m_getter = [&]() { return value; };
	}
	void Init(std::function<T()> getter) {
		m_getter = getter;
	}

	operator T() {
		return m_getter();
	}
	T operator*() {
		return m_getter();
	}
	T operator->() {
		return m_getter();
	}
};

template <typename T>
class Property<T, PropertyMode::Write> {
   private:
	std::function<void(const T&)> m_writer;

   public:
	Property() = default;
	void Init(T& value) {
		m_writer = [&](const T& _value) { value = _value; };
	}
	void Init(std::function<void(const T&)> writer) {
		m_writer = writer;
	}

	void operator=(const T& value) {
		m_writer(value);
	}
};

template <typename T>
class Property<T, PropertyMode::ReadWrite> {
   private:
	std::function<T()> m_getter;
	std::function<void(const T&)> m_writer;

   public:
	Property() = default;

	void Init(T& value) {
		m_getter = [&]() { return value; };
		m_writer = [&](const T& _value) { value = _value; };
	}
	void Init(T& value, std::function<void(const T&)> writer) {
		m_getter = [&]() { return value; };
		m_writer = writer;
	}
	void Init(std::function<T()> getter, T& value) {
		m_getter = getter;
		m_writer = [&](const T& _value) { value = _value; };
	}
	void Init(std::function<T()> getter, std::function<void(const T&)> writer) {
		m_getter = getter;
		m_writer = writer;
	}
	operator T() {
		return m_getter();
	}
	T operator*() {
		return m_getter();
	}
	T operator->() {
		return m_getter();
	}

	Property& operator=(const T& value) {
		m_writer(value);
		return *this;
	}
};