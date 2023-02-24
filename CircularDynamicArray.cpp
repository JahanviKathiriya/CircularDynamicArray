#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

template <class elmtype>
class CircularDynamicArray{
    private:
        elmtype *carr;
        int cap;
        int len;
        int head;
        int tail;
        int isReverse;
        int binarySearch(int start, int end, elmtype search);
        elmtype select(CircularDynamicArray<elmtype> V, int k);
        void mergeSort(int start, int end);
        elmtype safe;
    public:
        CircularDynamicArray(); //check !
        CircularDynamicArray(int s); //check !
        ~CircularDynamicArray(); //check !
        int length(); //check !
        int capacity(); //check !
        void clear(); //check !
        elmtype& operator[](int i); //check !
        void addEnd(elmtype v); //check st r
        void addFront(elmtype v); //check st r
        void delEnd(); //check st r
        void delFront(); //check st r
        void reverse(); //check !
        elmtype QuickSelect(int k); //check !
        void stableSort(); //check !
        int linearSearch(elmtype e); //check !
        int binSearch(elmtype e); //check !
        CircularDynamicArray(const CircularDynamicArray &x); //check !
        CircularDynamicArray& operator=(const CircularDynamicArray& x); //check !
};

template <class elmtype>
CircularDynamicArray<elmtype>::CircularDynamicArray(){
    carr = new elmtype[2];
    cap = 2;
    len = 0;
    head = 1;
    tail = 0;
    isReverse = -1;
}

template <class elmtype>
CircularDynamicArray<elmtype>::CircularDynamicArray(int s){
    carr = new elmtype[s];
    cap = s;
    len = s;
    head = 0;
    tail = s-1;
    isReverse = -1;
}

template <class elmtype>
elmtype& CircularDynamicArray<elmtype>::operator[](int i){
    if (i >= len) {
        cout<<"Out of Bounds"<<endl;
        return safe;
    }
    return carr[(cap + head - ((isReverse) * i)) % cap];
}

template <class elmtype>
void CircularDynamicArray<elmtype>::addFront(elmtype v){
    if (len == cap){
        elmtype* newcarr = new elmtype[cap*2];
        for(int i = 0; i < len; i++) newcarr[i] = (*this)[i];
        cap = cap*2;
        delete [] carr;
        carr = newcarr;
        head = cap-1;
        tail = len - 1;
        len++;
        isReverse = -1;
        (*this)[0] = v;
    }
    else{
        head = (cap + head + isReverse) % cap;
        len++;
        (*this)[0] = v;
    }
}

template <class elmtype>
void CircularDynamicArray<elmtype>::addEnd(elmtype v){
    if (cap == len){
        elmtype* newcarr = new elmtype[cap*2];
        for(int i = 0; i < len; i++) newcarr[i] = (*this)[i];
        cap = cap*2;
        delete [] carr;
        carr = newcarr;
        head = 0;
        len++;
        tail = len - 1;
        isReverse = -1;
        (*this)[tail] = v;
    }
    else{
        tail = (cap + tail - isReverse) % cap;
        len++;
        (*this)[len - 1] = v;
    }   
}

template <class elmtype>
void CircularDynamicArray<elmtype>::delFront(){
    head = (cap + head - isReverse) % cap;
    len--;
    if (len <= cap / 4){
        elmtype* newcarr = new elmtype[cap/2];
        for(int i = 0; i < len; i++) newcarr[i] = (*this)[i];
        cap = cap / 2;
        delete [] carr;
        carr = newcarr;
        head = 0;
        tail = len - 1;
        isReverse = -1;
    }
}

template <class elmtype>
void CircularDynamicArray<elmtype>::delEnd(){
    tail = (cap + tail + isReverse) % cap;
    len--;
    if (len <= cap / 4){
        elmtype* newcarr = new elmtype[cap/2];
        for(int i = 0; i < len; i++) newcarr[i] = (*this)[i];
        cap = cap / 2;
        delete [] carr;
        carr = newcarr;
        head = 0;
        tail = len - 1;
        isReverse = -1;
    }
}

template <class elmtype>
int CircularDynamicArray<elmtype>::capacity(){
    return cap;
}

template <class elmtype>
int CircularDynamicArray<elmtype>::length(){
    return len;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::clear(){
    delete [] carr;
    carr = new elmtype[2];
    cap = 2;
    len = 0;
    head = 1;
    tail = 0;
    isReverse = -1;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::reverse(){
    int p = tail;
    tail = head;
    head = p;
    isReverse = -1 * isReverse;
}

template <class elmtype>
CircularDynamicArray<elmtype>::~CircularDynamicArray(){
    delete [] carr;
}

template <class elmtype>
CircularDynamicArray<elmtype>::CircularDynamicArray(const CircularDynamicArray &x){
    len = x.len;
    cap = x.cap;
    head = x.head;
    tail = x.tail;
    isReverse = x.isReverse;
    carr = new elmtype[cap];
    for(int i = 0; i < cap; i++) carr[i] = x.carr[i];
}

template <class elmtype>
CircularDynamicArray<elmtype>& CircularDynamicArray<elmtype>::operator=(const CircularDynamicArray& x){
    if(this != &x){
        len = x.len;
        cap = x.cap;
        head = x.head;
        tail = x.tail;
        isReverse = x.isReverse;
        delete [] carr;
        carr = new elmtype[cap];
        for(int i = 0; i < cap; i++) carr[i] = x.carr[i];
    }  
    return *this;
}

template <class elmtype>
int CircularDynamicArray<elmtype>::linearSearch(elmtype e){
    for(int i = 0; i < len; i++) {
        if((*this)[i] == e) return i;
    }
    return -1;
}

template <class elmtype>
void CircularDynamicArray<elmtype>::mergeSort(int start, int end){
    int midd = (end + start) / 2;    //divide
    if (midd != end && midd != start){
        mergeSort(start, midd);
        mergeSort(midd+1, end);
    }
    int s1 = midd - start + 1;      //merge
    int s2 = end - midd;
    vector<elmtype> L,M;
    for(int i = 0; i < s1; i++) L.push_back((*this)[start + i]);
    for(int j = 0; j < s2; j++) M.push_back((*this)[midd + 1 + j]);
    int i = 0, j = 0, k = start;
    while(i < s1 && j < s2){
        if (L[i] <= M[j]) (*this)[k++] = L[i++];
        else (*this)[k++] = M[j++];
    }
    while(i < s1) (*this)[k++] = L[i++];
    while(j < s2) (*this)[k++] = M[j++];
}
template <class elmtype>
void CircularDynamicArray<elmtype>::stableSort(){
    mergeSort(0 , len - 1);
}

template <class elmtype>
elmtype CircularDynamicArray<elmtype>::select(CircularDynamicArray<elmtype> V, int k){
    CircularDynamicArray<elmtype> L, E, G;
    if(V.length() == 1) return V[0];
    int pivot = (rand() % (V.length() - 1));
    for (int i = 0; i < V.length(); i++){
        if (V[i] > V[pivot]) G.addEnd(V[i]);
        else if (V[i] == V[pivot]) E.addEnd(V[i]);
        else if (V[i] < V[pivot]) L.addEnd(V[i]);
    }
    if (k > L.length() && k <= (L.length() + E.length())) return E[0];
    else if (k <= L.length()) return select(L, k);
    else if (k > (L.length() + E.length())) return select(G, k - (L.length() + E.length()));
}
template <class elmtype>
elmtype CircularDynamicArray<elmtype>::QuickSelect(int k){
    if (k > len || k < 1) return safe;
    return select((*this), k);
}

template <class elmtype>
int CircularDynamicArray<elmtype>::binarySearch(int start, int end, elmtype search){
    int searchInd = (end + start) / 2;
    if ((*this)[searchInd] == search) return searchInd;
    else if (end <= start) return -1;
    else if ((*this)[searchInd] > search) return binarySearch(start, searchInd - 1, search);
    else if ((*this)[searchInd] < search) return binarySearch(searchInd + 1, end, search);
}
template <class elmtype>
int CircularDynamicArray<elmtype>::binSearch(elmtype e){
    return binarySearch(0, len - 1, e);
}