#include "iha_kontrol.hpp"

using namespace std;
using namespace mavsdk;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;

int main() {
    DroneController iha;
    
    iha.connect("udp://:14540");
   std::this_thread::sleep_for(std::chrono::seconds(5));
    iha.takeoff();
    std::this_thread::sleep_for(std::chrono::seconds(10)); 
    iha.hz_set();

    std::this_thread::sleep_for(std::chrono::seconds(10)); 
    iha.land();
    
    
    //Mavsdk mavsdk;
    //auto system = iha.get_system(mavsdk);
    //auto offboard = Offboard{system};
  // iha.set_velocity(offboard);


    return 0;
    
}