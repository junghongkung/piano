# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from flask import Flask, render_template, send_from_directory, request
import os 

from flask_socketio import SocketIO
import socketio


sio = socketio.Client()


app = Flask(__name__)
socket_io = SocketIO(app)

@app.route("/", methods=['GET', 'POST'])
def home():
    return render_template('main1.html',subject="Teachable Machine Audio Model")

@socket_io.on('connect')
def connected():
    print("connected!\n\n")
    socket_io.send('python')
    

    
@socket_io.on('message')
def handleMessage(msg, methods=['GET', 'POST']):
    if request.method=='GET':
        max_label_name, value = msg.split()
        print("max label name : " + max_label_name + "\n")
        print("value : " + value + "\n")
        
#favicon error를 해결하기 s위한 코드
@app.route('/favicon.ico') 
def favicon(): 
    return send_from_directory(os.path.join(app.root_path, 'static'), 'favicon.ico', mimetype='image/vnd.microsoft.icon')
    

if __name__ == "__main__":
    app.run()
    socket_io.run(app)
