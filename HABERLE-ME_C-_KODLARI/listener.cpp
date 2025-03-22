#include "ros/ros.h"
#include "std_msgs/String.h"
#include <std_msgs/Float64.h>
#include <iostream>

float x;

class iha
{
private:
    float konum;

public:
    void set(float a)
    {
        konum = a;
    }

    void sub(ros::NodeHandle &n)
    {
        ros::Subscriber sub = n.subscribe("baho", 10, &iha::chatterCallback, this);
        ros::spin();
    }

    void chatterCallback(const std_msgs::Float64::ConstPtr &msg)
    {
        x = msg->data;
        ROS_INFO("I heard: [%f]", x);
    }
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;

    iha uav;
    uav.sub(n);

    return 0;
}

