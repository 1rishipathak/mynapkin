# prints mean-avg-precision (map) values
from ultralytics import YOLO

if __name__ == '__main__':
    model = YOLO("runs/detect/runs/smoketest-2/weights/best.pt")
    m = model.val(data="datasets/pcd-small/data.yaml", split="test",
                  project="runs", name="test-eval")
    print("mAP50   :", m.box.map50)
    print("mAP50-95:", m.box.map)
    for i, name in model.names.items():
        print(f"  {name}: {m.box.maps[i]:.4f}")
