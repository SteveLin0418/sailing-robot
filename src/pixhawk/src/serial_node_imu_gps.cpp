#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <pixhawk/imu_gps.h>
#include <std_msgs/Float32.h>
#include <sailing_robot/Velocity.h>
#include <cmath>
#include <sensor_msgs/NavSatFix.h>

serial::Serial ser;
serial::Serial ser_gps;
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

void write_callback(const std_msgs::String::ConstPtr& msg){
    ROS_INFO_STREAM("Writing to serial port" << msg->data);
    ser.write(msg->data);
}

int main (int argc, char** argv){
    ros::init(argc, argv, "imu_gps_serial_node");
    ros::NodeHandle nh;

    ros::Subscriber write_sub = nh.subscribe("write", 1000, write_callback);
    ros::Publisher read_pub = nh.advertise<pixhawk::imu_gps>("imu_gps", 1000);
    ros::Publisher heading_pub = nh.advertise<std_msgs::Float32>("heading",10);
    ros::Publisher velocity_pub = nh.advertise<sailing_robot::Velocity>("gps_velocity",10);
    ros::Publisher pos_pub = nh.advertise<sensor_msgs::NavSatFix>("position",10);
    try
    {
        ser.setPort("/dev/ttyUSB0");
        ser.setBaudrate(9600);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
	serial::bytesize_t bytes = serial::eightbits;
	serial::parity_t parity=serial::parity_none;
	serial::stopbits_t stopbits=serial::stopbits_one;
        ser.setBytesize(bytes);
        ser.setParity(parity);
        ser.setStopbits(stopbits);
        ser.open();

        ser_gps.setPort("/dev/ttyACM0");
        ser_gps.setBaudrate(57600);
        ser_gps.setTimeout(to);
        ser_gps.setBytesize(bytes);
        ser_gps.setParity(parity);
        ser_gps.setStopbits(stopbits);
        ser_gps.open();
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

        int num = ser.available();
        int num_gps = ser_gps.available();

            ROS_INFO_STREAM("Reading from serial port, num: " << num);

            ROS_INFO_STREAM("Reading from serial port, num_gps: " << num_gps);


        if (num) {
            ROS_INFO_STREAM("Reading from serial port, num: " << num);
            std_msgs::String result;
            result.data = ser.read(num);
            ser.flushInput();
            for (i = 0; i < num; i++) {
                //ROS_INFO_STREAM("raw_data: " <<(unsigned int)(unsigned char)(result.data[i]));
                //ROS_INFO_STREAM("index: " <<i);
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                          << (unsigned int) (unsigned char) (result.data[i]) << ' ';
            }
            std::cout << std::endl;
            int cur = 0;
			while (cur < num && (unsigned int) (unsigned char) result.data[cur] != 0x55) cur++;
            while (cur + 11 < num) {
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                          << (unsigned int) (unsigned char) (result.data[cur]) << ' ';
                if ((unsigned int) (unsigned char) result.data[cur] == 0x55) {
                        switch ((unsigned int) (unsigned char) result.data[cur + 1]) {
                            case 0x53:
                                angle = ((unsigned int) (unsigned char) result.data[cur + 7] << 8 |
                                         (unsigned int) (unsigned char) result.data[cur + 6]) / 32768.0 * 180;
                                angle = 360-angle;
                        }
                        cur += 11;
				}
				else {
					while (cur < num && (unsigned int) (unsigned char) result.data[cur] != 0x55) cur++;
					continue;
				}
                    vx = vy = vz = 50;

                    ROS_INFO_STREAM("vx: " << vx);
                    ROS_INFO_STREAM("vy: " << vy);
                    ROS_INFO_STREAM("vz: " << vz);
                    ROS_INFO_STREAM("angle: " << angle);

                    imugps.latitude = latitude;
                    imugps.lontitude = lontitude;
                    imugps.vx = vx;
                    imugps.vy = vy;
                    imugps.vz = vz;
                    imugps.angle = angle;
                    read_pub.publish(imugps);

                    angle_float32.data = angle;
                    heading_pub.publish(angle_float32);

                    velocity.speed = sqrt(vx * vx + vy * vy);
                    velocity.heading = atan2((double) vx, (double) vy) * 180 / 3.14f;
                    velocity_pub.publish(velocity);

                    position.latitude = (double) latitude;
                    position.longitude = (double) lontitude;
                    position.altitude = (double) altitude;
                    pos_pub.publish(position);
            }
        }

        if (num_gps) {
            ROS_INFO_STREAM("Reading from serial port, num_gps: " << num_gps);
            std_msgs::String result;
            result.data = ser_gps.read(num_gps);
            ser_gps.flushInput();
            for (i = 0; i < num_gps; i++) {
                std::cout << std::hex << std::setw(2) << std::setfill('0')
                          << (unsigned int) (unsigned char) (result.data[i]) << ' ';
            }
            std::cout << std::endl;

			int res_offset = 0;

            if (((unsigned int) (unsigned char) (result.data[22]) == 33) &&
                ((unsigned int) (unsigned char) (result.data[18]) == 28)) {


                if (result.data[30 + res_offset] < 127) {
                    latitude = ((unsigned char) (result.data[27 + res_offset]) +
                                256.0 * (unsigned char) (result.data[28 + res_offset]) +
                                256.0 * 256.0 * (unsigned char) (result.data[29 + res_offset]) +
                                256.0 * 256.0 * 256.0 *
                                (unsigned char) (result.data[30 + res_offset])) / 10000000.0;
                } else {
                    latitude = ((unsigned char) (result.data[27 + res_offset]) + 256.0 * (unsigned char) (result.data[28 + res_offset]) +
                                256.0 * 256.0 * (unsigned char) (result.data[29 + res_offset]) +
                                256.0 * 256.0 * 256.0 * (unsigned char) (result.data[30 + res_offset]) -
                                256.0 * 256.0 * 256.0 * 256.0) / 10000000.0;
                }

                if (result.data[34 + res_offset] < 127) {
                    lontitude = ((unsigned char) (result.data[31 + res_offset]) +
                                 256.0 * (unsigned char) (result.data[32 + res_offset]) +
                                 256.0 * 256.0 * (unsigned char) (result.data[33 + res_offset]) +
                                 256.0 * 256.0 * 256.0 *
                                 (unsigned char) (result.data[34 + res_offset])) / 10000000.0;
                } else {
                    lontitude = ((unsigned char) (result.data[31 + res_offset]) + 256.0 * (unsigned char) (result.data[32 + res_offset]) +
                                 256.0 * 256.0 * (unsigned char) (result.data[33 + res_offset]) +
                                 256.0 * 256.0 * 256.0 * (unsigned char) (result.data[34 + res_offset]) -
                                 256.0 * 256.0 * 256.0 * 256.0) / 10000000.0;
                }

                if (result.data[38 + res_offset] < 127) {
                    altitude = ((unsigned char) (result.data[35 + res_offset]) +
                                256.0 * (unsigned char) (result.data[36 + res_offset]) +
                                256.0 * 256.0 * (unsigned char) (result.data[37 + res_offset]) +
                                256.0 * 256.0 * 256.0 *
                                (unsigned char) (result.data[38 + res_offset])) / 1000.0;
                } else {
                    altitude = ((unsigned char) (result.data[35 + res_offset]) + 256.0 * (unsigned char) (result.data[36 + res_offset]) +
                                256.0 * 256.0 * (unsigned char) (result.data[37 + res_offset]) +
                                256.0 * 256.0 * 256.0 * (unsigned char) (result.data[38 + res_offset]) -
                                256.0 * 256.0 * 256.0 * 256.0) / 1000.0;
                }

                ROS_INFO_STREAM("latitude: " << latitude);
                ROS_INFO_STREAM("lontitude: " << lontitude);
                ROS_INFO_STREAM("altitude: " << altitude);

                imugps.latitude = latitude;
                imugps.lontitude = lontitude;
                imugps.vx = vx;
                imugps.vy = vy;
                imugps.vz = vz;
                imugps.angle = angle;
                read_pub.publish(imugps);

                angle_float32.data = angle;
                heading_pub.publish(angle_float32);

                velocity.speed = sqrt(vx * vx + vy * vy);
                velocity.heading = atan2((double) vx, (double) vy) * 180 / 3.14f;
                velocity_pub.publish(velocity);

                position.latitude = (double) latitude;
                position.longitude = (double) lontitude;
                position.altitude = (double) altitude;

                pos_pub.publish(position);
            }
        }
        loop_rate.sleep();
    }
}

