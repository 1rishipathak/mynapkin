from roboflow import Roboflow 
rf = Roboflow(api_key="ku1TCNRQy6btVAhVRcTx")
project = rf.workspace("smartcarparkingsystem").project("person-cat-dog")
version = project.version(1)
dataset = version.download("yolov8")
