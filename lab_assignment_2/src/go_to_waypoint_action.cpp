#include "lab_assignment_2/my_action.h"
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseActionGoal.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <geometry_msgs/PoseStamped.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

namespace KCL_rosplan {

    MyActionInterface::MyActionInterface(ros::NodeHandle &nh) {
    // here the initialization
    }

    bool MyActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) 
    {
        // here the implementation of the action
        std::cout << "Going from " << msg->parameters[1].value << " to " << msg->parameters[2].value << std::endl;
        
        MoveBaseClient ac("move_base", true);

	    move_base_msgs::MoveBaseGoal goal;

        while(!ac.waitForServer(ros::Duration(5.0))){
            ROS_INFO("Waiting for the move_base action server to come up");
        }

        goal.target_pose.header.frame_id = "map";
        goal.target_pose.header.stamp = ros::Time::now();

        if(msg->parameters[2].value == "wp1"){
            goal.target_pose.pose.position.x = 6.0;
            goal.target_pose.pose.position.y = 2.0;
            goal.target_pose.pose.orientation.w = 1.0;
        }
        else if (msg->parameters[2].value == "wp2"){
            goal.target_pose.pose.position.x = 7.0;
            goal.target_pose.pose.position.y = -5.0;
            goal.target_pose.pose.orientation.w = 1.0;
        }
        else if (msg->parameters[2].value == "wp3"){
            goal.target_pose.pose.position.x = -3.0;
            goal.target_pose.pose.position.y = -8.0;
            goal.target_pose.pose.orientation.w = 1.0;
        }
        else if (msg->parameters[2].value == "wp4"){
            goal.target_pose.pose.position.x = -7.0;
            goal.target_pose.pose.position.y = -1.5;
            goal.target_pose.pose.orientation.w = 1.0;
        }
        else if (msg->parameters[2].value == "start"){
            goal.target_pose.pose.position.x = 0.0;
            goal.target_pose.pose.position.y = 1.0;
            goal.target_pose.pose.orientation.w = 1.0;
        }

        ac.sendGoal(goal);
        ac.waitForResult();
        
        
        if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        {
            ROS_INFO("Hooray, the base moved 1 meter forward");
            return true;
        }
        else
        {
            ROS_INFO("The base failed to move forward 1 meter for some reason");
            return false;
        }
        
    }
}
int main(int argc, char **argv) {
    ros::init(argc, argv, "my_rosplan_action", ros::init_options::AnonymousName);
    ros::NodeHandle nh("~");
    KCL_rosplan::MyActionInterface my_aci(nh);
    my_aci.runActionInterface();
    return 0;
}
