#ifndef SET_JOINT_POSITION_HH_
#define SET_JOINT_POSITION_HH_

#include <vector>

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

namespace gazebo
{
    class SetJointPosition : public ModelPlugin
    {
        public:
            using Float64MultiArray = std_msgs::msg::Float64MultiArray;

            SetJointPosition();
            virtual ~SetJointPosition();

            virtual void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);

        private:
            virtual void OnUpdate();
            void OnPositionCommand(const Float64MultiArray::SharedPtr msg);

            event::ConnectionPtr updateConnection_;

            std::vector<physics::JointPtr> joints_;

            rclcpp::Node::SharedPtr node_ptr_;
            rclcpp::Subscription<Float64MultiArray>::SharedPtr subscriber_;
            rclcpp::executors::SingleThreadedExecutor::SharedPtr executor_;
    };                           
}

#endif
