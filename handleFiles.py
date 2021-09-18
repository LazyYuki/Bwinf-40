import json as js

def readtxtLines(file):
    with open(file, 'r') as file:
        txtlines = file.readlines()
        file.close
    return txtlines
    


#------------------------------------------------------------------------------
def writeJson(file, article):
    with open(file, 'w') as file:
        js.dump(article, file)
        file.close

def readJson(file):
    with open(file, 'r') as file:
        obj = js.loads(file.read())
        file.close
    return obj

