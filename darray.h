/*
 * Dynamic array class
 * No special optimizations or something.
 * Just base mechanics for allocate/free items
 */
#pragma once
#ifndef _DARRAY_IONCE
#define _DARRAY_IONCE

#include <cassert>
#include <cstddef>
#include <stdlib.h>
#include <string.h>

#define DEAFULT_ALLOCATION_SIZE 10

template <class T>
class Darray {
private:
  size_t allocated;
  size_t elemcount;
  T * dataptr;

public:
  Darray():
    allocated(0),
    elemcount(0),
    dataptr(0)
  {}

  Darray(int size) :
    Darray()
  {
    this->resize(size);
  }

  Darray(const T &value, const size_t size) :
    Darray()
  {
    this->resize(size, value);
  }

  ///
  ///Copy constructor
  ///
  Darray(const Darray &da) :
    Darray()
  {
    int size = sizeof(T) * da.allocated;
    this->dataptr = (T *)malloc(size);
    memcpy(this->dataptr, da.dataptr, size);
  }

  ~Darray()
  {
    if (this->dataptr) {
      this->clear();
      free(this->dataptr);
    }
  }

  T const * const &getPtr() const
  {
    return this->dataptr;
  }

  T * const &getPtr()
  {
    return const_cast<T * &>(
      static_cast<const Darray<T>&>(*this).getPtr()
    );
  }

  ///
  /// Put new element to the end of darray
  /// this method extends darray if necessary
  ///
  void push(const T &data)
  {
    if (this->allocated <= this->elemcount) {
      extend();
    }
    new(this->dataptr + this->elemcount++) T(data);
  }

  ///
  /// Removes element from the end of array
  ///
  void pop()
  {
    if (this->elemcount > 0) {
      (*this)[this->elemcount - 1].~T();
      --this->elemcount;
    }
  }

  ///
  /// Pop all elements
  ///
  void clear()
  {
    while (this->size()) {
      this->pop();
    }
  }

  ///
  ///Insert array of elements
  ///position - index of first inserted element
  ///
  void insert(const T * const data, const size_t len, const size_t position)
  {
    size_t allocate = len - (this->allocated - this->elemcount);
    if (position > this->allocated) {
      allocate += position - this->allocated;
    }

    if (allocate > 0)
      extend(allocate);

    if (this->elemcount > 0 && position < this->elemcount) {
      memmove(this->dataptr + (position + len),
             this->dataptr + position,
             (this->elemcount - position) * sizeof(T));
    }

    memcpy(this->dataptr + position, data, sizeof(T) * len);

    if (position > this->elemcount) {
      this->elemcount = this->allocated;
    } else {
      this->elemcount += len;
    }
  }

  ///
  /// Insert array of data to the end
  ///
  void append(const T * const data, const size_t len)
  {
    insert(data, len, this->size() ? this->size() - 1 : 0);
  }

  ///
  /// Insert array of data to the bigining
  ///
  void prepend(const T * const data, const size_t len)
  {
    insert(data, len, 0);
  }

  void set(const T * const data, size_t len)
  {
    if (this->allocated < len) {
      this->extend(len - this->allocated);
    }

    memcpy(this->dataptr, data, sizeof(T) * len);
    this->elemcount = len;
  }

  ///
  /// Returns amount of stored elements
  ///
  int size() const
  {
    return static_cast<int>(this->elemcount);
  }

  ///
  /// Change size of darra and fill new allocated memory with @placehodler
  ///
  void resize(const size_t new_size, const T placeholder = T())
  {
    if (this->allocated == new_size) {
      return;
    }

    if (this->allocated > new_size) {
      this->elemcount = new_size;
      shrink();
      return;
    }

    extend(new_size - this->allocated);
    while (this->elemcount < this->allocated) {
      this->push(placeholder);
    }
  }

  ///
  /// Extends darray on @size
  ///
  void extend(const size_t size = DEAFULT_ALLOCATION_SIZE)
  {
    this->allocated += size;
    if (!this->dataptr) {
      this->dataptr = static_cast<T *>(malloc(this->allocated * sizeof(T)));
    } else {
      this->dataptr = static_cast<T *>(realloc(this->dataptr,
                                               this->allocated * sizeof(T)));
    }
  }

  ///
  /// Free unused memory with reallocation
  ///
  void shrink()
  {
    if (this->allocated == 0) {
      return;
    }
    T * temp = static_cast<T *>(malloc(this->elemcount * sizeof(T)));
    memcpy(temp, this->dataptr, this->elemcount * sizeof(T));
    free(this->dataptr);
    dataptr = temp;
    allocated = elemcount;
    return;
  }

  T const &operator[](const size_t index) const
  {
    assert(index < elemcount);
    return *(this->dataptr + index);
  }

  T &operator[](const size_t index)
  {
    return const_cast<T &>(
      static_cast<const Darray<T>&>(*this)[index]
    );
  }

  Darray<T> &operator=(const Darray<T> &rhv)
  {
    if (this == &rhv) {
      return *this;
    }

    this->resize(rhv.allocated);
    memcpy(this->dataptr, rhv.dataptr, this->allocated * sizeof(T));
    this->elemcount = rhv.elemcount;

    return *this;
  }

  friend bool operator==(const Darray<T> &lhv, const Darray<T> &rhv)
  {
    if (lhv.dataptr == rhv.dataptr) {
      return true;
    }
    return false;
  }
};

#endif
