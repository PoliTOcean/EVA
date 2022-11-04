# Python program to illustrate HoughLine
# method for line detection
import cv2
import numpy as np

def compute_lines(img, th):
    #print(img)
    # Convert the img to grayscale
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

    # Apply edge detection method on the image
    edges = cv2.Canny(gray,50,150,apertureSize = 3)

    # This returns an array of r and theta values
    lines = cv2.HoughLines(edges,1,np.pi/180, th)
    return lines

def display_lines(img, th):

    lines = compute_lines(img, th)

    # The below for loop runs till r and theta values
    # are in the range of the 2d array
    if lines is not None:
        for l in lines:
            for r,theta in l:
                
                # Stores the value of cos(theta) in a
                a = np.cos(theta)

                # Stores the value of sin(theta) in b
                b = np.sin(theta)
                
                # x0 stores the value rcos(theta)
                x0 = a*r
                
                # y0 stores the value rsin(theta)
                y0 = b*r
                
                # x1 stores the rounded off value of (rcos(theta)-1000sin(theta))
                x1 = int(x0 + 1000*(-b))
                
                # y1 stores the rounded off value of (rsin(theta)+1000cos(theta))
                y1 = int(y0 + 1000*(a))

                # x2 stores the rounded off value of (rcos(theta)+1000sin(theta))
                x2 = int(x0 - 1000*(-b))
                
                # y2 stores the rounded off value of (rsin(theta)-1000cos(theta))
                y2 = int(y0 - 1000*(a))
                
                # cv2.line draws a line in img from the point(x1,y1) to (x2,y2).
                # (0,0,255) denotes the colour of the line to be
                #drawn. In this case, it is red.
                cv2.line(img,(x1,y1), (x2,y2), (0,0,255),2)

    return img



if __name__ == "__main__":
    
    th = 190
    img = cv2.imread('swimming_pool.jpg')
    final_img = display_lines(img, th)
    cv2.imwrite('linesDetected.jpg', final_img)

