#include "mylibrary.hpp"

MyDroneController::MyDroneController() :
    drone(std::make_shared<mavsdk::Mavsdk>()) {}

MyDroneController::~MyDroneController() {}

void MyDroneController::connect(const std::string& connection_url) {
    drone->add_any_connection(connection_url);
    drone->connect().wait();
}

void MyDroneController::setSpeed(float speed_m_s) {
    action = std::make_shared<mavsdk::Action>(*drone);
    action->set_velocity_ned({speed_m_s, 0.0, 0.0}).wait();
}




