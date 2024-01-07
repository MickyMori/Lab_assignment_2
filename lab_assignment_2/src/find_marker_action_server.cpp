#include <ros/ros.h>
#include <unistd.h>
#include <iostream>
#include <actionlib/server/simple_action_server.h>
#include <lab_assignment_2/FindMarkerAction.h>
#include <std_msgs/Int32.h>
#include <lab_assignment_2/Marker.h>
#include <geometry_msgs/Twist.h>

class FindMarkerActionServer {
public:
    FindMarkerActionServer(ros::NodeHandle nh) : nh_(nh), as_(nh, "find_marker", boost::bind(&FindMarkerActionServer::executeCallback, this, _1), false) {
        as_.start();
        marker_pub_ = nh_.advertise<std_msgs::Int32>("/rosbot/search_id", 10);
        cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
        found_sub_ = nh_.subscribe("/rosbot/marker_found", 1, &FindMarkerActionServer::foundCallback, this);
    }

    void rotate_rosbot(double ang_z)
    {
        geometry_msgs::Twist cmd_vel_msg;
        cmd_vel_msg.angular.z = ang_z;
        cmd_vel_pub_.publish(cmd_vel_msg);
    }

    void executeCallback(const lab_assignment_2::FindMarkerGoalConstPtr &goal) {
        // Publish marker request

        id.data = goal->goal;
        std::cout << "Finding "<< id.data << std::endl;
        marker_pub_.publish(id);

        marker_found_ = false;

        rotate_rosbot(0.8);

        // Wait for marker found
        while (!marker_found_) {
            ros::spinOnce();
            ros::Duration(0.1).sleep();  // adjust sleep duration as needed
        }

        rotate_rosbot(0.0);

        std::cout << "Found "<< id.data << std::endl;
        as_.setSucceeded();
    }

    void foundCallback(const lab_assignment_2::Marker msg) {
        if((msg.id == id.data))
        {
            marker_found_ = true;
        }
    }

private:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<lab_assignment_2::FindMarkerAction> as_;
    ros::Publisher marker_pub_;
    ros::Publisher cmd_vel_pub_;
    ros::Subscriber found_sub_;
    bool marker_found_ = false;
    std_msgs::Int32 id;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "find_marker_server");
    ros::NodeHandle nh;

    FindMarkerActionServer server(nh);

    ros::spin();

    return 0;
}
