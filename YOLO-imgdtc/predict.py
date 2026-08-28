from ultralytics import YOLO

if __name__ == '__main__':
    model = YOLO("runs/detect/runs/smoketest-2/weights/best.pt")
    model.predict(source="datasets/pcd-small/test/images",
                  save=True, conf=0.5, project="runs", name="preds")