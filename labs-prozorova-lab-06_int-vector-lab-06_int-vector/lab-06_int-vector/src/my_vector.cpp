#include "my_vector.hpp"

MyVector::MyVector() : MyVector(2) {}

MyVector::MyVector(std::size_t init_capacity) : _size(0), _capacity(init_capacity), _data(new int[init_capacity]) {}

MyVector::~MyVector() {
  delete[] _data;
}

std::size_t MyVector::size() const {
  return _size;
}

std::size_t MyVector::capacity() const {
  return _capacity;
}

void MyVector::set(std::size_t index, int value) {
  assert (index < _size);
  _data[index] = value;
}

int MyVector::get(std::size_t index) const {
  assert (index < _size);
  return _data[index];
}

void MyVector::reserve(std::size_t new_capacity) {
  if (new_capacity <= _capacity) { 
    return;
  }

  MyVector other(new_capacity);
  std::copy(_data, _data + _size, other._data);

  using std::swap;
  swap(_data, other._data);
  swap(_capacity, new_capacity);
}

void MyVector::resize(std::size_t new_size) {
  if (new_size > _capacity) {
    reserve(std::max(new_size, 2 * _capacity));
  }

  for (std::size_t i = _size; i < new_size; ++i) {
    _data[i] = 0;
  }
  _size = new_size;
}

void MyVector::push_back(int value) {
  if (_size >= _capacity) {
    reserve(2 * _capacity);
  }
  _data[_size++] = value;
}

void MyVector::insert(std::size_t index, int value) {
  if (index > _size) {
    return;
  }

  if (_size >= _capacity) {
    reserve(2 * _capacity);
  }

  std::move(_data + index, _data + _size, _data + index + 1);
  _data[index] = value;
  _size++;
}

void MyVector::erase(std::size_t index) {
  assert (index < _size);
  std::move(_data + index + 1, _data + _size, _data + index);
  _size--;
}

MyVector::MyVector(const MyVector &other) 
  : _size(other._size), 
  _capacity(other._capacity), 
  _data(new int[other._capacity]) {
  std::copy(other._data, other._data + _size, _data);
}

MyVector &MyVector::operator=(MyVector other) {
  using std::swap;
  swap(_size, other._size);
  swap(_capacity, other._capacity);
  swap(_data, other._data);
  return *this;
}
