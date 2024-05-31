from flask import Flask,render_template,request

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')
app.route('/',methods=['POST']) 
def getvalue():
    msg= request.from('name')#hoot el name mtehek sfar
    return render_template('pass.html',msg=msg)


if __name__ == '__main__':
    app.run(debug=True)