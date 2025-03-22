
#include "iha_kontrol.hpp"
#include <iostream>
#include <mavsdk/plugins/telemetry/telemetry.h>

#include <mavsdk/geometry.h>

using namespace std;
using namespace mavsdk;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::this_thread::sleep_for;

DroneController::DroneController() : mavsdk(std::make_shared<mavsdk::Mavsdk>()) {}

void DroneController::connect(const std::string &connection_url)
{
    mavsdk::ConnectionResult connection_result = mavsdk->add_any_connection(connection_url);
    if (connection_result != mavsdk::ConnectionResult::Success)
    {
        std::cerr << "Connection error: " << connection_result << std::endl;
        return;
    }
    std::cout << "Connected to drone!" << std::endl;
}

void DroneController::start()
{
    std::cout << "Starting telemetry..." << std::endl;

    if (mavsdk->systems().empty())
    {
        std::cerr << "No systems found!" << std::endl;
        return;
    }

    telemetry = std::make_shared<mavsdk::Telemetry>(*(mavsdk->systems()[0]));

    // Start a separate thread to continuously print telemetry data
    telemetry_thread = std::async(std::launch::async, [this]()
                                  { printTelemetry(); });
}

void DroneController::printTelemetry()
{
    while (true)
    {
        const auto position = telemetry->position();
        auto head = telemetry->heading();
       d = head.heading_deg;
        a = position.latitude_deg;
        b = position.longitude_deg;
        c =  position.absolute_altitude_m;

        /*
        std::cout << "\nx " << x << std::endl
                  << "y " << y << std::endl
                  << "z " << z << std::endl;
                  */
        if (abs(270-d)<1 ){
            dalis_modu2();
            break;
        }
    }
}

void DroneController::takeoff()
{
    std::vector<std::shared_ptr<mavsdk::System>> systems = mavsdk->systems();
    if (systems.size() == 0)
    {
        std::cerr << "No systems found!" << std::endl;
        return;
    }

    action = std::make_shared<mavsdk::Action>(*systems[0]);
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

void DroneController::land()
{
    const auto land_result = action->land();
    if (land_result != mavsdk::Action::Result::Success)
    {
        std::cerr << "Landing error: " << land_result << std::endl;
        return;
    }
    std::cout << "Drone is landing!" << std::endl;
}

int DroneController::hiz_set(float velocity_x, float velocity_y, float velocity_z, float yaw_x_y)
{

    System &system = *mavsdk->systems().at(0);

    auto offboard = Offboard(system);

    Offboard::VelocityNedYaw velocity{};
    velocity.north_m_s = velocity_x;
    velocity.east_m_s = velocity_y;
    velocity.down_m_s = velocity_z;
    velocity.yaw_deg = yaw_x_y;

    Offboard::Result set_velocity_result = offboard.set_velocity_ned(velocity);

    if (set_velocity_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::set_velocity_ned() failed: " << set_velocity_result << '\n';
        return 1;
    }

    Offboard::Result offboard_result = offboard.start();

    if (offboard_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
        return 1;
    }

    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "Hiz setlendi" << std::endl;

    return 0;
}

int DroneController::hiz_body_set()
{

    System &system = *mavsdk->systems().at(0);
    auto offboard = Offboard(system);
    float hiz_x, hiz_y, hiz_z, yaw_x_y;
    int a;
    cout << " \n hiz değerlerini girin: ";

    cout << "\nileri yonlu hiz degerini girin:";
    cin >> hiz_x;
    cout << "\nyanal hiz degerini girin:";
    cin >> hiz_y;
    cout << "\ndikey hiz degerini girin:";
    cin >> hiz_z;
    cout << "\nacisal hiz degerini:";
    cin >> yaw_x_y;
    cout << "\nkodun durmasini istiyorsaniz 1'e basin:";
    cin >> a;
    if (a == 1)
    {
        return 1;
    }
    Offboard::VelocityBodyYawspeed velocity{};
    velocity.forward_m_s = hiz_x;
    velocity.right_m_s = hiz_y;
    velocity.down_m_s = hiz_z;
    velocity.yawspeed_deg_s = yaw_x_y;

    Offboard::Result set_velocity_result = offboard.set_velocity_body(velocity);

    if (set_velocity_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::set_velocity_ned() failed: " << set_velocity_result << '\n';
        return 1;
    }

    Offboard::Result offboard_result = offboard.start();

    if (offboard_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
        return 1;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Hiz setlendi" << std::endl;

    return 0;
}

int DroneController::dalis_modu()
{

    System &system = *mavsdk->systems().at(0);
    auto offboard = Offboard(system);
    float roll, pitch, yaw, th_value;
    int a;
    cout << " \n hiz değerlerini girin: ";

    cout << "\nroll_deg degerini girin:";
    cin >> roll;
    cout << "\npitch_deg degerini girin:";
    cin >> pitch;
    cout << "\nyaw_deg degerini girin:";
    cin >> yaw;
    cout << "\nthrust_value degerini girin:";
    cin >> th_value;
    cout << "\nkodun durmasini istiyorsaniz 1'e basin:";
    cin >> a;
    if (a == 1)
    {
        return 1;
    }
    Offboard::Attitude attitude{};
    attitude.roll_deg = roll;
    attitude.pitch_deg = pitch;
    attitude.yaw_deg = yaw;
    attitude.thrust_value = th_value;

    Offboard::Result set_attitude_result = offboard.set_attitude(attitude);

    if (set_attitude_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::set_velocity_ned() failed: " << set_attitude_result << '\n';
        return 1;
    }

    Offboard::Result offboard_result = offboard.start();

    if (offboard_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
        return 1;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Hiz setlendi" << std::endl;

    return 0;
}

int DroneController::dalis_modu2()
{

    System &system = *mavsdk->systems().at(0);
    auto offboard = Offboard(system);
    float roll, pitch, yaw, th_value;

    roll = 0.0;
    pitch = -45.0;
    yaw = 0.0;
    th_value = 10.0;

    Offboard::Attitude attitude{};
    attitude.roll_deg = roll;
    attitude.pitch_deg = pitch;
    attitude.yaw_deg = yaw;
    attitude.thrust_value = th_value;

    Offboard::Result set_attitude_result = offboard.set_attitude(attitude);

    if (set_attitude_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::set_velocity_ned() failed: " << set_attitude_result << '\n';
        return 0;
    }

    Offboard::Result offboard_result = offboard.start();

    if (offboard_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
        return 0;
    }

    std::cout << "\nDalis moduna gecildi" << std::endl;

   return 0;
}

void DroneController::git()
{
    action->goto_location(100.0, 100.0, 100.0, 0.0);

    std::cout << "pozisyona gidiliyor" << std::endl;
}

void DroneController::git_offb()
{

    System &system = *mavsdk->systems().at(0);
    auto offboard = Offboard(system);
    Offboard::PositionGlobalYaw positionGlobalYaw{};

    positionGlobalYaw.lat_deg = 10.0;
    positionGlobalYaw.lon_deg = 10.0;
    positionGlobalYaw.alt_m = 10.0;
    positionGlobalYaw.yaw_deg = 0.0;

    Offboard::Result set_attitude_result2 = offboard.set_position_global(positionGlobalYaw);

    if (set_attitude_result2 != Offboard::Result::Success)
    {
        std::cerr << "Offboard::.set_position_global failed: " << set_attitude_result2 << '\n';
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));

    Offboard::Result start_result = offboard.start();
    if (start_result != Offboard::Result::Success)
    {
        std::cerr << "Error: Failed to start offboard mode!" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "Flying to position..." << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));
}

void DroneController::git_offb_ned()
{

    System &system = *mavsdk->systems().at(0);
    auto offboard = Offboard(system);
    Offboard::PositionNedYaw positionNedYaw{};

    positionNedYaw.north_m = 100.0;
    positionNedYaw.east_m = 100.0;
    positionNedYaw.down_m = 100.0;
    positionNedYaw.yaw_deg = 0.0;

    Offboard::Result set_attitude_result4 = offboard.set_position_ned(positionNedYaw);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    Offboard::Result start_result4 = offboard.start();

    std::cout << "Flying to position..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(20));
}

void DroneController::circle(double yukseklik)
{
  std::vector<std::shared_ptr<mavsdk::System>> systems = mavsdk->systems();

    if (systems.size() == 0)
    {
        std::cerr << "No systems found!" << std::endl;
        return;
    }
    action = std::make_shared<mavsdk::Action>(*systems[0]);

    mavsdk::Action::OrbitYawBehavior daire;

    float radius_m = 20.0;
    float r = radius_m;
    float velocity_ms = 50.0;
    double latitude_deg = a;
    double longitude_deg = b;
    double absolute_altitude_m = c + yukseklik;
    action->do_orbit(radius_m, velocity_ms, daire, latitude_deg, longitude_deg, absolute_altitude_m);
}

void DroneController::transformation()
{

    std::vector<std::shared_ptr<mavsdk::System>> systems = mavsdk->systems();

    if (systems.size() == 0)
    {
        std::cerr << "No systems found!" << std::endl;
        return;
    }

    mavsdk::geometry::CoordinateTransformation::GlobalCoordinate globalcordinate{};
    globalcordinate.latitude_deg = a;
    globalcordinate.longitude_deg = b;
    auto trans = std::make_shared<mavsdk::geometry::CoordinateTransformation>(globalcordinate);

    // mavsdk::geometry::CoordinateTransformation::LocalCoordinate local_coordinate =  trans->local_from_global  (globalcordinate) ;
    mavsdk::geometry::CoordinateTransformation::LocalCoordinate local {};
    cout<<"cember cizilicek konumlari girin\n";
    cin>>local.north_m;
    cin>>local.east_m;
 

     mavsdk::geometry::CoordinateTransformation::GlobalCoordinate global = trans-> global_from_local(local);

   cout<<"\n kordinatlari yaziyor ... \n";
   a=global.latitude_deg;
   b= global.longitude_deg;
   cout<< global.latitude_deg<<endl;
   cout<<global.longitude_deg;
}

void DroneController::gps_veri(){

    System &system = *mavsdk->systems().at(0);
     auto telemetry = std::make_shared<mavsdk::Telemetry>(*(mavsdk->systems()[0]));
    


    auto gps = telemetry->position();

    double  x= gps.latitude_deg;
     double y= gps.longitude_deg;
     float z= gps.absolute_altitude_m;
    cout<<x<<endl;
    cout<<y<<endl;
    cout<<z<<endl;
   

    }


    int DroneController::dal()
{

    System &system = *mavsdk->systems().at(0);
    auto offboard = Offboard(system);
    float hiz_x, hiz_y, hiz_z, yaw_x_y;
  

    Offboard::VelocityBodyYawspeed velocity{};
    velocity.forward_m_s = 50;
    velocity.right_m_s = hiz_y;
    velocity.down_m_s = 50;
    velocity.yawspeed_deg_s = 45.0;

    Offboard::Result set_velocity_result = offboard.set_velocity_body(velocity);

    if (set_velocity_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::set_velocity_ned() failed: " << set_velocity_result << '\n';
        return 1;
    }

    Offboard::Result offboard_result = offboard.start();

    if (offboard_result != Offboard::Result::Success)
    {
        std::cerr << "Offboard::start() failed: " << offboard_result << '\n';
        return 1;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "45 derce dalisa gecidl" << std::endl;

    return 0;
}








