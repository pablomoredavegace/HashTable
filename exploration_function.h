#ifndef EXPLORATION_FUNCTION_H_
#define EXPLORATION_FUNCTION_H_

#include "dispersion_function.h"

template <class Key>
class ExplorationFunction {
  public:
    virtual ~ExplorationFunction() = default;
    virtual unsigned operator()(const Key& key, unsigned i) const = 0;
};

template <class Key>
class LinearExploration : public ExplorationFunction<Key> {
  public:
    unsigned operator()(const Key& key, unsigned i) const override {
      return i;
    }
};

template <class Key>
class QuadraticExploration : public ExplorationFunction<Key> {
  public:
    unsigned operator()(const Key& key, unsigned i) const override {
      return i * i;
    }
};

template <class Key>
class DoubleDispersion : public ExplorationFunction<Key> {
  public:
    explicit DoubleDispersion(DispersionFunction<Key>& dispersion_function)
    : Funcion_dispersion(dispersion_function) {}

    unsigned operator()(const Key& key, unsigned i) const override {
      return Funcion_dispersion(key) * i;
    }
  
  private:
    DispersionFunction<Key>& Funcion_dispersion;
};

template <class Key>
class RehashFunction : public ExplorationFunction<Key> {
  public:
    unsigned operator()(const Key& key, unsigned i) const override {
      std::srand(static_cast<unsigned>(static_cast<long>(key)));
      unsigned value = 0;

      for(unsigned j = 0; j < i; ++j) {
        value = static_cast<unsigned>(std::rand());
      }

      return value;
    }
};

#endif