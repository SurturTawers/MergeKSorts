#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;
void printArray(float *A, int size){
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
}
void merge(float *a, int l, int m, int r){
    int n1 = m - l + 1, n2 = r - m;
    float *L, *R;
    L=new float[n1];
    R=new float[n2];
    for (int i = 0; i < n1; i++){
        L[i] = a[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = a[m + 1 + j];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
    delete[] L;
    delete[] R;
}
void merge3(float* A,int l,int t, int d_t,int r){
    merge(A,l,t,d_t);
    merge(A,l,d_t,r);
}
void merge3sort(float* A, int l, int r ){
    if(l<r){
        int t=(r-l)/3;
        merge3sort(A,l,t+l);
        merge3sort(A,t+l+1,(2*t)+l);
        merge3sort(A,(2*t)+l+1,r);
        merge3(A,l,t+l,(2*t)+l,r);
    }
}
void mergesort(float *A, int l, int r){
    if(l<r){
        int m= floor((l+r)/2);
        mergesort(A,l,m);
        mergesort(A,m+1,r);
        merge(A,l,m,r);
    }
}
void merge4(float *A,int l,int c,int d_c,int t_c,int r){
    merge(A,l,c,d_c);
    merge(A,d_c+1,t_c,r);
    merge(A,l,d_c,r);
}
void mergesort4(float *A,int l, int r){
    if(l<r){
        int m=floor((r-l)/4);
        mergesort4(A,l,m+l);
        mergesort4(A,(m+1)+l,(2*m)+l);
        mergesort4(A,((2*m)+1)+l,(3*m)+l);
        mergesort4(A,((3*m)+1)+l,r);
        merge4(A,l,m+l,(2*m)+l,(3*m)+l,r);
    }
}
int main() {
    auto start=chrono::high_resolution_clock::now();
    auto end=chrono::high_resolution_clock::now();
    auto time=chrono::duration_cast<chrono::nanoseconds>(end-start).count();
    double total=0;
    float* A;
    int n;
    cout<<"Tamaño del arreglo: ";
    cin>>n;
    A=new float[n];
    for(int i=0;i<50;i++){ //EJECUTO 50 VECES PARA CALCULAR PROMEDIO DE TIEMPO
        //cout<<"creando arreglo"<<endl;
        for(int i=0; i<n;i++){
            float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/2));
            A[i]=r;
        }
        //cout<<"arreglo creado"<<endl;
        start=chrono::high_resolution_clock::now();
        mergesort4(A,0,n-1);
        //merge3sort(A,0,n-1);
        //mergesort(A,0,n-1);
        end=chrono::high_resolution_clock::now();
        time=chrono::duration_cast<chrono::milliseconds>(end-start).count();
        total+=time;
    }
    total/=50;
    cout << "\nmergesort4: "<<total/1000 <<"s"<<endl;
    delete[] A;
    return 0;
}