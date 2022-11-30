# The C2 Server 

import os

import psycopg2
from flask import Flask, jsonify, request
from flask_cors import CORS
from flask_jwt_extended import create_access_token,get_jwt, get_jwt_identity, unset_jwt_cookies, jwt_required, JWTManager

app = Flask(__name__)
cors = CORS(app, resources={r"/login": {"origins": "http://localhost:3000"}})

host = os.environ['host']
password = os.environ['password']
username = os.environ['username']
port = os.environ['thePort']
database = os.environ['database']


# Code taken from https://dev.to/nagatodev/how-to-add-login-authentication-to-a-flask-and-react-application-23i7
app.config["JWT_SECRET_KEY"] = "change-me"
jwt = JWTManager(app) 

@app.route('/login', methods=["POST"])
def create_token():
    print(request.json)
    username = request.json.get("username", None)
    password = request.json.get("password", None)
    if username != "test" or password != "test": #hardcoded login, compare to database
        return {"msg": "Wrong email or password"}, 401

    access_token = create_access_token(identity=username)
    response = {"access_token":access_token}
    response.headers.add('Access-Control-Allow-Origin', '*')
    return response 

def load():
    # Connect to C2
    try:
        print("Connecting")
        conn = psycopg2.connect(dbname=database, user=username, password=password, host=host, port=port, connect_timeout=20)
        print("Success? Should be 0 -> ", conn.closed)
        cursor = conn.cursor()
    except:
        print("failed to connect")

    print(f"Connection closed? {conn.closed}")
    return cursor

# For when you want to any query, used to avoid connections timing out 
def executeQuery(query):
    cursor = load()
    cursor.execute(query)
    returnThis = cursor.fetchall()

    return returnThis 

@app.route("/hello", methods=["GET"])
def sure():
    try:
        cursor = load()
    except:
        print("failure")
    print(host, password, username, port, database)
    return "<p>hey!!</p>"

@app.route("/whoami", methods=["GET"])
def handle_whoami():
    #TO IMPLEMENT 
    pass 

@app.route("/test", methods=["GET"])
def handle_test():
    stuff = executeQuery("SELECT * from test")
    return ("<p>%s</p>" % stuff)

@app.route("/")
def hello():
    return "<p>Hello, World!</p>"

@app.route("/execute", methods=["POST"])
def handle_execute():
    pass 

@app.route("/getCommands", methods=["GET"])
def get_commands():
    pass