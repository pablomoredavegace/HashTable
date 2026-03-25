#ifndef SEQUENCE_H_
#define SEQUENCE_H_

/**
 * @brief Clase abstracta para secuencias de la tabla hash
 * @param Key Tipo de clave
 */
template <class Key>
class Sequence {
  public:
    /**
     * @brief Destructor virtual por defecto
     */
    virtual ~Sequence() = default;

    /**
     * @brief Búsqueda de clave en la secuencia
     * @param key Clave a buscar
     * @return true si la clave está en la secuencia, false si no se encuentra
     */
    virtual bool search(const Key& key) const = 0;

    /**
     * @brief Inserción de clave en la secuencia
     * @param key Clave a insertar
     * @return ture si la clave se inserta correctamente, false si no se inserta
     */
    virtual bool insert(const Key& key) = 0;
};

#endif