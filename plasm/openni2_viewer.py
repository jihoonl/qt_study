#!/usr/bin/env python

"""
This sample shows how to grab openni2
"""

import sys
import ecto, ecto_ros, ecto_pcl_ros, ecto_pcl
import ecto_ros.ecto_sensor_msgs as ecto_sensor_msgs
from ecto.opts import scheduler_options, run_plasm
from ecto_pcl import *
import rgbd_viewer

def generate_graph():
    grabber = ecto_pcl.OpenNI2Grabber()

    grab = ecto_pcl.OpenNI2Grabber()
    viewer = rgbd_viewer.CloudViewer("Hello world")

    graph = [grab[:] >> viewer[:]]

    return graph

if __name__ == "__main__":
    plasm = ecto.Plasm()
    graph = generate_graph()
    plasm.connect(graph)
    ecto.view_plasm(plasm)
    ecto.opts.doit(plasm, description='Openni2 viewer')
