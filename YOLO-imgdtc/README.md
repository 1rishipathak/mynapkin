This project uses yolov8 (yolov8n) to identify dogs, cats, persons in an image.
The main dataset contains ~9k images (labelled) downloaded from roboflow, with already seperated into train,test,split sets.
It also contains a 'make_small_dataset.py' python script to reduce the size of the dataset (to make training faster and reduce compute required).
The order to run the files are:
1. download_data.py
2. make_small_dataset.py
3. check.py (to check if images are being labelled correctly (does not guarantee correct class assignment)
4. train.py
5. predict.py
6. evaluate.py

The result-5-worst and result-5-best contain some of the best and worst images
The accuracy figures from evaluate.py are saved under the 'test-eval' folder.
