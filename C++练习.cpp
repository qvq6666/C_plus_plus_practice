#include <iostream>
using namespace std;
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
int main(){
    int len = 5;
    int *arr = new int[len]{1,2,3,4,5};
    in(arr,len,5,6);
    for (int i = 0; i < len; i++){
        cout<<"{"<<arr[i]<<"}";
    }
    delete[] arr;
    return 0;
}