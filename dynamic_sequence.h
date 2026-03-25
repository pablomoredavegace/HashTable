#ifndef DYNAMIC_SEQUENCE_H_
#define DYNAMIC_SEQUENCE_H_

#include "sequence.h"
#include <list>

/**
 * @brief Secuencia dinámica en la dispersión abierta
 * @param Key Tipo de clave
 */
template <class Key>
class DynamicSequence : public Sequence<Key> {
  public:
    /**
     * @brief Constructor de secuencia dinámica por defecto
     */
    DynamicSequence() = default;

    /**
     * @brief Destructor virtual por defecto
     */
    ~DynamicSequence() override = default;


    /**
     * @brief Búsqueda de clave en secuencia dinámica
     * @param key Clave a buscar
     * @return true si la clave está almacenada, false si no lo está
     */
    bool search(const Key& key) const override {
      for(const Key& element : Datos) {
        if(element == key) {
          return true;
        }
      }
      return false;
    }

    /**
     * @brief Inserción de clave en secuencia dinámica
     * @param key Clave a insertar
     * @return true si la clave se inserta correctamente, false si no se inserta
     */
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