#ifndef MYLIBRARY_H
#define MYLIBRARY_H

#include <string>
#include <memory>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/action/action.h>

class MyDroneController {
public:
    MyDroneController();
    ~MyDroneController();

    void connect(const std::string& connection_url);
    void setSpeed(float speed_m_s);

private:
    std::shared_ptr<mavsdk::Mavsdk> drone;
    std::shared_ptr<mavsdk::Action> action;
};

#endif // MY_DRONE_CONTROLLER_H

