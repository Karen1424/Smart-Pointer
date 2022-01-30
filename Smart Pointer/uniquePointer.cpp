#include <iostream>
#include <functional>

template < typename T, typename del = std::function<void(T*)>>
class smartPointer {
public:
    smartPointer(const smartPointer &) = delete;
    smartPointer(smartPointer && ) noexcept;
    smartPointer(T* n_ptr = nullptr, del deletor = nullptr);
    ~smartPointer();
public:
    void operator=(const smartPointer &) = delete;
    void operator=(smartPointer &&) noexcept;
    T& operator*();
public:
    void get_deletor(std::function<void(T*)>);
private:
    void clear() noexcept;
private:
    T* s_ptr;
    del ptr ;
};

template < typename T, typename del>
smartPointer<T,del>::smartPointer(T* n_ptr, del deletor)
{
    s_ptr = n_ptr;
    n_ptr = nullptr;
    ptr = deletor ; 
}
template < typename T, typename del>
smartPointer<T,del>::smartPointer(smartPointer<T,del> && other) noexcept
{
    this->s_ptr = other.s_ptr;
    other.s_ptr = nullptr;
    this->ptr = other.ptr;
}

template < typename T, typename del>
void smartPointer<T,del>::operator=(smartPointer<T,del> && other) noexcept
{
        
    if(s_ptr != nullptr) clear();
    this->s_ptr = other.s_ptr;
    other.s_ptr = nullptr;
    ptr = other.ptr;
}

template < typename T, typename del>
void smartPointer<T,del>::clear() noexcept
{
    if(ptr == nullptr)
    {
        std::cout << "delete" << std::endl;
        delete s_ptr ;
        s_ptr = nullptr;
    }
    else
    {
        ptr(s_ptr);
        std::cout << "del";
    }
}

template <typename T, typename del>
T& smartPointer<T,del>::operator*() 
{
    return *s_ptr;
}

template <typename T, typename del>
smartPointer<T,del>::~smartPointer()
{
    clear();
}

template <typename T, typename del>
void smartPointer<T,del>::get_deletor(std::function<void(T*)> deletor)
{
    this->ptr = deletor;
}

int main() {

    int * b = new int; 
    *b = 10;
    smartPointer<int> ptr (b, [&](int * b){ });
    std::cout<< "++++++++++++++++++++++++++++"<<std::endl;
    std::cout<< *ptr <<std::endl;
    *ptr = 25;
    std::cout<< "++++++++++++++++++++++++++++"<<std::endl;
    std::cout << *ptr;

    return 0;
}