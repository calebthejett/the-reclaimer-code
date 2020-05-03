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

class work:
  def __init__(self, port, start):
    self.running = True
    self.port = port
    self.start = start

  def run(self):
    print("Opening {}".format(self.port))
    data = ""
    with serial.Serial(self.port, baudrate=115200) as ser:
      while self.running:
        val = ser.read()
        try:
          data += val.decode()
        except UnicodeDecodeError:
          print("{}: ignoring {}".format(self.port,str(val)))
          pass

    print("dumping {}".format(self.port))
    dest = self.port.replace("/","_")+".csv"
    with open(os.path.join("./out/",self.start,dest),'w') as f:
      f.write(data)
    print("Done!")

  def stop(self):
    self.running = False





if __name__ == "__main__":
  ports = glob.glob('/dev/tty[A-Za-z][A-Za-z]*')
  selected = selectFromList(ports, "Please select a port:")

  start = str(round(time.time()))
  try:
    os.mkdir("./out")
  except FileExistsError:
    pass
  os.mkdir(os.path.join("./out/",start))

  workers = []
  for sel in selected:
    newWork = work(ports[sel],start)
    newThread = threading.Thread(target = newWork.run)
    newThread.daemon = True
    newThread.start()
    workers.append([newWork,newThread])
  
  try:
    while True:
      time.sleep(1)
  except KeyboardInterrupt:
    print("Shutting down")
    for worker in workers:
      worker[0].stop()
      worker[1].join()


  
     
