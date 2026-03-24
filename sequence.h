#ifndef SEQUENCE_H_
#define SEQUENCE_H_

template <class Key>
class Sequence {
  public:
    virtual ~Sequence() = default;
    virtual bool search(const Key& key) const = 0;
    virtual bool insert(const Key& key) = 0;
};

#endif