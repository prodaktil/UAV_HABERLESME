
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
#include <mavsdk/geometry.h>


class DroneController {

private:
    std::shared_ptr<mavsdk::Mavsdk> mavsdk;
    std::shared_ptr<mavsdk::Telemetry> telemetry;
    std::shared_ptr<mavsdk::Action> action;
    std::future<void> telemetry_thread;
    float x,y,z;
    double a,b,c,d;

    
public:
    DroneController();

    void connect(const std::string& connection_url);
    
    void start();
    
    void printTelemetry();

    void land();
    void takeoff();
    int hiz_body_set();
   int hiz_set(float velocity_x, float velocity_y, float velocity_z , float yaw_x_y );
    std::shared_ptr<mavsdk::System> get_system(mavsdk::Mavsdk& mavsdk);
  int dalis_modu();
   int dalis_modu2();
     void git();
void git_offb();
void git_offb_ned();
void circle(double);
  void transformation();
  void gps_veri();
  int dal();

  
  }; 

#endif
