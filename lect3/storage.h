#ifndef STORAGE_H_INCLUDED
#define STORAGE_H_INCLUDED

//#define T int

template<typename T> class Storage {
private:
    T *data;
    size_t size;

public:
    Storage() {
        data = nullptr;
        size = 0;
    }

    void AddElem(T val) {
        if (data == nullptr) {
            data = new T[1];
            data[0] = val;
            size = 1;
        } else {
            T *buf = new T[size + 1];
            for (size_t i = 0; i < size; i++) {
                buf[i] = data[i];
            }
            buf[size] = val;
            delete [] data;
            data = buf;
            size++;
        }
    };

    T GetElemByNum(size_t num) {
        return data[num];
    };
    size_t TotalSize() {
        return size;
    };

};

#endif // STORAGE_H_INCLUDED
