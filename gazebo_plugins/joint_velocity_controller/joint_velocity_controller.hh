#ifndef JOINT_VELOCITY_CONTROLLER_HH_
#define JOINT_VELOCITY_CONTROLLER_HH_

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

namespace gazebo
{
    class JointVelocityController : public ModelPlugin
    {
        public:
            using Float64 = std_msgs::msg::Float64;
            
            JointVelocityController();
            virtual ~JointVelocityController();

            virtual void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);
            
        private:
            virtual void OnUpdate();
            void OnVelocityCommand(const Float64::SharedPtr msg);

            event::ConnectionPtr updateConnection_;

            physics::JointPtr joint_;

            rclcpp::Node::SharedPtr node_ptr_;
            rclcpp::Subscription<Float64>::SharedPtr subscriber_;
            rclcpp::executors::SingleThreadedExecutor::SharedPtr executor_;

            double velocity_;
    };
}

#endif
