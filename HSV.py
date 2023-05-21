import cv2
import numpy as np

def nothing(x):
    pass

# Membuat jendela untuk mengatur nilai HSV
cv2.namedWindow('HSV Calibration')

# Membuat trackbars untuk mengatur nilai HSV
cv2.createTrackbar('Hue Low', 'HSV Calibration', 0, 179, nothing)
cv2.createTrackbar('Hue High', 'HSV Calibration', 179, 179, nothing)
cv2.createTrackbar('Saturation Low', 'HSV Calibration', 0, 255, nothing)
cv2.createTrackbar('Saturation High', 'HSV Calibration', 255, 255, nothing)
cv2.createTrackbar('Value Low', 'HSV Calibration', 0, 255, nothing)
cv2.createTrackbar('Value High', 'HSV Calibration', 255, 255, nothing)

# Mengakses kamera
cap = cv2.VideoCapture(1)

while True:
    # Membaca frame dari kamera
    _, frame = cap.read()

    # Mengubah frame ke mode HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Mendapatkan nilai trackbar saat ini
    hue_low = cv2.getTrackbarPos('Hue Low', 'HSV Calibration')
    hue_high = cv2.getTrackbarPos('Hue High', 'HSV Calibration')
    saturation_low = cv2.getTrackbarPos('Saturation Low', 'HSV Calibration')
    saturation_high = cv2.getTrackbarPos('Saturation High', 'HSV Calibration')
    value_low = cv2.getTrackbarPos('Value Low', 'HSV Calibration')
    value_high = cv2.getTrackbarPos('Value High', 'HSV Calibration')

    # Membuat batas HSV
    lower_hsv = np.array([hue_low, saturation_low, value_low])
    upper_hsv = np.array([hue_high, saturation_high, value_high])

    # Mengaplikasikan thresholding HSV
    mask = cv2.inRange(hsv, lower_hsv, upper_hsv)
    result = cv2.bitwise_and(frame, frame, mask=mask)

    # Menampilkan frame asli, mask, dan hasil
    cv2.imshow('Original', frame)
    cv2.imshow('Mask', mask)
    cv2.imshow('Result', result)

    # Keluar dari loop jika tombol 'q' ditekan
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Melepaskan kamera dan menutup jendela
cap.release()
cv2.destroyAllWindows()