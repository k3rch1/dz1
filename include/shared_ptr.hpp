#pragma once
#include <cstddef>
#include <type_traits>

template<class T>
class shared_ptr {
private:
    T* ptr_;
    size_t* ref_count;

    template<class U>
    friend class shared_ptr;

public:
    explicit shared_ptr(T* ptr = nullptr);

    ~shared_ptr();

    shared_ptr(const shared_ptr& other);
    shared_ptr(shared_ptr&& other) noexcept;

    shared_ptr& operator=(const shared_ptr& other);
    shared_ptr& operator=(shared_ptr&& other) noexcept;

    T& operator*() const;
    T* operator->() const;
    T* get() const;

    operator bool() const;

    size_t use_count() const;

    void reset(T* ptr = nullptr);

    template<class U>
    requires std::is_convertible_v<U*, T*>
    shared_ptr(shared_ptr<U>&& other) noexcept;

    template<class U>
    requires std::is_convertible_v<U*, T*>
    shared_ptr& operator=(shared_ptr<U>&& other) noexcept;
};

template<class T>
shared_ptr<T>::shared_ptr(T* ptr) : ptr_(ptr), ref_count(ptr ? new size_t(1) : nullptr) {}

template<class T>
shared_ptr<T>::~shared_ptr() {
    if(ref_count == nullptr || --(*ref_count) == 0) {
        delete ptr_;
        delete ref_count;
    }
}

template<class T>
shared_ptr<T>::shared_ptr(const shared_ptr& other) {
    (*other.ref_count)++;
    ref_count = other.ref_count;
    ptr_ = other.ptr_;
}

template<class T>
shared_ptr<T>::shared_ptr(shared_ptr&& other) noexcept {
    ptr_ = other.ptr_;
    ref_count = other.ref_count;

    other.ptr_ = nullptr;
    other.ref_count = nullptr;
}

template<class T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& other) noexcept {
    if (this == &other) return *this;

    (*other.ref_count)++;

    if (--(*ref_count) == 0) {
        delete ptr_;
        delete ref_count;
    }

    ptr_ = other.ptr_;
    ref_count = other.ref_count;

    return *this;
}

template<class T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& other) noexcept {
    if (this == &other) return *this;

    if (ref_count != nullptr && --(*ref_count) == 0) {
        delete ptr_;
        delete ref_count;
    }

    ptr_ = other.ptr_;
    ref_count = other.ref_count;

    other.ptr_ = nullptr;
    other.ref_count = nullptr;

    return *this;
}

template<class T>
T& shared_ptr<T>::operator*() const {
    return *ptr_;
}

template<class T>
T* shared_ptr<T>::operator->() const {
    return ptr_;
}

template<class T>
T* shared_ptr<T>::get() const {
    return ptr_;
}

template<class T>
shared_ptr<T>::operator bool() const {
    return ptr_ != nullptr;
}

template<class T>
void shared_ptr<T>::reset(T* ptr) {
    if (ptr_ == ptr) return;

    if (ref_count != nullptr && --(*ref_count) == 0) {
        delete ptr_;
        delete ref_count;
    }

    ptr_ = ptr;
    ref_count = new size_t(1);
}

template<class T>
size_t shared_ptr<T>::use_count() const {
    return ref_count ? *ref_count : 0;
}

template<class T>
template<class U>
requires std::is_convertible_v<U*, T*>
shared_ptr<T>::shared_ptr(shared_ptr<U>&& other) noexcept : ptr_(other.ptr_), ref_count(other.ref_count) {
    other.ptr_ = nullptr;
    other.ref_count = nullptr;
}

template<class T>
template<class U>
    requires std::is_convertible_v<U*, T*>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<U>&& other) noexcept {
    if (ptr_ == other.ptr_)  return *this;

    if (ref_count && --(*ref_count) == 0) {
        delete ptr_;
        delete ref_count;
    }

    ptr_ = other.ptr_;
    ref_count = other.ref_count;

    other.ptr_ = nullptr;
    other.ref_count = nullptr;

    return *this;
}

template<class T>
class shared_ptr<T[]> {
private:
    T* ptr_;
    size_t* ref_count;

public:
    explicit shared_ptr(T* ptr = nullptr);

    ~shared_ptr();

    shared_ptr(const shared_ptr& other);
    shared_ptr(shared_ptr&& other) noexcept;

    shared_ptr& operator=(const shared_ptr& other);
    shared_ptr& operator=(shared_ptr&& other) noexcept;

    T* get() const;

    operator bool() const;
    const T& operator[](size_t index) const;

    size_t use_count() const;

    void reset(T* ptr = nullptr);
};

template<class T>
shared_ptr<T[]>::shared_ptr(T* ptr) : ptr_(ptr), ref_count(ptr ? new size_t(1) : nullptr) {}

template<class T>
shared_ptr<T[]>::~shared_ptr() {
    if(ref_count == nullptr || --(*ref_count) == 0) {
        delete[] ptr_;
        delete ref_count;
    }
}

template<class T>
shared_ptr<T[]>::shared_ptr(const shared_ptr& other) {
    (*other.ref_count)++;
    ref_count = other.ref_count;
    ptr_ = other.ptr_;
}

template<class T>
shared_ptr<T[]>::shared_ptr(shared_ptr&& other) noexcept {
    ptr_ = other.ptr_;
    ref_count = other.ref_count;

    other.ptr_ = nullptr;
    other.ref_count = nullptr;
}

template<class T>
shared_ptr<T[]>& shared_ptr<T[]>::operator=(const shared_ptr& other) {
    if (this == &other) return *this;

    (*other.ref_count)++;

    if (--(*ref_count) == 0) {
        delete[] ptr_;
        delete ref_count;
    }

    ptr_ = other.ptr_;
    ref_count = other.ref_count;

    return *this;
}

template<class T>
shared_ptr<T[]>& shared_ptr<T[]>::operator=(shared_ptr&& other) noexcept {
    if (this == &other) return *this;

    if (ref_count != nullptr && --(*ref_count) == 0) {
        delete[] ptr_;
        delete ref_count;
    }

    ptr_ = other.ptr_;
    ref_count = other.ref_count;

    other.ptr_ = nullptr;
    other.ref_count = nullptr;

    return *this;
}

template<class T>
T* shared_ptr<T[]>::get() const {
    return ptr_;
}

template<class T>
shared_ptr<T[]>::operator bool() const {
    return ptr_ != nullptr;
}

template<class T>
void shared_ptr<T[]>::reset(T* ptr) {
    if (ptr_ == ptr) return;

    if (ref_count != nullptr && --(*ref_count) == 0) {
        delete[] ptr_;
        delete ref_count;
    }

    ptr_ = ptr;
    ref_count = new size_t(1);
}

template<class T>
size_t shared_ptr<T[]>::use_count() const {
    return ref_count ? *ref_count : 0;
}

template<class T>
const T& shared_ptr<T[]>::operator[](size_t index) const {
    return ptr_[index];
}