/////////////////////////////////////////////////
//
//  This file is part of
//      ___  ____  __  __  ___    __    ____
//     / __)(_  _)(  \/  )/ __)  /__\  (  _ \
//     \__ \ _)(_  )    (( (__  /(__)\  )(_) )
//     (___/(____)(_/\/\_)\___)(__)(__)(____/
//
//  A simulation library for electronic circuits
//  See also https://github.com/Terstegge/SimCad
//  (c) Andreas Terstegge
//
/////////////////////////////////////////////////
//
// Implementation of a generic Named Array (Narray).
// The array will automatically set the name of
// all contained objects.
//
#ifndef _NARRAY_H_
#define _NARRAY_H_

#include "Named.h"
#include <string>

template<typename T, size_t N>
class Narray : public Named {

public:

    typedef size_t  size_type;

    class iterator {
    public:
        iterator(T ** p) : _ptr(p) { }

              T & operator * ()       { return **_ptr;  }
        const T & operator * () const { return **_ptr;  }

        iterator& operator++()        { ++_ptr; return *this; }
        iterator  operator++(int)     { iterator temp(*this); _ptr++;; return temp; }

        bool operator != (const iterator & rhs) const { return _ptr != rhs._ptr; }
        bool operator == (const iterator & rhs) const { return !operator!=(rhs); }
    private:
        T * * _ptr;
    };

    class const_iterator {
    public:
        const_iterator(T * const * p) : _ptr(p) { }

              T & operator * ()       { return **_ptr;  }
        const T & operator * () const { return **_ptr;  }

        const_iterator& operator++()        { ++_ptr; return *this; }
        const_iterator  operator++(int)     { const_iterator temp(*this); _ptr++;; return temp; }

        bool operator != (const const_iterator & rhs) const { return _ptr != rhs._ptr; }
        bool operator == (const const_iterator & rhs) const { return !operator!=(rhs); }
    private:
        T * const * _ptr;
    };

    inline size_type size()       const { return N; }
    inline iterator begin()             { return iterator(&_elements[0]); }
    inline iterator end()               { return iterator(&_elements[N]); }
    inline const_iterator begin() const { return const_iterator(&_elements[0]); }
    inline const_iterator end()   const { return const_iterator(&_elements[N]); }

    inline T &       operator[] (int i)         { return *_elements[i]; }
    inline const T & operator[] (int i) const   { return *_elements[i]; }

    Narray(const std::string & n) : Named(n) {
        for (size_t i=0; i < N; ++i) {
            _elements[i] = new T(n + "[" + std::to_string(i) + "]");
        }
    }

    ~Narray() {
        for (size_t i=0; i < N; ++i) {
            delete _elements[i];
        }
    }

private:
    T * _elements[N];
};

#endif // _NARRAY_H_
