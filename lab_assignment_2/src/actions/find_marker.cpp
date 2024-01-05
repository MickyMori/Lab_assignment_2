#include "my_rosplan_interface/my_action.h" 
#include <unistd.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <rt2_packages/motion_plan/action/PlanningAction.h>

namespace KCL_rosplan {
    MyActionInterface::MyActionInterface(ros::NodeHandle &nh) {
	 search_sub = nh_.subscribe("/rosbot/search_id", 10, &MyActionInterface::search_callback, this); //create a sub to get the desired target

    }    
    
    void search_callback(const std_msgs::Int32 target_msg){
  	target = target_msg.data;
    }
  
    bool MyActionInterface::concreteCallback(const rosplan_dispatch_msgs::ActionDispatch::ConstPtr& msg) { //??????
        // here the implementation of the action
        /*std::cout << "Going back to the start " << msg->parameters[2].value << std::endl; 
        actionlib::SimpleActionClient<motion_plan::PlanningAction> ac("reaching_goal", true); //controllare che motion_plan::PlanningAction sia la cartella giusta
	motion_plan::PlanningGoal goal; //controllare che action::PlanningAction sia la cartella giusta
	ac.waitForServer();
	goal.target_pose.header.frame_id  =  "map";
	if(msg->parameters[2].value == "wp0"){
		goal.target_pose.pose.position.x = 0.0;
		goal.target_pose.pose.position.y = 0.0;
		goal.target_pose.pose.orientation.w = 1.0;
	}
	ac.sendGoal(goal);
	ac.waitForResult();
        ROS_INFO("Action (%s) performed: completed!", msg->name.c_str()); 
        return true;*/
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "find_marker", ros::init_options::AnonymousName); 
    ros::NodeHandle nh("~"); 
    KCL_rosplan::MyActionInterface my_aci(nh);
    my_aci.runActionInterface(); 
    return 0;
}
