#ifndef GAZEBO_SET_POSITION_PLUGIN_HH_
#define GAZEBO_SET_POSITION_PLUGIN_HH_

#include <ignition/math/Vector3.hh>

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

#include "rclcpp/rclcpp.hpp"
#include "ttr_msgs/msg/motion.hpp"

namespace gazebo
{
    class SetPositionPlugin : public ModelPlugin
    {
        public:
            SetPositionPlugin();
            virtual ~SetPositionPlugin();

            virtual void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);

        private:
            virtual void OnUpdate();
            void OnPositionCommand(const ttr_msgs::msg::Motion::SharedPtr msg);

            event::ConnectionPtr updateConnection_;

            physics::ModelPtr model_;

            rclcpp::Node::SharedPtr node_ptr_;
            rclcpp::Subscription<ttr_msgs::msg::Motion>::SharedPtr position_sub_;
            rclcpp::executors::SingleThreadedExecutor::SharedPtr executor_;
            
            ignition::math::Pose3d goal_position_;
    };
}

#endif
