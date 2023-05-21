# import pandas as pd
import tensorflow as tf
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.preprocessing.image import ImageDataGenerator

# Data augmentation
train_datagen = ImageDataGenerator(
    rescale=1./255,
    rotation_range=30,
    shear_range=0.3,
    horizontal_flip=True,
    fill_mode='nearest',
)

val_datagen = ImageDataGenerator(
    rescale=1./255,
    # rotation_range=10,
    # shear_range=0.2,
    # horizontal_flip=True,
)

# Directories and batch size
train_dir = r'D:\Project-project\Fefi_Arm\Datasheet\train'
val_dir = r'D:\Project-project\Fefi_Arm\Datasheet\validation'
img_rows, img_cols = 180, 180
sub_object,batch_size = 3 ,3

# Image data generators
train_generator = train_datagen.flow_from_directory(
    train_dir,
    target_size=(img_rows, img_cols),
    batch_size=batch_size,
    class_mode='categorical',
    classes=['Hitam', 'Merah', 'Putih']
)

val_generator = val_datagen.flow_from_directory(
    val_dir,
    target_size=(img_rows, img_cols),
    batch_size=batch_size,
    class_mode='categorical',
    classes=['Hitam', 'Merah', 'Putih']
)

# Model architecture
model = tf.keras.models.Sequential([
          tf.keras.layers.Conv2D(32, (3, 3), activation = 'relu', input_shape = (img_rows, img_cols, 3)),
          tf.keras.layers.MaxPooling2D(2, 2),
          tf.keras.layers.Conv2D(64, (3, 3), activation = 'relu'),
          tf.keras.layers.MaxPooling2D(2, 2),
          tf.keras.layers.Conv2D(128, (3, 3), activation = 'relu'),
          tf.keras.layers.MaxPooling2D(2, 2),
          tf.keras.layers.Conv2D(128, (3, 3), activation = 'relu'),

          tf.keras.layers.MaxPooling2D(2, 2),
          tf.keras.layers.Flatten(),
          tf.keras.layers.Dense(200, activation = 'relu'),
          tf.keras.layers.Dropout(0.3,seed=112),
          tf.keras.layers.Dense(500, activation = 'relu'),
          tf.keras.layers.Dropout(0.5,seed=112),
          tf.keras.layers.Dense(sub_object, activation = 'softmax')
])
     
model.summary()

# Compile the model
model.compile(loss = 'categorical_crossentropy',
              optimizer = 'Adam',
            # optimizer = Adam(learning_rate = 1),
              metrics = ['accuracy'])

# Callbacks
class myCallback(tf.keras.callbacks.Callback):
    def on_epoch_end(self, epoch, logs={}):
        if logs.get('accuracy') > 0.98:
            print('\nAkurasi mencapai 98%')
            self.model.stop_training = True

callbacks = myCallback()

# Train the model
history = model.fit(
    train_generator,
    steps_per_epoch=train_generator.samples // batch_size,
    epochs=250,
    validation_data=val_generator,
    validation_steps=val_generator.samples // batch_size,
    verbose=1,
    callbacks=[callbacks]
)

# Save the model
model.save('D:\Project-project\Fefi_Arm\Datasheet\datasheet_seven1.h5')

