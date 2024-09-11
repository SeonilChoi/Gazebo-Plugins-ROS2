#include "set_joint_position.hh"

using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(SetJointPosition)

SetJointPosition::SetJointPosition() : ModelPlugin()
{}

SetJointPosition::~SetJointPosition()
{}

void SetJointPosition::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
{
    updateConnection_ = event::Events::ConnectWorldUpdateBegin(
        std::bind(&SetJointPosition::OnUpdate, this));
    
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
    
    node_ptr_ = rclcpp::Node::make_shared("set_joint_position_node", ns);
    
    subscriber_ = node_ptr_->create_subscription<Float64MultiArray>("joint_position_command", 1,
        [this](const Float64MultiArray::SharedPtr msg){ OnPositionCommand(msg); });

    executor_ = rclcpp::executors::SingleThreadedExecutor::make_shared();
    executor_->add_node(node_ptr_);
}

void SetJointPosition::OnUpdate()
{ 
    executor_->spin_once(std::chrono::nanoseconds(100));
}

void SetJointPosition::OnPositionCommand(const Float64MultiArray::SharedPtr msg)
{
    auto joint_it = joints_.begin();
    for (const auto & val : msg->data){
        (*joint_it)->SetPosition(0, val);
        ++joint_it;
    }
}
