from CNN_class import SkinCNN
from tensorflow.keras.utils import to_categorical
from sklearn.preprocessing import LabelEncoder
import numpy as np

def train_and_save_model(model_path):
    model = SkinCNN(num_classes=4)
    train_dict = model.load_data("train.csv")
    val_dict = model.load_data("val.csv")
    test_dict = model.load_data("test.csv")
    model.fit_label_encoder([train_dict, val_dict, test_dict])
    trainX, trainY = model.prepare_data(train_dict)
    valX, valY = model.prepare_data(val_dict)
    testX, testY = model.prepare_data(test_dict)
    model.train((trainX, trainY), (valX, valY))
    model.evaluate((testX, testY))
    model.model.save(model_path)

if __name__ == "__main__":
    train_and_save_model("model.h5")
