#ifndef DISPERSION_FUNCTION_H_
#define DISPERSION_FUNCTION_H_

template <class Key>
class DispersionFunction {
  public:
    virtual ~DispersionFunction() = default;
    virtual unsigned operator()(const Key& key) const = 0;
};

template <class Key>
class ModuloDispersion : public DispersionFunction<Key> {
  public:
    explicit ModuloDispersion(unsigned table_size) 
    : Tamaño_Table(table_size) {}

    unsigned operator()(const Key& key) const override {
      return static_cast<unsigned>(static_cast<long>(key) % Tamaño_Table);
    }

  private:
    unsigned Tamaño_Table;
};

template <class Key>
class SumaDispersion : public DispersionFunction<Key> {
  public:
    explicit SumaDispersion(unsigned table_size)
      : Tamaño_Table(table_size) {}
    
    unsigned operator()(const Key& key) const override {
      long value = static_cast<long>(key);
      if(value < 0) {
        value = -value;
      }

      unsigned sum = 0;
      while(value > 0) {
        sum += static_cast<unsigned>(value % 10);
        value /= 10;
      }

      return sum % Tamaño_Table;
    }

  private: 
    unsigned Tamaño_Table;
};

template <class Key>
class RandDispersion : public DispersionFunction<Key> {
  public:
    explicit RandDispersion(unsigned table_size)
      : Tamaño_Table(table_size) {}
    
    unsigned operator()(const Key& key) const override {
      std::srand(static_cast<unsigned>std::rand()) % Tamaño_Table;
    }
  
  private: 
    unsigned Tamaño_Table;
};

#endif