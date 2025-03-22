#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"

bool yaz(beginner_tutorials::AddTwoInts::Request  &req,
         beginner_tutorials::AddTwoInts::Response &res)
{
  ROS_INFO("request: x=%lf, y=%lf", (double)req.a, (double)req.b);
  res.xx = req.a;
  res.yy = req.b;
  ROS_INFO("sending back response: xx = [%lf] yy=%lf   ", (double)res.xx, (double)res.yy);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "IHA_s");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("IHA_KONUM", yaz);
  ros::spin();

  return 0;
}
