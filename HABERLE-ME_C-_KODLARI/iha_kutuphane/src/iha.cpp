#include "iha_kontrol.hpp"
#include<iostream>
using namespace std;
using namespace mavsdk;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;

int main() {
   int x=2;
  DroneController iha;          
  
  iha.connect("udp://:14540");
  std::this_thread::sleep_for(std::chrono::seconds(5));
 iha.gps_veri();
 iha.start();

  iha.transformation();
   std::this_thread::sleep_for(std::chrono::seconds(5));

  iha.takeoff();
  std::this_thread::sleep_for(std::chrono::seconds(10));



  //iha.git();
  //iha.hiz_body_set();
  iha.circle(100.0);
  std::this_thread::sleep_for(std::chrono::seconds(10));
 // iha.git_offb_ned();
    

 // while (x!=1){ 
  //cout<<"\n x eksenindeki hizini girin \n";
  //cin>> x ;
  //iha.hiz_set(x ,100.0, 100.0, 90.0);
  //std::this_thread::sleep_for(std::chrono::seconds(3));
  // x = iha.hiz_body_set(); 
   //x = iha.dalis_modu2();
 // }

 //  iha.land();
    
    
    //Mavsdk mavsdk;
    //auto system = iha.get_system(mavsdk);
    //auto offboard = Offboard{system};
  // iha.set_velocity(offboard);

    return 0;
}