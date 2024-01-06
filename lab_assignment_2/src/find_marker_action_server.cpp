#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <lab_assignment_2/FindMarkerAction.h>
#include <std_msgs/Int32.h>

class FindMarkerActionServer {
public:
    FindMarkerActionServer(ros::NodeHandle nh) : nh_(nh), as_(nh, "find_marker", boost::bind(&FindMarkerActionServer::executeCallback, this, _1), false) {
        as_.start();
        marker_pub_ = nh_.advertise<std_msgs::Int32>("/rosbot/search_id", 10);
        found_sub_ = nh_.subscribe("/rosbot/marker_found", 1, &FindMarkerActionServer::foundCallback, this);
    }

    void executeCallback(const lab_assignment_2::FindMarkerGoalConstPtr &goal) {
        // Publish marker request
        std_msgs::Int32 id = goal;
        marker_pub_.publish(id);

        // Wait for marker found
        while (!marker_found_) {
            ros::spinOnce();
            ros::Duration(0.1).sleep();  // adjust sleep duration as needed
        }

        lab_assignment_2::FindMarkerResult result;
        result.result = true;
        as_.setSucceeded(result);
    }

    void foundCallback(const std_msgs::Empty::ConstPtr& msg) {
        marker_found_ = true;
    }

private:
    ros::NodeHandle nh_;
    actionlib::SimpleActionServer<lab_assignment_2::FindMarkerAction> as_;
    ros::Publisher marker_pub_;
    ros::Subscriber found_sub_;
    bool marker_found_ = false;
};

int main(int argc, char** argv) {
    ros::init(argc, argv, "find_marker_server");
    ros::NodeHandle nh;

    FindMarkerActionServer server(nh);

    ros::spin();

    return 0;
}
