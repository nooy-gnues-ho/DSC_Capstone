import serial
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
PORT = 'COM7';
BaudRate = 9600;

cred = credentials.Certificate(r"C:\Users\oha84\capstone/serviceAccountKey.json");
firebase_admin.initialize_app(cred,{
    'databaseURL' : 'https://capstone-b431a-default-rtdb.firebaseio.com/'
});



ser = serial.Serial(PORT,BaudRate);

while True:
    gps = ser.readline().decode();
    print("gps : " + gps);
    dir = db.reference('gps정보');
    dir.update({'gps정보':gps});
    

