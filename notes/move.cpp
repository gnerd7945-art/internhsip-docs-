/* if we dealing with pointer use manual nulling, smart pointers can use move,  same for string objects(other objects too  that have move constructor in them),
 && was used so that move on obj could be applied and compiler does not flag it. , make it sound more brief with exmaple 
 2) return by vlaue returns rvalue(temporary)
 */
#include<iostream>

class My_class{
  public:
  int* ptr;
    //My_class(const int& ref):ptr(&ref){};  will not work as My_class(10) here 10 will exist for splitsecond after that, this memory contains garbage this ptr points to garbage.
    My_class(const int &ref){
        ptr = new int(ref);
        std::cout<< "mem allocated to ptr" <<std::endl;
    }
    My_class(My_class &obj){
        ptr = obj.ptr;  // not ptr = std::move(obj.ptr); beacue raw pointers are not objects which have move construvotr in them.
        obj.ptr = nullptr;
        std::cout<<*((*this).ptr)<<std::endl;
    }
    My_class(My_class &&obj) // explicitly says that this is temporary. so move in main could work. m
    {
        ptr = obj.ptr;
        obj.ptr = nullptr;
        std::cout<<"used explicit way to move:"<<*ptr<<std::endl;
    }
};
int main(){
    My_class my(200);
    My_class mine(my); // copy constructor logic to move constructor. 
    My_class mine2 = std::move(mine); // applying move on mine(permaennet object) makes compiler look for R_value construcotr in class if present. 
}
