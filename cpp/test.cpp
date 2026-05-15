#include<string>
#include<iostream>
int main(){
    int* ptr = new int(5);
  	for(int i =0;i<5;i++){
        ptr[i] = 11;
    }
      std::cout<< *ptr<<std::endl;
  return 0;

}