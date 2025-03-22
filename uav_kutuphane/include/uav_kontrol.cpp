#include "uav_kontrol.hpp"
#include <iostream>
#include <mavsdk/plugins/telemetry/telemetry.h>

#include <mavsdk/geometry.h>

using namespace std;
using namespace mavsdk;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;



UavKontrol::UavKontrol(int sistem_id) :  mavsdk(std::make_shared<mavsdk::Mavsdk> ()), k(sistem_id){
// systems = mavsdk->systems();
// uav_system = systems[k];
// takeoff();
// telemetry_yaz();
// std::this_thread::sleep_for(std::chrono::seconds(5));
}


void UavKontrol::takeoff()
{
    systems = mavsdk->systems();
    if (systems.size() == 0)
    {
        std::cerr << "No systems found!" << std::endl;
       return;
    }
    
    action = std::make_shared<mavsdk::Action>(systems[k]);
    const auto arm_result = action->arm();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    const auto takeoff_result = action->takeoff();

    if (takeoff_result != mavsdk::Action::Result::Success)
    {
        std::cerr << "Takeoff error: " << takeoff_result << std::endl;
        return;
    }
    std::cout << "Drone is taking off!" << std::endl;
}

void UavKontrol::land()
{
    const auto land_result = action->land();
    if (land_result != mavsdk::Action::Result::Success)
    {
        std::cerr << "Landing error: " << land_result << std::endl;
        return;
    }
    std::cout << "Drone is landing!" << std::endl;
}

void UavKontrol::telemetry_yaz(){
        if (systems.size() == 0)
    {
        std::cerr << "No systems found!" << std::endl;
       return;
    }
        auto telemetry = std::make_shared<mavsdk::Telemetry>(systems[k]);
        
        std::this_thread::sleep_for(std::chrono::seconds(2));

while(true){
        auto position = telemetry->position();
        cout<<"latitude:"<<position.latitude_deg<< std::endl;
        cout<<"longtitude:"<<position.longitude_deg<< std::endl;
        cout<<"absolute_altitude"<<position.absolute_altitude_m<< std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

}
}

void UavKontrol::konum_yaz() {
    auto systems = mavsdk->systems();
    if (systems.size() == 0) {
        std::cerr << "Sistem bulunamadi!" << std::endl;
        return;
    }

auto telemetry = std::make_shared<mavsdk::Telemetry>(systems[k]);

telemetry->subscribe_position([](mavsdk::Telemetry::Position position) {
    std::cout << "Position: " << position.latitude_deg << ", " << position.longitude_deg << std::endl;
});
}


void UavKontrol::sistem_bul() {

std::vector<std::shared_ptr<mavsdk::System>> systems = mavsdk->systems();

    for (size_t i = 0; i < systems.size(); i++) {
        auto system_id = systems[i]->get_system_id();
        cout << "sistem bulundu: system ID = " << static_cast<int>(system_id) << '\n';
    }
}
