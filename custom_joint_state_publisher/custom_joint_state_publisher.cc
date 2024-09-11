#include "custom_joint_state_publisher.hh"

using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(CustomJointStatePublisher)

CustomJointStatePublisher::CustomJointStatePublisher() : ModelPlugin()
{}

CustomJointStatePublisher::~CustomJointStatePublisher()
{}

void CustomJointStatePublisher::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
{
    updateConnection_ = event::Events::ConnectWorldUpdateBegin(
        std::bind(&CustomJointStatePublisher::OnUpdate, this));
    
    world_ = _parent->GetWorld();

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
    length_ = joints_.size(); 

    node_ptr_ = rclcpp::Node::make_shared("joint_state_publisher", ns);
    
    publisher_ = node_ptr_->create_publisher<JointState>("joint_states", 1);
}

void CustomJointStatePublisher::OnUpdate()
{ 
    JointState msg;

    auto sim_time = world_->SimTime();
    msg.header.stamp.sec = sim_time.sec;
    msg.header.stamp.nanosec = sim_time.nsec;
    
    msg.position.reserve(length_);
    msg.velocity.reserve(length_);
    msg.effort.reserve(length_);
    for (const auto & joint : joints_){
        msg.position.push_back(joint->Position(0));
        msg.velocity.push_back(joint->GetVelocity(0));
        msg.effort.push_back(joint->GetForce(0));
    }

    publisher_->publish(msg);
}
