
import cv2
import numpy as np

def compute_start_end(img):

    x1, x2, x3 = int(img.shape[0] * 0.5 * 0.8), int(img.shape[0] * 0.5), int(img.shape[0] * 0.5 * 1.3)
    y1, y2, y3 = int(img.shape[1] * 0.5 * 0.8), int(img.shape[1] * 0.5), int(img.shape[1] * 0.5 * 1.3)

    start_col = 0
    while not ( all(img[x1][start_col] == img[x2][start_col]) and all(img[x2][start_col] == img[x3][start_col])
                and all(img[x1][start_col] != [255, 255, 255])):
        start_col += 1

    start_row = 0
    while not (all(img[start_row][y1] == img[start_row][y2]) and all(img[start_row][y2] == img[start_row][y3])
                and all(img[start_row][y3] != [255, 255, 255])):
        start_row += 1

    end_col = img.shape[1] - 1
    while not (all(img[x1][end_col] == img[x2][end_col]) and all(img[x2][end_col] == img[x3][end_col])
                and all(img[x3][end_col] != [255, 255, 255])):
        end_col -= 1

    end_row = img.shape[0] - 1
    while not (all(img[end_row][y1] == img[end_row][y2]) and all(img[end_row][y2] == img[end_row][y3])
                and all(img[end_row][y3] != [255, 255, 255])):
        end_row -= 1

    return start_col, start_row, end_col, end_row


def compute_final_position(img, angle, speed, time):
    
    start_col, start_row, end_col, end_row = compute_start_end(img)

    sum_r = 0
    sum_c = 0
    tot = 0
    
    for r in range(start_row, end_row):
        for c in range(start_col, end_col):
            black = True
            for ch in range(img.shape[2]):
                if img[r, c, ch] != 0:
                    black = False
                    break
            if black:
                sum_r += r
                sum_c += c
                tot += 1
    sum_r = int(sum_r / tot)
    sum_c = int(sum_c / tot)

    square_size = (end_row - start_row) // 24
    row_pos = (sum_r - start_row) // square_size
    col_pos = (sum_c - start_col) // square_size

    dist = speed * (time * 60 * 60) # meters

    final_row = row_pos - round(dist * ((np.cos(angle / 180 * np.pi))) / 2000)
    final_col = col_pos + round(dist * ((np.sin(angle / 180 * np.pi))) / 2000)

    top_left_corner = (int(final_col * (end_col - start_col) / 48) + start_col, int(final_row * (end_row - start_row) / 24) + start_row)
    bottom_right_corner = (int((final_col + 1) * (end_col - start_col) / 48) - 1 + start_col, int((final_row + 1) * (end_row - start_row) / 24) - 1 + start_row)

    cv2.rectangle(img,top_left_corner,bottom_right_corner,(0,0,255), -1)
    cv2.imwrite('final_position.jpg', img)

    return final_col, final_row



if __name__ == "__main__":
    
    img = cv2.imread('grid_real.png')
    angle = 116
    speed = 0.098
    time = 144


    compute_final_position(img, angle, speed, time)
