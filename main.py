import os
import cv2
import numpy as np
from PIL import Image

def generate_video(folder_name, images, video_name, fps):
    # print(images[0][0])
    frame = cv2.imread(os.path.join(folder_name, images[0][0]))
    height, width, layer = frame.shape
    video = cv2.VideoWriter(video_name, 0, fps, (width, height))
    
    for layers in images:
        image = cv2.imread(os.path.join(folder_name, layers[0]))
        for pic in layers:
            image = cv2.addWeighted(image, 0.5, cv2.imread(os.path.join(folder_name, pic)), 0.5, 0)
        video.write(image)
    cv2.destroyAllWindows()
    video.release()



video_name = "first.avi"

file = open("_images_", "r")
lines = file.readlines()
image_folder = lines[0].strip()
# print(image_folder)
if lines[1]=="nil":
    image_list = [[image] for image in os.listdir(image_folder)]
    # print(image_list)
    generate_video(image_folder, image_list, video_name, 1)
else:
    image_list = []
    for i in range(1, len(lines)):
        frame = []
        line = lines[i].split("$")
        for j in range(len(line)):
            frame.append(line[j].strip())
        image_list.append(frame)
    print(image_list)
    generate_video(image_folder, image_list, video_name, 1)

file.close()