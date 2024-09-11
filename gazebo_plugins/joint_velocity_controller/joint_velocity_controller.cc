#include "joint_velocity_controller.hh"

#include <string>

using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(JointVelocityController)

JointVelocityController::JointVelocityController() : ModelPlugin(), velocity_(0.0)
{}

JointVelocityController::~JointVelocityController()
{}

void JointVelocityController::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
{
    std::string joint_name = _sdf->Get<std::string>("joint_name");
    
    updateConnection_ = event::Events::ConnectWorldUpdateBegin(
        std::bind(&JointVelocityController::OnUpdate, this));

    joint_ = _parent->GetJoint("prismatic_joint");

    node_ptr_ = rclcpp::Node::make_shared(joint_name + "_velocity_controller_node");
    
    subscriber_ = node_ptr_->create_subscription<Float64>("velocity_command", 1, 
        [this](const Float64::SharedPtr msg){ OnVelocityCommand(msg); });
    
    executor_ = rclcpp::executors::SingleThreadedExecutor::make_shared();
    executor_->add_node(node_ptr_);    
}

void JointVelocityController::OnUpdate()
{
    this->executor_->spin_once(std::chrono::nanoseconds(100));
    joint_->SetVelocity(0, velocity_);
}

void JointVelocityController::OnVelocityCommand(const Float64::SharedPtr msg)
{
    velocity_ = msg->data;
}
