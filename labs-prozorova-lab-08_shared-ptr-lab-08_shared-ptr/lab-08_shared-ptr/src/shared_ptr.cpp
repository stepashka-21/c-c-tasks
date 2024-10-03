#include "shared_ptr.hpp"
	/**
	 * Получает объект по сырому указателю во владение.
	 * Передача того же указателя во владение кому либо ещё — неопределённое поведение.
	 */
shared_ptr::shared_ptr(Matrix *obj) { // ???
    storage_ = new Storage(obj);
}
	/**
	 * Строит копию умного указателя, разделяя владение с оригиналом.
	 */
shared_ptr::shared_ptr(const shared_ptr& other) : storage_(other.storage_) {
    storage_->incr();
}
	/**
	 * Присваивает умному указателю новое значение, корректно меняя владение с одного объекта на другой.
	 */
shared_ptr& shared_ptr::operator=(shared_ptr other) {
    std::swap(storage_, other.storage_);
    return *this;
}

shared_ptr::~shared_ptr() {
    storage_->decr();
    if (storage_->getCounter() == 0) {
    	delete storage_;
	}
}
	/**
	 * Возвращает сырой указатель для несовместимого кода.
	 */
Matrix* shared_ptr::ptr() const {
    return storage_->getObject();
}
	/**
	 * Проверка на nullptr.
	 */
bool shared_ptr::isNull() const {
    return storage_->getObject() == nullptr;
}
	/**
	 * Присваивает умному указателю новый для владения.
	 */
void shared_ptr::reset(Matrix* obj) {
    *this = shared_ptr(obj);
}

Matrix* shared_ptr::operator->() const {
    return storage_->getObject();
}
Matrix& shared_ptr::operator*() const {
    return *storage_->getObject();
}

shared_ptr::Storage::Storage(Matrix* mtx) : data_(mtx), ref_count_(1) {}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ref_count_++;
}

void shared_ptr::Storage::decr() {
    ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}
Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}
