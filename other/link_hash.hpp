#include <vector>

template<typename T>
class link_hash
{
private:
    int MOD;
    std::vector<T> *key_val;
    T *val;
    int *key;

public:
    link_hash(int mod)
    {
        MOD = mod;
        key_val = new std::vector<T>[MOD];
        val = new T[MOD];
    }
    ~link_hash()
    {
        delete[] key_val;
        delete[] val;
    }

};