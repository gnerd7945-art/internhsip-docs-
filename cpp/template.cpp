#include <iostream> 
#include<vector>

template<typename T>
class Array{
    public:
        std::vector<T> array;
        T size =0;
        T sum =0;

        Array(std::vector<T>& arr, T s): array(std::move(arr)), size(s){}

        Array() = default;

        const T& ReturnSum(){
            for(const T& i: array ){
                sum+=i;
            }
            return sum;
        } 
        template<typename U>
        U test(const U& var);

};

template<typename T> 
template<typename U>
U Array<T>::test(const U& var){
     std::cout<<var<<std::endl;
     return var;
        }

        // class template specialization 

template<>
class Array<bool> {
public:
    int i;
    void func(){
        std::cout<<"hi"<<std::endl;
    }
};

int main(){
    std::vector<int> v{1,2,3,4,5};
    std::vector<double> v1{v.begin(),v.end()};
    Array<int> a(v,v.size());
    Array<double> b(v1,v1.size());
    auto r = a.ReturnSum();
    auto r1 = b.ReturnSum();

    bool var = a.test(true);
    std::cout<<var<<"\n";
    std::cout<<r<<r1<<std::endl;

    Array<bool> ba;
    ba.func();
    return 0;
}
