# Gazebo-Plugins-ROS2

This work presents custom plugins of Gazebo for ROS2.

### build

```
git clone https://github.com/SeonilChoi/Gazebo-Plugins-ROS2.git
mkdir plugin_path/build plugins
cd plugin_path/build
cmake ..
make
```
### ~/.bashrc
```
export GAZEBO_PLUGIN_PATH=$GAZEBO_PLUGIN_PATH:~/plugins
```

---

## set_joint_position_plugin
```
<plugin name="set_joint_position_plugin" filename="libset_joint_position_plugin.so">
  <joint_name1>joint1</joint_name1>
  <joint_name2>joint2</joint_name2>
  ...
  <namespace>namespace</namespace>
</plugin>
```

## set_joint_velocity_plugin
```
<plugin name="set_joint_velocity_plugin" filename="libset_joint_velocity_plugin.so">
  <joint_name1>joint1</joint_name1>
  <joint_name2>joint2</joint_name2>
  ...
  <namespace>namespace</namespace>
</plugin>
```

## custom_joint_state_publisher_plugin
```
<plugin name="custom_joint_state_publisher_plugin" filename="libcustom_joint_state_publisher_plugin.so">
    <joint_name1>joint1</joint_name1>
    <joint_name2>joint2</joint_name2>
    ...
    <namespace>namespace</namespace>
</plugin>
```
