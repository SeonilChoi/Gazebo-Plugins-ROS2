#ifndef CUSTOM_JOINT_STATE_PUBLISHER_HH_
#define CUSTOM_JOINT_STATE_PUBLISHER_HH_

#include <vector>

#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

namespace gazebo
{
    class CustomJointStatePublisher : public ModelPlugin
    {
        public:
            using JointState = sensor_msgs::msg::JointState;

            CustomJointStatePublisher();
            virtual ~CustomJointStatePublisher();

            virtual void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf);

        private:
            virtual void OnUpdate();

            event::ConnectionPtr updateConnection_;
            
            physics::WorldPtr world_;
            std::vector<physics::JointPtr> joints_;

            rclcpp::Node::SharedPtr node_ptr_;
            rclcpp::Publisher<JointState>::SharedPtr publisher_;
            
            size_t length_;
    };                           
}

#endif
