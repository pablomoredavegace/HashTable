#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

#include "dispersion_function.h"
#include "exploration_function.h"
#include "sequence.h"
#include "dynamic_sequence.h"
#include "static_sequence.h"

template <class Key, class Container = StaticSequence<Key>>
class HashTable : public Sequence<Key> {
  public:
    HashTable(unsigned table_size, DispersionFunction<Key>& fd,
              ExplorationFunction<Key>& fe, unsigned block_size)
    :Tamaño_table(table_size), table_(nullptr), fd_(fd), fe_(fe),
    block_size_(block_size) {
      table_ = new Container*[Tamaño_table];
      for(unsigned i = 0; i < Tamaño_table; ++i) {
        table_[i] = new Container(block_size_);
      }
    }

    ~HashTable() override {
      for(unsigned i = 0; i < Tamaño_table; ++i) {
        delete table_[i];
      }
      delete[] table_;
    }

    bool search(const Key& key) const override {
      unsigned index = fd_(key);

      if(table_[index]->search(key)) {
        return true;
      }

      if(!table_[index]->isFull()) {
        return false;
      }

      for(unsigned i = 1; i < Tamaño_table; ++i) {
        unsigned probe = (index + fe_(key, i)) % Tamaño_table;

        if(table_[probe]->search(key)) {
          return true;
        }

        if(!table_[probe]->isFull()) {
          return false;
        }
      }
      return false;
    }

    bool insert(const Key& key) override {
      if(search(key)) {
        return false;
      }

      unsigned index = fd_(key);

      if(table_[index]->insert(key)) {
        return true;
      }

      for(unsigned i = 1; i < Tamaño_table; ++i) {
        unsigned probe = (index + fe_(key, i)) % Tamaño_table;

        if(table_[probe]->insert(key)) {
          return true;
        }
      }
      return false;
    }

  private:
    unsigned Tamaño_table;
    Container** table_;
    DispersionFunction<Key>& fd_;
    ExplorationFunction<Key>& fe_;
    unsigned block_size_;
};


template <class Key>
class HashTable<Key, DynamicSequence<Key>> : public Sequence<Key> {
  public:
    HashTable(unsigned table_size, DispersionFunction<Key>& fd)
    :Tamaño_table(table_size), table_(nullptr), fd_(fd) {
      table_ = new DynamicSequence<Key>[Tamaño_table];
    }

    ~HashTable() override {
      delete[] table_;
    }

    bool search(const Key& key) const override {
      unsigned index = fd_(key);
      return table_[index].search(key);
    }

    bool insert(const Key& key) const override {
      unsigned index = fd_(key);
      return table_[index].insert(key);
    }
  
  private:
    unsigned table_size_;
    DynamicSequence<Key>* table_;
    DispersionFunction<Key>& fd_;

};

#endif