import os
import cv2
import numpy as np
from PIL import Image
from fpdf import FPDF
import math

def generate_pdf(folder_name, images, image_settings = None, page_settings = [800, 800], pdf_name = "output.pdf"):
    pdf = FPDF('P', 'mm', [page_settings[0], page_settings[1]])
    size = [math.floor(page_settings[0]/0.264583), math.floor(page_settings[1]/0.264583)]
    if image_settings is None:
        for i in range(len(images)):
            pdf.add_page()
            if images[i][0].endswith(".jpg") or images[i][0].endswith(".jpeg") or images[i][0].endswith(".png"):
                pdf.image(os.path.join(folder_name, images[i][0]), x = 0, y = 0)
    else:
        for i in range(len(images)):
            pdf.add_page()
            if images[i][0].endswith(".jpg") or images[i][0].endswith(".jpeg") or images[i][0].endswith(".png"):
                pdf.image(os.path.join(folder_name, images[i][0]),
                    x = image_settings[i][0], y = image_settings[i][1],
                    w = image_settings[i][2], h = image_settings[i][3])
    pdf.output(pdf_name, 'F')



def generate_video(folder_name, images, video_name = "output.avi", fps = 1):
    # print(images[0][0])
    if images[0][0].endswith(".jpg") or images[0][0].endswith(".jpeg") or images[0][0].endswith(".png"):
        frame = cv2.imread(os.path.join(folder_name, images[0][0]))
    else:
        print("file is not image file")
        return
    height, width, layer = frame.shape
    video = cv2.VideoWriter(video_name, 0, fps, (width, height))
    
    for layers in images:
        if layers[0].endswith(".jpg") or layers[0].endswith(".jpeg") or layers[0].endswith(".png"):
            video.write(cv2.imread(os.path.join(folder_name, layers[0])))
        else:
            print("file is not image file")
            break
    cv2.destroyAllWindows()
    video.release()


file = open("_images_", "r")
lines = file.readlines()
mode = lines[0].strip().split(" ")
file_name = lines[1].strip()
image_folder = lines[2].strip()
# print(image_folder)
if lines[3]=="nil":
    image_list = [[image] for image in os.listdir(image_folder)]
    # print(image_list)
    if mode[0]=="VIDEO":
        generate_video(image_folder, image_list, video_name=file_name, fps=int(mode[1]))
    elif mode[0]=="PDF":
        generate_pdf(image_folder, image_list, pdf_name=file_name, page_settings=[int(mode[1]), int(mode[2])])
    else:
        print("Unknown format")
else:
    image_list = []
    for i in range(3, len(lines)):
        frame = []
        line = lines[i].split("$")
        for j in range(len(line)):
            frame.append(line[j].strip())
        image_list.append(frame)
    # print(image_list)
    if mode[0]=="VIDEO":
        generate_video(image_folder, image_list, video_name=file_name, fps=int(mode[1]))
    elif mode[0]=="PDF":
        generate_pdf(image_folder, image_list, pdf_name=file_name, page_settings=[int(mode[1]), int(mode[2])])
    else:
        print("Unknown format")

file.close()