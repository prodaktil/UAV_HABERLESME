

#include "iha_kontrol.hpp"
using namespace std;
using namespace mavsdk;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;
    DroneController::DroneController() : mavsdk(std::make_shared<mavsdk::Mavsdk>()) {}

    void DroneController::connect(const std::string& connection_url) {
        mavsdk::ConnectionResult connection_result = mavsdk->add_any_connection(connection_url);
        if (connection_result != mavsdk::ConnectionResult::Success) {
            std::cerr << "Connection error: " << connection_result << std::endl;
            return;
        }
        std::cout << "Connected to drone!" << std::endl;
    }

    void DroneController::start() {
        std::cout << "Starting telemetry..." << std::endl;

        if (mavsdk->systems().empty()) {
            std::cerr << "No systems found!" << std::endl;
            return;
        }

        telemetry = std::make_shared<mavsdk::Telemetry>(*(mavsdk->systems()[0]));

        // Start a separate thread to continuously print telemetry data
        telemetry_thread = std::async(std::launch::async, [this]() { printTelemetry(); });
    }

	void DroneController::printTelemetry() {
    while (true) {
        const auto odometry = telemetry->odometry();
                   x = odometry.position_body.x_m;
                   y = odometry.position_body.y_m;
                   z = odometry.position_body.z_m;
        std::cout<<"\nx "<<x <<std::endl<<"y "<< y <<std::endl<<"z "<< z <<std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Adjust sleep duration as needed
     }
    }
    void DroneController::set_velocity(mavsdk::Offboard& offboard){
    const Offboard::VelocityNedYaw stay{};
    offboard.set_velocity_ned(stay);
    Offboard::VelocityNedYaw turn_east{}; 
    turn_east.yaw_deg = 90.0f;
    offboard.set_velocity_ned(turn_east);
    sleep_for(seconds(1));
    }




    
std::shared_ptr<System> DroneController::get_system(Mavsdk& mavsdk)
{
    std::cout << "Waiting to discover system...\n";
    auto prom = std::promise<std::shared_ptr<System>>{};
    auto fut = prom.get_future();

    // We wait for new systems to be discovered, once we find one that has an
    // autopilot, we decide to use it.
    mavsdk.subscribe_on_new_system([&mavsdk, &prom]() {
        auto system = mavsdk.systems().back();

        if (system->has_autopilot()) {
            std::cout << "Discovered autopilot\n";

            // Unsubscribe again as we only want to find one system.
            mavsdk.subscribe_on_new_system(nullptr);
            prom.set_value(system);
        }
    });

    // We usually receive heartbeats at 1Hz, therefore we should find a
    // system after around 3 seconds max, surely.
    if (fut.wait_for(seconds(3)) == std::future_status::timeout) {
        std::cerr << "No autopilot found.\n";
        return {};
    }

    // Get discovered system now.
    return fut.get();
}


 void DroneController::takeoff() {
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
 void DroneController::land() {
     const auto land_result = action->land();
     if (land_result != mavsdk::Action::Result::Success) {
         std::cerr << "Landing error: " << land_result << std::endl;
         return;
     }
     std::cout << "Drone is landing!" << std::endl;
 }
 
  int DroneController::hz_set() {

    Mavsdk mavsdk;
    
   // const ConnectionResult connection_result = mavsdk.add_udp_connection("udp://:14540");
        // std::this_thread::sleep_for(std::chrono::seconds(5));
/*
    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Connection error: " << connection_result << std::endl;
        return  1;
    }

    std::cout << "Connecting..." << std::endl;
          std::this_thread::sleep_for(std::chrono::seconds(5));

    // Wait until system is connected
    
    while (!system.is_connected()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
*/
    // Wait for the system to connect
  
   // std::this_thread::sleep_for(std::chrono::seconds(5));
    
    
 

    System& system = *mavsdk.systems().at(0);
    auto telemetry = Telemetry(system);
    auto offboard = Offboard(system);
    std::cout << "kontrol 3" << std::endl;

    // Set the velocity here
    const float velocity_x = 100.0f;
    const float velocity_y = 0.0f;
    const float velocity_z = 100.0f;

    Offboard::VelocityNedYaw velocity{};
    velocity.north_m_s = velocity_x;
    velocity.east_m_s = velocity_y;
    velocity.down_m_s = velocity_z;
    velocity.yaw_deg = 0.0f; // You can adjust the yaw here.
    std::cout << "kontrol 4" << std::endl;

    Offboard::Result set_velocity_result = offboard.set_velocity_ned(velocity);
    std::cout << "kontrol 5" << std::endl;

    if (set_velocity_result != Offboard::Result::Success) {
        std::cerr << "Offboard::set_velocity_ned() failed: " << set_velocity_result << '\n';
        return 1;
    }

    // Enter Offboard mode
    Offboard::Result offboard_result = offboard.start();

    if (offboard_result != Offboard::Result::Success) {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
        return 1;
    }

    // Wait for a while
    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "Hiz setlendi" << std::endl;

    return 0;
}

