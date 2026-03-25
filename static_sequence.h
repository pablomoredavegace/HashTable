#ifndef STATIC_SEQUENCE_H_
#define STATIC_SEQUENCE_H_

#include "sequence.h"
#include <vector>

/**
 * @brief Secuencia estática en la dispersión cerrada
 * @param Key Tipo de clave
 */
template <class Key>
class StaticSequence : public Sequence<Key> {
  public:
    /**
     * @brief Constructor de secuencia estática
     * @param block_size Número máximo de claves en la secuencia
     */
    explicit StaticSequence(unsigned block_size)
    : Datos(block_size), size_(0) {}

    /**
     * @brief Destructor virtual por defecto
     */
    ~StaticSequence() override = default;

    /**
     * @brief Búsqueda de clave en secuencia estática
     * @param key Clave a buscar
     * @return true si la clave está almacenada, false si no lo está
     */
    bool search(const Key& key) const override {
      for(unsigned i = 0; i < size_; ++i) {
        if(Datos[i] == key) {
          return true;
        }
      }
      return false;
    }

    /**
     * @brief Inserción de clave en secuencia estática
     * @param key Clave a insertar
     * @return true si la clave se inserta correctamente, false si no se inserta
     */
    bool insert(const Key& key) override {
      if(isFull() || search(key)) {
        return false;
      }
      Datos[size_] = key;
      ++size_;
      return true;
    }

    /**
     * @brief Comprobar si la secuencia está llena
     * @return true si no hay huecos libres, false si hay huecos
     */
    bool isFull() const {
      return size_ >= Datos.size();
    }

    private:
      std::vector<Key> Datos;
      unsigned size_;
};

#endif