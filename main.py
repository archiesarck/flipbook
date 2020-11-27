import os
import cv2
from PIL import Image

def generate_video(folder_name, images, video_name, fps):
    frame = cv2.imread(os.path.join(folder_name, images[0]))
    height, width, layer = frame.shape
    video = cv2.VideoWriter(video_name, 0, fps, (width, height))
    
    for image in images:
        video.write(cv2.imread(os.path.join(folder_name, image)))
    cv2.destroyAllWindows()
    video.release()

video_name = "first.avi"
image_folder = "./imgs/"
image_list = [image for image in os.listdir(image_folder)]
generate_video(image_folder, image_list, video_name, 2)