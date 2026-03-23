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
  std::cout<<"my specs:" <<name<<","<<load<<","<<engine->get_power()<<","<<engine->get_type()<<std::endl; // cant acess engine->PowerValue and engine->Engine_type directly as they are private. 
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
  std::cout<<"my specs:" <<name<<","<<load<<","<<engine->get_power()<<","<<engine->get_type()<<std::endl;
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
  this will help us prune redundant variables, , you have name, load, and Engine* engine declared in both classes. If you decide later that every vehicle also needs a 
fuelLevel, you’d have to add it twice. With a base class, you declare these once in Vehicle. same for specs() method**
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
class Vehicle{
private:
string name;
int load;
Engine* engine; 
public: 
Vehicle(string name, int load, int PowerValue, string Enigne_Type): name(name),load(load){
  engine = new Engine(PowerValue,Engine_Type);}
void specs(){
    std::cout<<"my specs:" <<name<<","<<load<<","<<engine->get_power()<<","<<engine->get_type()<<std::endl;
}
void change_engine(int Power, string name){
  engine->set_power(Power);
  engine->set_engine_type(name);
}
~Vehicle(){
  delete engine;
}   
};
class Truck :: public Vehicle{
public:
 Truck(string name, int load, int PowerValue, string Enigne_Type): Vehicle(name, load,PowerValue,Engine_Type){ // vehicle constructor called. 
   std::cout<<"TRuck created"<<std::endl;
     }
};
class Ship{
 public:
Ship{
using Vehicle::Vehicle; // tells Shipe to use Vehicle constructor
};
int main(){
  Truck truck( "tata",500,2000,"tata_enigne);
 truck.specs();
 truck.change_engine(3000,"updated_tata_engine");
 truck.specs();
return 0;
}
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*We are still harcoding type of Engine in vehical class, what if n number of engine are there, to create an object with different engines we use dependecy injection.*
 class Engine{
private:
int PowerValue;
string Engine_name;
public:
   Engine(int power, string name):PowerValue(power),name(name){};
int get_power(){
  return PowerValue;
}
string get_name(){
  return Engine_name;
}
//setter
void set_power(int p){
  PowerValue = p;
}
void set_engine_name(string name){
  Engine_name= name;}
virtual void get_specs(string fuel_name){} =0;
};
class Turbo_engine: public
class Vehicle{
private:
string name;
int load;
Engine* engine; 
public: 
Vehicle(string name, int load, int PowerValue, string Enigne_name,Engine* e): name(name),load(load){
  engine =e;}
void specs(){
    std::cout<<"my specs:" <<name<<","<<load<<","<<engine->get_power()<<","<<engine->get_name(),"using engine:"<<engine->get_specs()<<std::endl;
}
void change_engine(int Power, string name){
  engine->set_power(Power);
  engine->set_engine_name(name);
}
~Vehicle(){
  delete engine;
}   
};
class Truck :: public Vehicle{
public:
 Truck(string name, int load, int PowerValue, string Enigne_name,Engine* e): Vehicle(name, load,PowerValue,Engine_name,e){ // vehicle constructor called. 
   std::cout<<"TRuck created in truck class, attributs handeled by Vehicle base class"<<std::endl;
     }
};
class Ship{
 public:
  using Vehicle::Vehicle; // tells Ship to use Vehicle constructor
};
int main(){
  Enigne* e1 = new turboEngine("jet_fuel");
  Enigne* e2 =- new DIeselEngine("diesel_fuel");
  Truck truck( "tata",500,2000,"tata_enigne",e1);
 truck.specs();
 truck.change_engine(3000,"updated_tata_engine");
 truck.specs();
return 0;
}





