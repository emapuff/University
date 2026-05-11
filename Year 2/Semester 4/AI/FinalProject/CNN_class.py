import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import itertools
from sklearn.metrics import confusion_matrix
from sklearn.preprocessing import LabelEncoder
from tensorflow.keras.utils import to_categorical
from tensorflow.keras import layers, models
from tensorflow.keras.callbacks import EarlyStopping

class SkinCNN:
    def __init__(self, num_classes=4):
        self.num_classes = num_classes
        self.label_encoder = LabelEncoder()
        self.model = None
        self.history = None

    def load_data(self, file_path):
        df = pd.read_csv(file_path)
        data = {}
        for label in df['label'].unique():
            data[label] = df[df['label'] == label]['file_path'].tolist()
        return data

    def prepare_data(self, data_dict):
        inputs = []
        outputs = []
        for label, paths in data_dict.items():
            for path in paths:
                inputs.append(np.load(path))
                outputs.append(label)
        inputs = np.array(inputs) / 255.0
        outputs = self.label_encoder.transform(outputs)
        outputs = to_categorical(outputs, num_classes=self.num_classes)
        return inputs, outputs

    def build_model(self, input_shape):
        self.model = models.Sequential([
            layers.Conv2D(32, (3, 3), activation='relu', input_shape=input_shape),
            layers.Conv2D(64, (3, 3), activation='relu'),
            layers.MaxPooling2D((2, 2)),
            layers.Conv2D(128, (3, 3), activation='relu'),
            layers.MaxPooling2D((2, 2)),
            layers.Flatten(),
            layers.Dense(64, activation='relu'),
            layers.Dense(self.num_classes, activation='softmax')
        ])
        self.model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

    def train(self, train_data, val_data, epochs=100, batch_size=32):
        X_train, y_train = train_data
        X_val, y_val = val_data
        self.build_model(X_train.shape[1:])
        early_stop = EarlyStopping(patience=10, restore_best_weights=True)
        print(f"[INFO] Starting training for {epochs} epochs...")
        self.history = self.model.fit(
            X_train, y_train,
            epochs=epochs,
            batch_size=batch_size,
            validation_data=(X_val, y_val),
            callbacks=[early_stop]
        )

    def evaluate(self, test_data):
        X_test, y_test = test_data
        loss, acc = self.model.evaluate(X_test, y_test, verbose=2)
        print("Test accuracy:", acc)
        return loss, acc

    def predict(self, X):
        pred_probs = self.model.predict(X)
        return np.argmax(pred_probs, axis=1)

    def plot_confusion_matrix(self, y_true, y_pred, title="Confusion Matrix"):
        cm = confusion_matrix(y_true, y_pred)
        classes = self.label_encoder.classes_

        plt.figure()
        plt.imshow(cm, interpolation='nearest', cmap='Blues')
        plt.title(title)
        plt.colorbar()
        tick_marks = np.arange(len(classes))
        plt.xticks(tick_marks, classes, rotation=45)
        plt.yticks(tick_marks, classes)

        thresh = cm.max() / 2.
        for i, j in itertools.product(range(cm.shape[0]), range(cm.shape[1])):
            plt.text(j, i, format(cm[i, j], 'd'),
                     horizontalalignment="center",
                     color="white" if cm[i, j] > thresh else "black")

        plt.ylabel('True label')
        plt.xlabel('Predicted label')
        plt.tight_layout()
        plt.show()

    def fit_label_encoder(self, datasets):
        all_labels = []
        for data_dict in datasets:
            for label in data_dict.keys():
                all_labels.append(label)
        self.label_encoder.fit(all_labels)