#include <iostream>

using namespace std;

//struct Storage {
//    int *data;
//    size_t size;
//};

class Storage {
private:
    int *data;
    size_t size;

public:
    Storage() {
        data = nullptr;
        size = 0;
    }

    void AddElem(int val) {
        if (data == nullptr) {
            data = new int[1];
            data[0] = val;
            size = 1;
        } else {
            int *buf = new int[size + 1];
            for (size_t i = 0; i < size; i++) {
                buf[i] = data[i];
            }
            buf[size] = val;
            delete [] data;
            data = buf;
            size++;
        }
    };

    int GetElemByNum(size_t num) {
        return data[num];
    };
    size_t TotalSize() {
        return size;
    };

};

bool testStorage4(){
    Storage storage;
    for (int k = 0; k < 4; k++) {
        storage.AddElem(k);
    }
    if (storage.TotalSize() != 4) return false;
    for (int k = 0; k < 4; k++) {
        if (storage.GetElemByNum(k) != k) {
            cout << storage.GetElemByNum(k) << k << endl;
            return false;
        }
    }
    return true;
}

int main()
{
    Storage storage;
    storage.AddElem(1);
    storage.AddElem(2);
    storage.AddElem(3);
    storage.AddElem(4);
    storage.AddElem(5);
    cout << "total size: " << storage.TotalSize() << endl;
    cout << (testStorage4() ? "CORRECT" : "FAILURE") << endl;
    return 0;
}
