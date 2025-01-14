/*
 *	Copyright (C) 2018-2020 Robosense Authors
 *  License: Modified BSD Software License Agreement
 *
 *  $Id$
 */

/** \file
 *
 *  ROS driver node for the Robosense 3D LIDARs.
 */
#include <ros/ros.h>
#include "rsdriver.h"
#include "std_msgs/String.h"

using namespace rslidar_driver;
volatile sig_atomic_t flag = 1;

static void my_handler(int sig)
{
  flag = 0;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "rsdriver",ros::init_options::AnonymousName);
  ros::NodeHandle node;
  ros::NodeHandle private_nh("~");

  signal(SIGINT, my_handler);

  // start the driver
  rslidar_driver::rslidarDriver dvr(node, private_nh);
  // loop until shut down or end of file
  while (ros::ok() && dvr.poll())
  {
    ros::spinOnce();
  }

  return 0;
}
