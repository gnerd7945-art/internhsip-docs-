// passing references in cpp:-
  void add(int *num){ // num pointer to 'a'
 *num = 2+ *num;
}
int main(){
int a;
printf(add(&a));
}
