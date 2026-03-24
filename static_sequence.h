#ifndef STATIC_SEQUENCE_H_
#define STATIC_SEQUENCE_H_

#include "sequence.h"
#include <vector>

template <class Key>
class StaticSequence : public Sequence<Key> {
  public:
    explicit StaticSequence(unsigned block_size)
    : Datos(block_size), size_(0) {}

    ~StaticSequence() override = default;

    bool search(const Key& key) const override {
      for(unsigned i = 0; i < size_; ++i) {
        if(Datos[i] == key) {
          return true;
        }
      }
      return false;
    }

    bool insert(const Key& key) override {
      if(isFull() || search(key)) {
        return false;
      }
      Datos[size_] = key;
      ++size_;
      return true;
    }

    bool isFull() const {
      return size_ >= Datos.size();
    }

    private:
      std::vector<Key> Datos;
      unsigned size_;
};

#endif