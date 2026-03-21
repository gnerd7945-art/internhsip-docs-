inheritance: is-a , composition: has-a 
  // truck has an engine , ship has an  engine.
  class Engine{
private:
int PowerValue;
string Engine_type;
public:
   Engine(int power, string name):PowerValue(power),type(name){};
int get_power(){
  return PowerValue;
}
string get_type(){
  return type;
}
//setter
void set_power(int p){
  PowerValue = p;
}
void set_engine_type(string name){
  Engine_type = name;
}
};

class Truck{
private:
 string name;
 int load;
 Engine* engine;  // declared in private variable, pointer provide riuntime polymorphism, we could use different child engine. using Engine engine instead would make us stuck with only one type. 
public:
 Truck(string n,int l,int P,string engine_name): name(n),load(l){
   engine = new Engine(p,engine_name); // used in constructor
 };
void specs(){
  std::cout<<"my specs:" <<name<<","<<load<<","<<engine->get_power()<<","<<engine->get_type()<<std::endl;
}
void change_engine(int power,string name){
  engine->set_power(power); // here input params "power", setter function has 'p'
  engine-> set_type(name)
}
~Truck(){ // destructor needed to remove memory allocated to pointer, notice destructor also takes input. Destructor is automaically called at end of function in which object created. If object itself is created using new , then call delete Truck truck, which will automatically delete engine. 
  delete engine;  
}
};
class Ship{
private:
 sting name;
 int load;
 Engine* engine; 
public:
 Ship(string n,int l,int P,string engine_name): name(n),load(l){
   engine = new Engine(p,engine_name);
 };
void specs(){
  std::cout<<"my specs:" <<name<<","<<load<<","<<engine->power<<","<<engine->type<<std::endl;
}
void change_engine(int power,string name){
  engine->set_power(power); // here input params "power", setter function has 'p'
  engine-> set_type(name)
}
~Ship(){ // destructor needed to remove memory allocated to pointer, notice destructor also takes input. 
  delete engine;
}
};
int main(){
  Truck truck( "tata",500,2000,"tata_enigne);
 truck.specs();
 truck.change_engine(3000,"updated_tata_engine");
 truck.specs();
return 0;
}
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  **some notes, notice that tuck and ship both are vehivle and could be inherited from a base class, named Vehicle. 
  this will help us prune redundunt variables, , you have name, load, and Engine* engine declared in both classes. If you decide later that every vehicle also needs a 
fuelLevel, you’d have to add it twice. With a base class, you declare these once in Vehicle. same for specs() method**

  





