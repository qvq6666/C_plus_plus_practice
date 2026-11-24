#include <iostream>
#include <string>
using namespace std;
template<typename temp>
void cout_arr(temp *&arr,int len){
    for (int i = 0; i < len; i++){
        cout<<"{"<<arr[i]<<"}";
    }
}
template<typename temp>
void remove_val(temp *&arr,int &len,temp see){
    int time = 0;
    for (int i = 0; i < len; i++){
        if (arr[i]==see){
            time+=1;
        }
    }
    temp *new_arr = new temp[len-time];
    int new_arr_i = 0;
    for (int arr_i = 0 ; arr_i < len; arr_i++){
        if (arr[arr_i]!=see){
            new_arr[new_arr_i] = arr[arr_i];
            new_arr_i += 1;
        }
    }
    delete[] arr;
    arr = new_arr;
    len -= time;
}
template<typename temp>
bool insert(temp *&arr,int &len,int see,temp new_val){
    if (see > len or see < 0){
        return false;    
    }
    temp *new_arr = new temp[len+1];
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
    return true;
}
template<typename temp>
void append(temp *&arr,int &len,temp new_val){
    temp *new_arr = new temp[len+1];
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
    string *arr = new string[len]{"Hello"," "};
    append(arr,len,string("World"));
    insert(arr,len,3,string("!"));
    append(arr,len,string("!"));
    remove_val(arr,len,string("!"));
    cout_arr(arr,len);
    delete[] arr;
    return 0;
}