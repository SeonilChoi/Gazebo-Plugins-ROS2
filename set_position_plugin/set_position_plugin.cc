#include "set_position_plugin.hh"

using namespace gazebo;

GZ_REGISTER_MODEL_PLUGIN(SetPositionPlugin)

SetPositionPlugin::SetPositionPlugin() : ModelPlugin()
{}

SetPositionPlugin::~SetPositionPlugin()
{}

void SetPositionPlugin::Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
{
    this->updateConnection_ = event::Events::ConnectWorldUpdateBegin(std::bind(&SetPositionPlugin::OnUpdate, this));
    
    this->model_            = _parent;

    ignition::math::Vector3 position(-0.975, 0.0, 0.665);
    ignition::math::Quaternion quaternion(1.0, 0.0, 0.0, 0.0);
    ignition::math::Pose3d init_position;
    
    init_position.Set(position, quaternion);
    
    model_->SetWorldPose(init_position);

    const auto QOS_RKL10V = rclcpp::QoS(rclcpp::KeepLast(10)).reliable().durability_volatile();
    
    this->node_ptr_ = rclcpp::Node::make_shared("set_position_node");
    position_sub_ = node_ptr_->create_subscription<ttr_msgs::msg::Motion>("paddle_position", QOS_RKL10V, std::bind(&SetPositionPlugin::OnPositionCommand, this, std::placeholders::_1));

    this->executor_ = rclcpp::executors::SingleThreadedExecutor::make_shared();
    this->executor_->add_node(this->node_ptr_);
}

void SetPositionPlugin::OnUpdate()
{
    this->executor_->spin_once(std::chrono::nanoseconds(1));
    model_->SetWorldPose(goal_position_);
}

void SetPositionPlugin::OnPositionCommand(const ttr_msgs::msg::Motion::SharedPtr msg)
{
    ignition::math::Vector3 position(msg->position.x, msg->position.y, msg->position.z);
    ignition::math::Quaternion quaternion(msg->orientation.w, msg->orientation.x, msg->orientation.y, msg->orientation.z);
    
    goal_position_.Set(position, quaternion);
}
