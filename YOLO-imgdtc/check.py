from ultralytics import YOLO
import yaml

if __name__ == '__main__':
    with open("datasets/pcd-small/data.yaml") as f:
        print(yaml.safe_load(f))

    model = YOLO("yolov8s.pt")
    model.val(data="datasets/pcd-small/data.yaml", split="val",
              project="runs", name="labelcheck")