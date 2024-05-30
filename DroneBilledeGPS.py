# Lavet af Mathias Hoppe, taget inspiration fra Tomasz Week 13 lab 5
import serial
import time 
import datetime
import requests
from picamera2 import Picamera2, Preview
from libcamera import controls 

ser = serial.Serial (port="/dev/ttyS0", baudrate=9600)    #Open port ttyS0 with baud rate 9600
time.sleep(0.1) #wait for serial to open

# Picamera2 - 
picam2 = Picamera2()
#camera_config = picam2.create_preview_configuration()
#picam2.configure(camera_config)
#picam2.start_preview(Preview.QTGL)
picam2.set_controls({"AfMode": controls.AfModeEnum.Continuous}) 
#picam2.set_controls({"AfMode": controls.AfModeEnum.Auto})
picam2.start()
time.sleep(2)

while True:
    print("---------------------")
    
    # Serial - read the bytes from Arduino
    received_data = ser.read_until().decode('ascii')  # Read until an expected sequence is found ('\n' by default)
    print("GPS: ", received_data)
    GPS_dateTime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S") 
    print("GPS datetime: ", GPS_dateTime)
   
    dateFilename = datetime.datetime.now().strftime("%Y-%m-%d %H.%M.%S") 
    photo_dateTime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    strFilename = "images/"+dateFilename+".jpg"
    picam2.capture_file(strFilename) 
    
    # send data to VM
    print("**Send data to VM")
    urlVM = 'http://152.115.77.165:50308/dn-insert.php' # Burde være db-insert.php, for database, men tykke fingre.
    dataPost = {'password': '1234', 'GPS_value':received_data.rstrip("\n"), 'GPS_dateTime':GPS_dateTime, 'photo_dateTime':photo_dateTime}
    files = {'file-image': open(strFilename, 'rb')}
    requestsResult = requests.post(urlVM, files=files, data=dataPost)
   
    print("***********************")
    print("**Response from VM: ***")
    print(requestsResult.text)
    print("**********************")
    print("---------------------")
    
    time.sleep(30) # Forces program to rest for 30 sekunds, so we don't get spammed by Photos and GPS data
    
