import cv2
import tensorflow as tf
import numpy as np
import serial

port = 'COM6'  # Ubah sesuai dengan port serial yang digunakan
baud_rate = 115200  # Sesuaikan dengan baud rate pada perangkat

# Inisialisasi objek serial
ser = serial.Serial(port, baud_rate)

# Load model
model = tf.keras.models.load_model('D:\Project-project\Fefi_Arm\Datasheet\datasheet_seven1.h5')

# Define class labels
class_labels = ['Hitam', 'Putih', 'Merah']
labels = "prepare"

x1 = 160
y1 = 160
x2 = 340
y2 = 340

posRed: int = 0
posBlack: int = 0
posWhite: int = 0
posNot: int = 0

# Start video capture
cap = cv2.VideoCapture(1)
img_rows, img_cols = 180, 180

kondisi: int = 0

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    cropped_image = frame[y1:y2, x1:x2]


    # Resize frame to match the input shape of the model
    # resized_frame = cv2.resize(frame, (img_rows, img_cols))

    # Preprocess the frame
    # preprocessed_frame = resized_frame / 255.0
    preprocessed_frame = cropped_image / 255.0

    # Add a batch dimension to the preprocessed frame
    preprocessed_frame = np.expand_dims(preprocessed_frame, axis=0)

    # Make predictions on the preprocessed frame
    predictions = model.predict(preprocessed_frame)

    # Get the probabilities for each class
    class_probabilities = predictions[0]

    # Display the predicted class and its probability for each class
    for i, class_probability in enumerate(class_probabilities):
        class_label = class_labels[i]
        probability = class_probability * 100
        print(f"{class_label}: {probability:.2f}%")

        if class_label == 'Hitam' and probability > 10:
            cv2.putText(frame, "Hitam", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 255 ,0), 2)
            # Kirim data ke perangkat
            ser.write(b'1')
            kondisi = 1
        
        elif class_label == 'Merah' and probability == 100:
            cv2.putText(frame, "Merah", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 255, 0), 2)
            # Kirim data ke perangkat
            ser.write(b'2')
            kondisi = 1

        elif class_label == 'Putih' and probability > 0.15:
            cv2.putText(frame, "Putih", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 255 ,0), 2)
            # Kirim data ke perangkat
            ser.write(b'3')
            kondisi = 1   

    if kondisi == 0:
        cv2.putText(frame, "No Objet Detection", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1.0, (0, 0, 255), 2)
        # Kirim data ke perangkat
        ser.write(b'0')

    kondisi = 0 
 
    # Display the resulting frame
    cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
    cv2.imshow('frame', frame)
    
    # Press 'q' to quit
    if cv2.waitKey(1) & 0xFF == ord('q'): 
        break

# Release the capture and close all windows
cap.release()
cv2.destroyAllWindows()
