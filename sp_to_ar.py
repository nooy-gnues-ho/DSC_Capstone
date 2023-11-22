import serial
import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
from pyDFPlayer import DFPlayer
from time import sleep
df=DFPlayer(uart_id=1,tx_pin_id=4,rx_pin_id=5)
PORT = 'COM9';
BaudRate = 9600;

cred = credentials.Certificate(r"C:\Users\oha84\capstone/serviceAccountKey.json");
firebase_admin.initialize_app(cred,{
    'databaseURL' : 'https://capstone-b431a-default-rtdb.firebaseio.com/'
});

#ser = serial.Serial(PORT,BaudRate);

while True:
    music.volume(20)
    ref = db.reference('/state/LED')
    data = ref.get()
    if(data == 'red'):
        df.play(1)
    elif(data == 'green'):
        df.play(2)
