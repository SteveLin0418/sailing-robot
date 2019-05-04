#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <pixhawk/imu_gps.h>
#include <std_msgs/Float32.h>
#include <sailing_robot/Velocity.h>
#include <cmath>
#include <sensor_msgs/NavSatFix.h>

int num;
int i;
float latitude;
float lontitude;
float altitude;
float vx;
float vy;
float vz;
float angle;
pixhawk::imu_gps imugps;
std_msgs::Float32 angle_float32;
sailing_robot::Velocity velocity;
sensor_msgs::NavSatFix position;
float time_last=0;
float time_now=0;
float time_inv=0;

serial::Serial ser;
int main (int argc, char** argv){
 ros::init(argc, argv, "camera");
    
  try
    {
        ser.setPort("/dev/ttyUSB0");
        ser.setBaudrate(57600);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
	serial::bytesize_t bytes = serial::eightbits;
	serial::parity_t parity=serial::parity_none;
	serial::stopbits_t stopbits=serial::stopbits_one;
        ser.setBytesize(bytes);
        ser.setParity(parity);
        ser.setStopbits(stopbits);
        ser.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open port ");
        return -1;
    }

    if(ser.isOpen()){
        ROS_INFO_STREAM("Serial Port initialized");
    }else{
        return -1;
    }

    ros::Rate loop_rate(10);
    while(ros::ok()){

        ros::spinOnce();

        if(ser.available()){
            ROS_INFO_STREAM("Reading from serial port");
            std_msgs::String result;
            num=ser.available();
            result.data = ser.read(num);
	    ser.flushInput();
        vx=(unsigned char)(result.data[10]);
        ROS_INFO_STREAM("vx: "<<vx);
		        
}
        loop_rate.sleep();
    }}