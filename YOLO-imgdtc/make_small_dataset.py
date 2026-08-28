import random, shutil
from pathlib import Path

SRC = Path("datasets/pcd")
DST = Path("datasets/pcd-small")
TARGETS = {"train": 3000, "valid": 800, "test": 909}
random.seed(42)

for split, target in TARGETS.items():
    src_img, src_lbl = SRC / split / "images", SRC / split / "labels"
    dst_img, dst_lbl = DST / split / "images", DST / split / "labels"
    dst_img.mkdir(parents=True, exist_ok=True)
    dst_lbl.mkdir(parents=True, exist_ok=True)

    files = sorted(src_img.glob("*.jpg"))
    random.shuffle(files)

    kept = 0
    for f in files:
        if kept >= target:
            break
        lbl = src_lbl / (f.stem + ".txt")
        if not lbl.exists():
            continue
        shutil.copy2(f, dst_img / f.name)
        shutil.copy2(lbl, dst_lbl / lbl.name)
        kept += 1

    print(f"{split}: kept {kept} of {len(files)}")

shutil.copy2(SRC / "data.yaml", DST / "data.yaml")
print("done")