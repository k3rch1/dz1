#pragma once
#include <cstddef>
#include <type_traits>

template<class T>
class unique_ptr {
private:
    T* ptr_;

    template<class U>
    friend class unique_ptr;
public:
    explicit unique_ptr(T* ptr = nullptr);

    ~unique_ptr();

    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr(unique_ptr&& other) noexcept;

    template<class U>
    requires std::is_convertible_v<U*, T*>
    unique_ptr(unique_ptr<U>&& other) noexcept;

    unique_ptr& operator=(const unique_ptr& other) = delete;
    unique_ptr& operator=(unique_ptr&& other) noexcept;

    template<class U>
    requires std::is_convertible_v<U*, T*>
    unique_ptr& operator=(unique_ptr<U>&& other) noexcept;

    T& operator*() const;
    T* operator->() const;
    T* get() const;

    operator bool() const;

    T* release();
    void reset(T* ptr = nullptr);
};

template<class T>
unique_ptr<T>::unique_ptr(T* ptr) : ptr_(ptr) {}

template<class T>
unique_ptr<T>::~unique_ptr() {
    delete ptr_;
}

template<class T>
unique_ptr<T>::unique_ptr(unique_ptr&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
}

template<class T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& other) noexcept {
    if (this == &other) return *this;

    delete ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;

    return *this;
}

template<class T>
T& unique_ptr<T>::operator*() const {
    return *ptr_;
}

template<class T>
T* unique_ptr<T>::operator->() const {
    return ptr_;
}

template<class T>
T* unique_ptr<T>::get() const {
    return ptr_;
}

template<class T>
unique_ptr<T>::operator bool() const {
    return ptr_ != nullptr;
}

template<class T>
T* unique_ptr<T>::release() {
    T* return_ptr = ptr_;
    ptr_ = nullptr;
    return return_ptr;
}

template<class T>
void unique_ptr<T>::reset(T* ptr) {
    if (ptr_ != ptr) {
        delete ptr_;
        ptr_ = ptr;
    }
}

template<class T>
template<class U>
requires std::is_convertible_v<U*, T*>
unique_ptr<T>::unique_ptr(unique_ptr<U>&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

template<class T>
template<class U>
    requires std::is_convertible_v<U*, T*>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr<U>&& other) noexcept {
    if (ptr_ == other.ptr_) return *this;

    delete ptr_;

    ptr_ = other.ptr_;
    other.ptr_ = nullptr;

    return *this;
}

template<class T>
class unique_ptr<T[]> {
private:
    T* ptr_;

public:
    explicit unique_ptr(T* ptr = nullptr);

    ~unique_ptr();

    unique_ptr(const unique_ptr& other) = delete;
    unique_ptr(unique_ptr&& other) noexcept;

    unique_ptr& operator=(const unique_ptr& other) = delete;
    unique_ptr& operator=(unique_ptr&& other) noexcept;

    T& operator[](size_t index) const;
    T* get() const;

    operator bool() const;

    T* release();
    void reset(T* ptr = nullptr);
};

template<class T>
unique_ptr<T[]>::unique_ptr(T* ptr) : ptr_(ptr) {}

template<class T>
unique_ptr<T[]>::~unique_ptr() {
    delete[] ptr_;
}

template<class T>
unique_ptr<T[]>::unique_ptr(unique_ptr&& other) noexcept {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
}

template<class T>
unique_ptr<T[]>& unique_ptr<T[]>::operator=(unique_ptr&& other) noexcept {
    if (this == &other) return *this;

    delete[] ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;

    return *this;
}

template<class T>
T* unique_ptr<T[]>::get() const {
    return ptr_;
}

template<class T>
unique_ptr<T[]>::operator bool() const {
    return ptr_ != nullptr;
}

template<class T>
T* unique_ptr<T[]>::release() {
    T* return_ptr = ptr_;
    ptr_ = nullptr;
    return return_ptr;
}

template<class T>
void unique_ptr<T[]>::reset(T* ptr) {
    if (ptr_ != ptr) {
        delete[] ptr_;
        ptr_ = ptr;
    }
}

template<class T>
T& unique_ptr<T[]>::operator[](size_t index) const {
    return ptr_[index];
}