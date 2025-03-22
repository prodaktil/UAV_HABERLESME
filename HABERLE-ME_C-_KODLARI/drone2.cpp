#include <iostream>
#include <future>
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/action/action.h>

class DroneController {
public:
 DroneController() : mavsdk(std::make_shared<mavsdk::Mavsdk>()) {}

 void connect(const std::string& connection_url) {
     mavsdk::ConnectionResult connection_result = mavsdk->add_any_connection(connection_url);
     if (connection_result != mavsdk::ConnectionResult::Success) {
         std::cerr << "Connection error: " << connection_result << std::endl;
         return;
     }
     std::cout << "Connected to drone!" << std::endl;
 }

 void start() {
     std::cout << "Starting telemetry..." << std::endl;

     if (mavsdk->systems().size() == 0) {
         std::cerr << "No systems found!" << std::endl;
         return;
     }
     telemetry = std::make_shared<mavsdk::Telemetry>(*(mavsdk->systems()[0]));
     // Subscribe to telemetry updates here...
 }

 void takeoff() {
     std::vector<std::shared_ptr<mavsdk::System>> systems = mavsdk->systems();
     if (systems.size() == 0) {
         std::cerr << "No systems found!" << std::endl;
         return;
     }


     action = std::make_shared<mavsdk::Action>(*systems[0]);
     const auto arm_result = action->arm();
     std::this_thread::sleep_for(std::chrono::seconds(2));
     const auto takeoff_result = action->takeoff();
     
     if (takeoff_result != mavsdk::Action::Result::Success) {
         std::cerr << "Takeoff error: " << takeoff_result << std::endl;
         return;
     }
     std::cout << "Drone is taking off!" << std::endl;
 }

 void land() {
     const auto land_result = action->land();
     if (land_result != mavsdk::Action::Result::Success) {
         std::cerr << "Landing error: " << land_result << std::endl;
         return;
     }
     std::cout << "Drone is landing!" << std::endl;
 }

private:
 std::shared_ptr<mavsdk::Mavsdk> mavsdk;
 std::shared_ptr<mavsdk::Telemetry> telemetry;
 std::shared_ptr<mavsdk::Action> action;
};

int main() {
 DroneController drone;
 drone.connect("udp://:14540");
  std::this_thread::sleep_for(std::chrono::seconds(5));
 drone.start();
 drone.takeoff();
 std::this_thread::sleep_for(std::chrono::seconds(10));
 drone.land();
 
 return 0;
}
