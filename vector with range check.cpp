template<class T>
struct myvector : vector<T> {
    myvector() : vector<T>() { }
    myvector(int n) : vector<T>(n) { }
    
    T& operator[](int i) {
        assert(0 <= i && i <= vector<T>::size());
        return vector<T>::operator[](i);
    }
};
