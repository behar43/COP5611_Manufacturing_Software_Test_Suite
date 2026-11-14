#!/usr/bin/python
import requests
import subprocess
import sys
import os.path
import json
import signal
import sys
from werkzeug.utils import secure_filename
from flask import Flask, jsonify, Response, request, abort
from flask import send_from_directory
# add current directory to path for all future imports

sys.path.append(os.path.realpath("."))

app = Flask(__name__, static_url_path='', static_folder='', template_folder='')


@app.route('/', methods=['GET'])
@app.route('/index.html', methods=['GET'])
def helpfunction():
    return app.send_static_file('index.html')

@app.route('/hello.htm', methods=['GET'])
def hellohelp():
    return app.send_static_file('hello.htm')

@app.route("/<path:path>")
def static_proxy(path):
    return app.send_static_file(path)

@app.route("/atptest.htm", methods=['GET'])
def executeatp():
    return app.send_static_file('atptest.htm')

@app.route("/esstest.htm", methods=['GET'])
def executeess():
    return app.send_static_file('esstest.htm')

@app.route('/version', methods=['GET'])
def versionfunction():
    return jsonify({
        "ATP Software Version": {
          "Version": "00.00.00",
          "Revision": 00,
          "Sub Revision": "00"
        }
    })

@app.route('/hello', methods=['GET'])
def hellofunction():
    if 'name' in request.args:
        hello = request.args['name']
    else:
        hello = u'HELLO'

    return jsonify({'hello': hello})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8484, debug=False, threaded=True) #debug=True or False #for debug trace use_reloader=False to disable reloader

