/*****************************
 Copyright 2011 Rafael Muñoz Salinas. All rights reserved.

 Redistribution and use in source and binary forms, with or without modification, are
 permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of
 conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice, this list
 of conditions and the following disclaimer in the documentation and/or other materials
 provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY Rafael Muñoz Salinas ''AS IS'' AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Rafael Muñoz Salinas OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 The views and conclusions contained in the software and documentation are those of the
 authors and should not be interpreted as representing official policies, either expressed
 or implied, of Rafael Muñoz Salinas.
 ********************************/
/**
 * @file marker_publish.cpp
 * @author Bence Magyar
 * @date June 2014
 * @brief Modified copy of simple_single.cpp to publish all markers visible
 * (modified by Josh Langsfeld, 2014)
 */

#include <iostream>
#include <aruco/aruco.h>
#include <aruco/cvdrawingutils.h>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Empty.h>
#include <unistd.h>

class ArucoMarkerPublisher
{
private:
  // ArUco stuff
  aruco::MarkerDetector mDetector_;
  std::vector<aruco::Marker> markers_;
  aruco::CameraParameters camParam_;

  // node params
  double marker_size_;
  bool useCamInfo_;
  bool start = true;
  int target;

  // ROS pub-sub
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  ros::Subscriber search_sub;

  ros::Publisher marker_pub = nh_.advertise<std_msgs::Empty>("/rosbot/marker_found", 1);
  image_transport::Publisher image_pub_;
  //image_transport::Publisher debug_pub_;

  cv::Mat inImage_;
  
public:
  ArucoMarkerPublisher() :
      nh_("~"), it_(nh_), useCamInfo_(true)
  {
    image_sub_ = it_.subscribe("/camera/color/image_raw", 1, &ArucoMarkerPublisher::image_callback, this);
    search_sub = nh_.subscribe("/rosbot/search_id", 10, &ArucoMarkerPublisher::search_callback, this); //create a sub to get the desired target
    
    image_pub_ = it_.advertise("result", 1);
    //debug_pub_ = it_.advertise("debug", 1);
    
    nh_.param<bool>("use_camera_info", useCamInfo_, false);
    camParam_ = aruco::CameraParameters();
  }
  
  void search_callback(const std_msgs::Int32 target_msg){
  	target = target_msg.data;
  }

  void image_callback(const sensor_msgs::ImageConstPtr& msg)
  {
    bool publishImage = image_pub_.getNumSubscribers() > 0;
    //bool publishDebug = debug_pub_.getNumSubscribers() > 0;

    ros::Time curr_stamp = msg->header.stamp;
    cv_bridge::CvImagePtr cv_ptr;
    
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      inImage_ = cv_ptr->image;
   
      // clear out previous detection results
      markers_.clear();

      // ok, let's detect
      mDetector_.detect(inImage_, markers_, camParam_, marker_size_, false);
      
      std_msgs::Empty empty_msg;

        for (std::size_t i = 0; i < markers_.size(); ++i)
        {
        	//only send information about the current target
        	if(markers_.at(i).id == target){
            marker_pub.publish(empty_msg);
        	}
        }

      // draw detected markers on the image for visualization
      for (std::size_t i = 0; i < markers_.size(); ++i)
      {
        markers_[i].draw(inImage_, cv::Scalar(0, 0, 255), 2);
      }
      // publish input image with markers drawn on it
      if (publishImage)
      {
        // show input with augmented information
        cv_bridge::CvImage out_msg;
        out_msg.header.stamp = curr_stamp;
        out_msg.encoding = sensor_msgs::image_encodings::RGB8;
        out_msg.image = inImage_;
        image_pub_.publish(out_msg.toImageMsg());
      }

      // publish image after internal image processing
      //if (publishDebug)
      //{
        // show also the internal image resulting from the threshold operation
        //cv_bridge::CvImage debug_msg;
        //debug_msg.header.stamp = curr_stamp;
        //debug_msg.encoding = sensor_msgs::image_encodings::MONO8;
        //debug_msg.image = mDetector_.getThresholdedImage();
        //debug_pub_.publish(debug_msg.toImageMsg());
      //}

    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
    }
  }
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "aruco_marker_publisher");

  ArucoMarkerPublisher node;

  ros::spin();
}
