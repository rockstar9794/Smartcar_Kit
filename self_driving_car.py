import time
import cv2
import numpy as np
import math
from perf_motor import Motor
from motor_details import MotorTools


def main():
    theta = 0
    minLineLength = 5
    maxLineGap = 10
    cap = cv2.VideoCapture(0)
    motor = Motor()
    motor.initDCMotor()
    while True:
        ret, image = cap.read()
        if ret:
            #cv2.imshow("Orig", image)

	    #image Proccessing of Line tracer
            height = image.shape[0]
            width = image.shape[1]
            image1= image[int(height-height/7):int(height), 0:width]
            
            low_yellow = np.array([18,94,140])
            up_yellow = np.array([48,255,255])
            
            frame1 = cv2.GaussianBlur(image1, (5, 5), 0)
            hsv1 = cv2.cvtColor(frame1, cv2.COLOR_BGR2HSV)
            
	    #Traffic Light Detection
            #image2= image[int(height-height/1):int(height), 0:width]
            #frame2 = cv2.GaussianBlur(image2, (5, 5), 0)
            #hsv2 = cv2.cvtColor(frame2, cv2.COLOR_BGR2HSV)
            
            #lower_red = np.array([0,50,50])
            #upper_red = np.array([10,255,255])
            #maskr = cv2.inRange(hsv2, lower_red, upper_red)
            #res = cv2.bitwise_and(frame,frame, maskr= maskr)
                       
            
            masky = cv2.inRange (hsv1, low_yellow, up_yellow)
            gray = cv2.cvtColor(image1, cv2.COLOR_BGR2GRAY)
            
            thresh = cv2.threshold(frame1, 60, 255, cv2.THRESH_BINARY)[1]
            edged = cv2.Canny(masky, 75, 150)
            lines = cv2.HoughLinesP(edged, 1, np.pi/180, 50, minLineLength, maxLineGap=250)
            if lines is not None:
                for line in lines:
                    for x1, y1, x2, y2 in lines[0]:
                        cv2.line(image1,(x1,y1),(x2,y2),(0,255,0),2)
                        theta = theta+math.atan2((y2-y1), (x2-x1))
            print(theta)
            threshold = 1
	    #Following the Line
            if(theta>-0.4 and theta<0.3):
                motor.goForward()
                print("Forward")
            elif(theta<=-0.4):
                motor.goRight()
                print("Right") 
            elif(theta>0.3):
                motor.goLeft()
                print("Left")
            
            theta = 0
            cv2.imshow("Frame", image1)
            #cv2.imshow("res", maskr)
            key = cv2.waitKey(1) & 0xFF
            if key == ord("q"):
                break
        else: 
            break
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()

