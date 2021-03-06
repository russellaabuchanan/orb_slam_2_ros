#ifndef ORB_SLAM_2_INTERFACE_STEREO
#define ORB_SLAM_2_INTERFACE_STEREO

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/Imu.h>

#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/time_synchronizer.h>

#include <string>

#include "orb_slam_2_ros/interface.hpp"

namespace orb_slam_2_interface {

// The synchronization policy used by the interface to sync stereo images
typedef message_filters::sync_policies::ApproximateTime<sensor_msgs::Image,
                                                        sensor_msgs::Image>
    sync_pol;

// Class handling global alignment calculation and publishing
class OrbSlam2InterfaceStereo : public OrbSlam2Interface {
 public:
  // Constructor
  OrbSlam2InterfaceStereo(const ros::NodeHandle& nh,
                          const ros::NodeHandle& nh_private);

 protected:
  // Subscribes to the appropriate ROS topics
  void subscribeToTopics();

  // Gets stereo rectification maps
  void stereoRectification();

  // Callbacks
  void stereoImageCallback(const sensor_msgs::ImageConstPtr& msg_left,
                           const sensor_msgs::ImageConstPtr& msg_right);

  #ifdef USE_IMU
  void ImuCallback(const sensor_msgs::Imu& imu);
  #endif

  // Subscribers
  std::shared_ptr<message_filters::Subscriber<sensor_msgs::Image>> left_sub_;
  std::shared_ptr<message_filters::Subscriber<sensor_msgs::Image>> right_sub_;
  std::shared_ptr<message_filters::Synchronizer<sync_pol>> sync_;
  ros::Subscriber imu_sub_;

  // Rectification maps
  cv::Mat left_rectification_map1_, left_rectification_map2_,
      right_rectification_map1_, right_rectification_map2_;

  // Rectification state
  bool stereo_rectified_;
};

}  // namespace orb_slam_2_interface

#endif /* ORB_SLAM_2_INTERFACE_STEREO */
