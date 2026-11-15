#include <iostream>
using namespace std;
void cout_arr(int *&arr,int len){
    for (int i = 0; i < len; i++){
        cout<<"{"<<arr[i]<<"}";
    }
}
void in(int *&arr,int &len,int see,int new_val){
    int *new_arr = new int[len+1];
    bool s = false;
    for (int i = 0; i < len+1; i++){
        if (i == see){
            new_arr[i] = new_val;
            s = true;
        }
        else{
            if (s){
                new_arr[i] = arr[i-1];
            }
            else{
                new_arr[i] = arr[i];
            }
        }
    }
    delete[] arr;
    arr = new_arr;
    len += 1;
}
void append(int *&arr,int &len,int new_val){
    int *new_arr = new int[len+1];
    for (int i = 0; i < len; i++){
        new_arr[i] = arr[i];
    }
    new_arr[len] = new_val;
    delete[] arr;
    arr = new_arr;
    len += 1;
}
int main(){
    int len = 2;
    int *arr = new int[len]{1,1};
    for (int i = 2; i < 5; i++){
        append(arr,len,arr[i-1]+arr[i-2]);
    }
    cout_arr(arr,len);
    delete[] arr;
    return 0;
}