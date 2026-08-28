from ultralytics import YOLO

if __name__ == '__main__':
    model = YOLO("yolov8s.pt")
    model.train(
        data="datasets/pcd-small/data.yaml",
        epochs=50,
        imgsz=640,
        batch=16,
        workers=8,
        device=0,
        patience=20,
        project="runs",
        name="smoketest",
    )