#ifndef DISPERSION_FUNCTION_H_
#define DISPERSION_FUNCTION_H_


/**
 * @brief Clase abstracta de función de dispersión
 * @param Key Tipo de clave a dispersar
 */
template <class Key>
class DispersionFunction {
  public:
    /**
     * @brief Destructor virtual por defecto
     */
    virtual ~DispersionFunction() = default;

    /**
     * @brief Cálculo de posición de la clave
     * @param key Clave a dispersar
     * @return Posición obtenida al dispersar
     */
    virtual unsigned operator()(const Key& key) const = 0;
};


/**
 * @brief Dispersión basada en el operador módulo
 * @param key Tipo de clave
 */
template <class Key>
class ModuloDispersion : public DispersionFunction<Key> {
  public:
    /**
     * @brief Constuctor de dispersión módulo
     * @param table_size Tamaño de la tabla hash
     */
    explicit ModuloDispersion(unsigned table_size) 
    : Tamaño_Table(table_size) {}

    /**
     * @brief Calculo de dispersión con el operador módulo
     * @param key Clave a dispersar
     * @return Posición calculada en la tabla
     */
    unsigned operator()(const Key& key) const override {
      return static_cast<unsigned>(static_cast<long>(key) % Tamaño_Table);
    }

  private:
    unsigned Tamaño_Table;
};

/**
 * @brief Dispersión basada en la suma de dígitos de la clave
 * @param Key Tipo de clave
 */
template <class Key>
class SumaDispersion : public DispersionFunction<Key> {
  public:
    /**
     * @brief Constructor de dispersión por suma
     * @param table_size Tamaño de la tabla hash
     */
    explicit SumaDispersion(unsigned table_size)
      : Tamaño_Table(table_size) {}
    
    /**
     * @brief Calculo de dispersión con suma de dígitos
     * @param key Clave a dispersar
     * @return Posición calculada en la tabla
     */
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

/**
 * @brief Función de dispersión random
 * @param Key Tipo de clave
 */
template <class Key>
class RandDispersion : public DispersionFunction<Key> {
  public:
    /**
     * @brief Constructor de dispersión random
     * @param table_size Tamaño de la tabla hash
     */
    explicit RandDispersion(unsigned table_size)
      : Tamaño_Table(table_size) {}
    
    /**
     * @brief Calculo de dispersión de la clave con aleatoriedad
     * @param key Clave a dispersar
     * @return Posición calculada en la tabla
     */
    unsigned operator()(const Key& key) const override {
      std::srand(static_cast<unsigned>std::rand()) % Tamaño_Table;
    }
  
  private: 
    unsigned Tamaño_Table;
};

#endif