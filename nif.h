#ifndef NIF_H_
#define NIF_H_

#include <iostream>

class nif {
  public:
    nif();
    nif(long value);

    operator long() const;

    bool operator==(const nif& other) const;
    bool operator!=(const nif& other) const;
    bool operator<(const nif& other) const;
    bool operator<=(const nif& other) const;
    bool operator>=(const nif& other) const;

    friend std::ostream& operator<<(std::ostream& os, const nif& value);

  private:
    long Valor;
};

#endif