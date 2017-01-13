/**
 @file    optimization_visualizer.h
 @author  Alexander W. Winkler (winklera@ethz.ch)
 @date    May 31, 2016
 @brief   Defines a class that visualizes the optimization values using ROS.
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ROS_OPTIMIZATION_VISUALIZER_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ROS_OPTIMIZATION_VISUALIZER_H_

#include <xpp/opt/i_visualizer.h>
#include <xpp/utils/state.h>
#include <xpp/opt/contact.h>

#include <ros/publisher.h>
#include <ros/subscriber.h>

namespace xpp {
namespace ros {

/** @brief Visualizes the current values of the optimization variables.
  *
  * This class is responsible for getting the state of the optimizaton
  * variables and generating ROS messages for rviz to visualize. The \c observer_
  * is responsible for supplying the interpreted optimization variables and
  * \c msg_builder_ is responsible for the generation of the ROS messages.
  */
class RosVisualizer : public xpp::opt::IVisualizer {
public:
  using State       = xpp::utils::StateLin2d;
  using VecContacts = std::vector<xpp::opt::Contact>;

  RosVisualizer();
  virtual ~RosVisualizer ();

  /** @brief Send a message with topic "optimization_variables" out to rviz */
  void Visualize() const override;

private:
  ::ros::Publisher ros_publisher_optimized_;
};

} /* namespace ros */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ROS_OPTIMIZATION_VISUALIZER_H_ */
