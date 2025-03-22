#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Float64.h>
#include <sstream>


 float aesk=10.0;
int main(int argc, char **argv)
{

  ros::init(argc, argv, "talker");


  ros::NodeHandle n; 


 ros::Publisher chatter_pub = n.advertise<std_msgs::Float64>("baho", 10);

  ros::Rate loop_rate(10); //10hz


  int count = 0;
  while (ros::ok())
  {

     
    aesk++;
    std_msgs::Float64 msg;
    msg.data = aesk;
    ROS_INFO("%f", msg.data);
    chatter_pub.publish(msg);


    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
