using namespace std;
// Including necessary C++ and ROS libraries
#include <iostream> /**< Standard input/output stream. */
#include <ros/ros.h> /**< ROS (Robot Operating System) library. */
#include <unistd.h> /**< Standard symbolic constants and types. */
#include <std_srvs/Empty.h>

int main(int argc, char **argv)
{
    // Initialize the ROS node
    ros::init(argc, argv, "logic_node");

    sleep(5);

    ros::NodeHandle n;
    ros::ServiceClient problem_generation = n.serviceClient<std_srvs::Empty>("/rosplan_problem_interface/problem_generation_server");
    ros::ServiceClient planner = n.serviceClient<std_srvs::Empty>("/rosplan_planner_interface/planning_server");
    ros::ServiceClient parser = n.serviceClient<std_srvs::Empty>("/rosplan_parsing_interface/parse_plan");
    ros::ServiceClient dispatcher = n.serviceClient<std_srvs::Empty>("/rosplan_plan_dispatcher/dispatch_plan");    
    std_srvs::Empty srv;

    if(problem_generation.call(srv))
    {
        if(planner.call(srv))
        {
            if(parser.call(srv))
            {
                if(dispatcher.call(srv))
                {

                }
                else
                {
                    ROS_ERROR("Failed to call dispatcher");
                    sleep(15);
                    return 1;
                }
            }
            else
            {
                ROS_ERROR("Failed to call parser");
                return 1;
            }
        }
        else
        {
            ROS_ERROR("Failed to call planner");
            return 1;
        }
    }
    else
    {
        ROS_ERROR("Failed to call problem generation server");
        return 1;
    }
    

    // Enter the ROS spin loop
    ros::spin();
}
