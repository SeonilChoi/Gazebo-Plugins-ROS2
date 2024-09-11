#include "set_joint_velocity.hh"

#include <string>

using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(SetJointVelocity)

SetJointVelocity::SetJointVelocity() : ModelPlugin()
{}

SetJointVelocity::~SetJointVelocity()
{}

void SetJointVelocity::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
{
    updateConnection_ = event::Events::ConnectWorldUpdateBegin(
        std::bind(&SetJointVelocity::OnUpdate, this));

    std::string ns;
    sdf::ElementPtr element = _sdf->GetFirstElement();
    while (element != nullptr){
        if (element->GetName() == "namespace"){
            ns = element->Get<std::string>();
        } else {
            joints_.push_back(_parent->GetJoint(element->Get<std::string>()));
        }
        element = element->GetNextElement();
    }

    node_ptr_ = rclcpp::Node::make_shared("set_velocity_node", ns);
    
    subscriber_ = node_ptr_->create_subscription<Float64MultiArray>("joint_velocity_command", 1, 
        [this](const Float64MultiArray::SharedPtr msg){ OnVelocityCommand(msg); });
    
    executor_ = rclcpp::executors::SingleThreadedExecutor::make_shared();
    executor_->add_node(node_ptr_);    
}

void SetJointVelocity::OnUpdate()
{
    executor_->spin_once(std::chrono::nanoseconds(100));
}

void SetJointVelocity::OnVelocityCommand(const Float64MultiArray::SharedPtr msg)
{
    auto joint_it = joints_.begin();
    for (const auto & val : msg->data){
        (*joint_it)->SetVelocity(0, val);
        ++joint_it;
    }
}
