#ifndef NIF_H_
#define NIF_H_

#include <iostream>

/**
 * @brief Representación el NIF como clave de la tabla
 */
class nif {
  public:

    /**
     * @brief Construye un NIF random de 8 dígitos
     */
    nif();

    /**
     * @brief Construye un NIF a partir de un valor
     * @param value Valor entero que inicializa el NIF
     */
    nif(long value);

    /**
     * @brief Conversión de NIF a long
     * @return NIF
     */
    operator long() const;

    /**
     * @brief Comparaciones de NIFs
     * @param other Segundo nif de comparación
     */
    bool operator==(const nif& other) const;
    bool operator!=(const nif& other) const;
    bool operator<(const nif& other) const;
    bool operator<=(const nif& other) const;
    bool operator>=(const nif& other) const;

    /**
     * @brief Inserta el valor del NIF en un flujo de salida
     * @param os Flujo de salida
     * @param value NIF a sacar
     * @return Referencia al flujo de salida
     */
    friend std::ostream& operator<<(std::ostream& os, const nif& value);

  private:
    long Valor;
};

#endif