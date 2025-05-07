from azure.cognitiveservices.vision.computervision import ComputerVisionClient
from azure.cognitiveservices.vision.computervision.models import OperationStatusCodes
from azure.cognitiveservices.vision.computervision.models import VisualFeatureTypes
from msrest.authentication import CognitiveServicesCredentials
from array import array
import os
from PIL import Image
import sys
import time
import Levenshtein
from pytesseract import *
import argparse
import cv2
from pytesseract import Output
subscription_key = os.environ["VISION_KEY"]
endpoint = os.environ["VISION_ENDPOINT"]
computervision_client = ComputerVisionClient(endpoint, CognitiveServicesCredentials(subscription_key))
import re
from scipy.spatial.distance import hamming


def text_extraction(file):
    img = open(file, "rb")
    read_response = computervision_client.read_in_stream(
        image=img,
        mode="Printed",
        raw=True
    )

    operation_id = read_response.headers['Operation-Location'].split('/')[-1]
    while True:
        read_result = computervision_client.get_read_result(operation_id)
        if read_result.status not in ['notStarted', 'running']:
            break
        time.sleep(1)

    result = []
    if read_result.status == OperationStatusCodes.succeeded:
        for text_result in read_result.analyze_result.read_results:
            for line in text_result.lines:
                result.append(line.text)

    clean_result = []
    for sentence in result:
        words = re.findall(r'\b\w+\b', sentence)
        words = [word.lower() for word in words]
        clean_result.extend(words)

    return clean_result


def hamming_distance(expected, resulted):
    if len(expected) != len(resulted):
        return False
    return hamming(expected, resulted) * len(expected)


def levenstein_distance(expected, resulted):
    return Levenshtein.distance(expected, resulted)


def jaccard_similarity(word1, word2):
    set1 = set(word1)
    set2 = set(word2)
    return len(set1 & set2) / len(set1 | set2)


def text_extraction_with_bboxes(file, min_confidence=50, resize_factor=0.5):
    img = open(file, "rb")
    read_response = computervision_client.read_in_stream(image=img, mode="Printed", raw=True)
    operation_id = read_response.headers['Operation-Location'].split('/')[-1]
    while True:
        read_result = computervision_client.get_read_result(operation_id)
        if read_result.status not in ['notStarted', 'running']:
            break
        time.sleep(1)

    result = []

    if read_result.status == OperationStatusCodes.succeeded:
        for text_result in read_result.analyze_result.read_results:
            for line in text_result.lines:
                result.append(line)

    image = cv2.imread(file)

    for line in result:
        text = line.text

        x1, y1, x2, y2, x3, y3, x4, y4 = line.bounding_box
        top_left = (int(x1), int(y1))
        bottom_right = (int(x3), int(y3))

        cv2.rectangle(image, top_left, bottom_right, (0, 0, 255), 2)
        cv2.putText(image, text, (int(x1), int(y1) - 10), cv2.FONT_HERSHEY_SIMPLEX, 1.2, (0, 255, 255), 3)
        print(f"Text: {text}")
        print("-" * 50)

    cv2.imshow("OCR Result", image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    new_width = int(image.shape[1] * resize_factor)
    new_height = int(image.shape[0] * resize_factor)
    resized_image = cv2.resize(image, (new_width, new_height))

    # Display the final resized image with bounding boxes and text annotations
    cv2.imshow("OCR Result", resized_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

    return resized_image


files = ["first.jpeg", "second.jpeg", "third.jpeg", "fourth.jpeg"]
expected_first = ['we', 'breathe', 'innovation', 'not', 'pollution', 'follow',
                  'urban', 'pathfindes', 'we', 'are', 'better', 'than', 'walkie', 'talkie']
expected_second = ['vacanta', 'la', 'mare', 'cu', 'bunica', 'si', 'cu', 'catelul']
expected_third = ['toda', 'puiuleț', 'emanuela', 'coralia', 'trifan', 'alexandra', 'izabela',
                  'țăpuc', 'delia', 'elena', 'suciu', 'mircea', 'dan']
expected_fourth = ['astazi', 'mergem', 'la', 'inot']

vectors = [expected_first, expected_second, expected_third, expected_fourth]

for i in range(len(files)):
    if i == 2:
        print("~~~~~~~~~~~~~~~RESULTS~~~~~~~~~~~~~~")
        results = text_extraction(files[i])
        print(results)
        print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
        for word, expected_word in zip(results, vectors[i]):
            print(list(expected_word))
            print(list(word))
            print("| Hamming | ", hamming_distance(list(expected_word), list(word)))
            print("| Levenshtein | ", levenstein_distance(list(expected_word), list(word)))
            print("| Jaccard | ", jaccard_similarity(list(expected_word), list(word)))


text_extraction_with_bboxes("third.jpeg")

