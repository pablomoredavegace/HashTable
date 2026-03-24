#ifndef DYNAMIC_SEQUENCE_H_
#define DYNAMIC_SEQUENCE_H_

#include "sequence.h"
#include <list>

template <class Key>
class DynamicSequence : public Sequence<Key> {
  public:
    DynamicSequence() = default;
    ~DynamicSequence() override = default;

    bool search(const Key& key) const override {
      for(const Key& element : Datos) {
        if(element == key) {
          return true;
        }
      }
      return false;
    }

    bool insert(const Key& key) override {
      if(search(key)) {
        return false;
      }
      Datos.push_back(key);
      return true;
    }

    private:
      std::list<Key> Datos;
};

#endif