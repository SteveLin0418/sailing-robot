// Generated by gencpp from file sailing_robot/Velocity.msg
// DO NOT EDIT!


#ifndef SAILING_ROBOT_MESSAGE_VELOCITY_H
#define SAILING_ROBOT_MESSAGE_VELOCITY_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace sailing_robot
{
template <class ContainerAllocator>
struct Velocity_
{
  typedef Velocity_<ContainerAllocator> Type;

  Velocity_()
    : speed(0.0)
    , heading(0.0)  {
    }
  Velocity_(const ContainerAllocator& _alloc)
    : speed(0.0)
    , heading(0.0)  {
  (void)_alloc;
    }



   typedef float _speed_type;
  _speed_type speed;

   typedef float _heading_type;
  _heading_type heading;





  typedef boost::shared_ptr< ::sailing_robot::Velocity_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::sailing_robot::Velocity_<ContainerAllocator> const> ConstPtr;

}; // struct Velocity_

typedef ::sailing_robot::Velocity_<std::allocator<void> > Velocity;

typedef boost::shared_ptr< ::sailing_robot::Velocity > VelocityPtr;
typedef boost::shared_ptr< ::sailing_robot::Velocity const> VelocityConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::sailing_robot::Velocity_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::sailing_robot::Velocity_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace sailing_robot

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'sailing_robot': ['/home/sailing/catkin_wws/src/sailing-robot/src/sailing_robot/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::sailing_robot::Velocity_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::sailing_robot::Velocity_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sailing_robot::Velocity_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::sailing_robot::Velocity_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sailing_robot::Velocity_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::sailing_robot::Velocity_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::sailing_robot::Velocity_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d0661ebd150249ab8f58a7b5063ee3b9";
  }

  static const char* value(const ::sailing_robot::Velocity_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd0661ebd150249abULL;
  static const uint64_t static_value2 = 0x8f58a7b5063ee3b9ULL;
};

template<class ContainerAllocator>
struct DataType< ::sailing_robot::Velocity_<ContainerAllocator> >
{
  static const char* value()
  {
    return "sailing_robot/Velocity";
  }

  static const char* value(const ::sailing_robot::Velocity_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::sailing_robot::Velocity_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# message for publishing GPS velocity\n\
float32 speed # [m/s]\n\
float32 heading # [degrees]\n\
\n\
";
  }

  static const char* value(const ::sailing_robot::Velocity_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::sailing_robot::Velocity_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.speed);
      stream.next(m.heading);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Velocity_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sailing_robot::Velocity_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::sailing_robot::Velocity_<ContainerAllocator>& v)
  {
    s << indent << "speed: ";
    Printer<float>::stream(s, indent + "  ", v.speed);
    s << indent << "heading: ";
    Printer<float>::stream(s, indent + "  ", v.heading);
  }
};

} // namespace message_operations
} // namespace ros

#endif // SAILING_ROBOT_MESSAGE_VELOCITY_H
