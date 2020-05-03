#!/usr/bin/python3

import serial
import glob
import threading
import os
import time
import datetime

def selectFromList(options, message = "Please select from below:"):
  valid = False
  while True:
    print(message)
    print("-----------------------------")
    for num, opt in enumerate(options):
      print("{}\t{}".format(num,opt))
    print()
    selected = input().split(" ")
    for item in selected:
      try:
        if (int(item) >= len(options) or int(item) < 0):
          raise TypeError
        return [int(x) for x in sorted(list(set(selected)))]
      except (TypeError, ValueError):
        print("invalid selection!")
        print()

def run(port, start):
  print("")




if __name__ == "__main__":
  #ports = glob.glob('/dev/tty[A-Za-z][A-Za-z]*')
  #selected = selectFromList(ports, "Please select a port:")
  start = str(round(time.time()))
  os.mkdir(os.path.join("./out/",start))
  
     
