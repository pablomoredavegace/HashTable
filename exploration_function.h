#ifndef EXPLORATION_FUNCTION_H_
#define EXPLORATION_FUNCTION_H_

#include "dispersion_function.h"

/**
 * @brief Clase abstracta de función de exploración
 * @param Key Tipo de clave a explorar
 */
template <class Key>
class ExplorationFunction {
  public:
    /**
     * @brief Destructor virtual por defecto
     */
    virtual ~ExplorationFunction() = default;

    /**
    * @brief Calculo de desplazamiento por exploración
    * @param key Clave a insertar o buscar
    * @param i Número de intento de exploración
    * @return Desplazamiento calculado para el intento
    */
    virtual unsigned operator()(const Key& key, unsigned i) const = 0;
};


/**
 * @brief Función de exploración lineal
 * @param Key Tipo de clave
 */
template <class Key>
class LinearExploration : public ExplorationFunction<Key> {
  public:
    /**
     * @brief Calculo de desplazamiento lineal
     * @param key Clave a insertar o buscar
     * @param i Número de intento de exploración
     * @return Desplazamiento lineal
     */
    unsigned operator()(const Key& key, unsigned i) const override {
      return i;
    }
};

/**
 * @brief Función de exploración cuadrática
 * @param Key Tipo de clave
 */
template <class Key>
class QuadraticExploration : public ExplorationFunction<Key> {
  public:
    /**
     * @brief Calculo de desplazamiento cuadrático
     * @param key Clave a insertar o buscar
     * @param i Número de intento de exploración
     * @return Desplazamiento cuadrático
     */
    unsigned operator()(const Key& key, unsigned i) const override {
      return i * i;
    }
};

/**
 * @brief Función de exploración por doble dispersión
 * @param Key Tipo de clave
 */
template <class Key>
class DoubleDispersion : public ExplorationFunction<Key> {
  public:
    /**
     * @brief Constructor de exploración por doble dispersión
     * @param dispersion_function Función de dispersión auxiliar
     */
    explicit DoubleDispersion(DispersionFunction<Key>& dispersion_function)
    : Funcion_dispersion(dispersion_function) {}

    /**
     * @brief Calculo de desplazamiento de doble dispersión
     * @param key Clave a insertar o buscar
     * @param i Número de intento de exploración
     * @return Desplazamiento doble
     */
    unsigned operator()(const Key& key, unsigned i) const override {
      return Funcion_dispersion(key) * i;
    }
  
  private:
    DispersionFunction<Key>& Funcion_dispersion;
};

/**
 * @brief Función de exploración por redispersión
 * @param Key Tipo de clave
 */
template <class Key>
class RehashFunction : public ExplorationFunction<Key> {
  public:
    /**
     * @brief Calculo de desplazamiento por redispersión
     * @param key Clave a insertar o buscar
     * @param i Número de intento de exploración
     * @return Desplazamiento por redispersión
     */
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