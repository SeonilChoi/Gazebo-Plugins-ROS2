# Gazebo-Plugins-ROS2-Foxy

This work presents custom plugins of Gazebo for ROS2 Foxy.

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

## joint_velocity_setter_plugin
```
<plugin name="joint_velocity_controller_plugin" filename="libjoint_velocity_controller_plugin.so">
  <joint_name>joint_name</joint_name>
</plugin>
```

## joint_position_publisher_plugin

## joint_state_initializer_plugin
