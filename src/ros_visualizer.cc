/**
 @file    optimization_visualizer.cc
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 31, 2016
 @brief   Brief description
 */

#include <xpp/ros/ros_visualizer.h>
#include <xpp/ros/ros_helpers.h>
#include <xpp/ros/marker_array_builder.h>
#include <xpp/ros/topic_names.h>

namespace xpp {
namespace ros {

using VectorXd = Eigen::VectorXd;
using MarkerArray = visualization_msgs::MarkerArray;
using EndeffectorID = xpp::utils::EndeffectorID;

RosVisualizer::RosVisualizer ()
{
  ::ros::NodeHandle n;
  ros_publisher_optimized_ = n.advertise<MarkerArray>(xpp_msgs::rviz_optimized, 1);
}

RosVisualizer::~RosVisualizer ()
{
}

void
RosVisualizer::Visualize () const
{
  const auto com_motion = GetComMotion();
  auto structure        = GetMotionStructure();
  auto contacts         = GetContacts();
  auto leg_ids          = structure.GetContactIds();
  auto start_stance     = structure.GetStartStance();

  VecContacts footholds;
  for (int i=0; i<contacts.size(); ++i) {
    xpp::opt::Contact f;
    f.ee    = static_cast<EndeffectorID>(leg_ids.at(i));
    f.p.x() = contacts.at(i).x();
    f.p.y() = contacts.at(i).y();
    f.p.z() = 0.0;
    footholds.push_back(f);
  }





  MarkerArray msg;
  MarkerArrayBuilder msg_builder_;
  msg_builder_.AddStartStance(msg, start_stance);
  msg_builder_.AddFootholds(msg, footholds, "footholds", visualization_msgs::Marker::CUBE, 1.0);
  msg_builder_.AddSupportPolygons(msg, structure, contacts);
  msg_builder_.AddCogTrajectory(msg, *com_motion, structure, "cog", 1.0);
  msg_builder_.AddZmpTrajectory(msg, *com_motion, structure, 0.58, "zmp_4ls", 0.2);



//  double gap_center_x = 0.45;
//  double gap_width_x = 0.2;
//  double ellipse_width = 1.0;
//  msg_builder_.AddLineStrip(msg, gap_center_x, gap_width_x, "gap");
//  msg_builder_.AddEllipse(msg, gap_center_x, 0.0, gap_width_x, ellipse_width, "ellipse");

//  static int n_markers_first_iteration = msg.markers.size();
//  for (int i=n_markers_first_iteration; i<msg.markers.size(); ++i) {
//    msg.markers.at(i).type = visualization_msgs::Marker::DELETE;
//    msg.markers.at(i).color.a = 0.0;
//  }

  ros_publisher_optimized_.publish(msg);
}

} /* namespace ros */
} /* namespace xpp */
