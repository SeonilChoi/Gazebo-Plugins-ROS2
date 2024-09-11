#include "set_joint_velocity.hh"

#include <string>

using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(SetJointVelocity)

SetJointVelocity::SetJointVelocity() : ModelPlugin(), velocity_(0.0)
{}

SetJointVelocity::~SetJointVelocity()
{}

void SetJointVelocity::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
{
    std::string joint_name = _sdf->Get<std::string>("joint_name");
    
    updateConnection_ = event::Events::ConnectWorldUpdateBegin(
        std::bind(&SetJointVelocity::OnUpdate, this));

    joint_ = _parent->GetJoint(joint_name);

    node_ptr_ = rclcpp::Node::make_shared("set_" + joint_name + "_velocity_node");
    
    subscriber_ = node_ptr_->create_subscription<Float64>(joint_name + "_velocity_command", 1, 
        [this](const Float64::SharedPtr msg){ OnVelocityCommand(msg); });
    
    executor_ = rclcpp::executors::SingleThreadedExecutor::make_shared();
    executor_->add_node(node_ptr_);    
}

void SetJointVelocity::OnUpdate()
{
    this->executor_->spin_once(std::chrono::nanoseconds(100));
    joint_->SetVelocity(0, velocity_);
}

void SetJointVelocity::OnVelocityCommand(const Float64::SharedPtr msg)
{
    velocity_ = msg->data;
}
