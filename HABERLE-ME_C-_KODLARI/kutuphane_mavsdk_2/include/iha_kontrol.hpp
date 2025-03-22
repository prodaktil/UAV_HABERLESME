
#ifndef iha_kontrol_hpp
#define iha_kontrol_hpp

#include <chrono>
#include <cmath>
#include <thread>
#include <iostream>
#include <future>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/offboard/offboard.h>

class DroneController {

private:
    std::shared_ptr<mavsdk::Mavsdk> mavsdk;
    std::shared_ptr<mavsdk::Telemetry> telemetry;
    std::shared_ptr<mavsdk::Action> action;
    std::future<void> telemetry_thread;
    float x,y,z;
    
public:
    DroneController();

    void connect(const std::string& connection_url);
    
    void start();
    
    void printTelemetry();
    void set_velocity(mavsdk::Offboard& offboard);
    void land();
    void takeoff();
    int hz_set();
   
    std::shared_ptr<mavsdk::System> get_system(mavsdk::Mavsdk& mavsdk);
};
#endif
