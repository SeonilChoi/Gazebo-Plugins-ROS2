# Gazebo-Plugins-ROS2

This work presents custom plugins of Gazebo for ROS2.

### build

```
cd plugin_path/build
cmake ..
make
```
### ~/.bashrc
```
export GAZEBO_PLUGIN_PATH=$GAZEBO_PLUGIN_PATH:~/gazebo_plugins/plugins
```

## set_joint_velocity_plugin
```
<plugin name="set_joint_velocity_plugin" filename="libset_joint_velocity_plugin.so">
  <joint_name>joint_name</joint_name>
</plugin>
```

## joint_state_publisher_plugin

## set_joint_position_plugin
