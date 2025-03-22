
#ifndef uav_kontrol_hpp
#define uav_kontrol_hpp

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


class UavKontrol {

private:

    std::shared_ptr<mavsdk::Action> action;

public:

    std::shared_ptr<mavsdk::Mavsdk> mavsdk;
    std::vector<std::shared_ptr<mavsdk::System>> systems;
    std::shared_ptr<mavsdk::System> uav_system;
    int k;
    
  UavKontrol(int sistem_id);
  void connect();
  void takeoff();
  void land();
  void telemetry_yaz();
  void sistem_bul();
  void konum_yaz();

};
#endif
