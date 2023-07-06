#Import Libraries
#Import Libraries
from PIL import Image
import matplotlib.pyplot as plt

from scipy.ndimage import zoom
from PIL import Image
import numpy as np

#Read image
img=Image.open('tria.jpeg')
#show image
#plt.imshow(img)
#plt.show()


small_img=img.resize((24,24),Image.BILINEAR)
#resize
o_size=(24,24) #output size
res=small_img.resize(o_size,Image.NEAREST)
#save image
res.save('mario_8x8.jpg')
#display image
plt.imshow(res)
plt.show()

from PIL import Image
img = Image.open('mario_8x8.jpg').convert('L')
img.save('greyscale_8x8.jpg')

import cv2
import numpy

img=cv2.imread('greyscale_8x8.jpg')

img = cv2.threshold(img, 105, 255, cv2.THRESH_BINARY)[1]
cv2.imwrite("black-white.jpg", img)

img = Image.open("black-white.jpg")
np_img = numpy.array(img)

print(np_img.shape)



##
from PIL import Image
import numpy as np

img = Image.open("black-white.jpg").convert('L')

np_img = np.array(img)
np_img = ~np_img  # invert B&W
np_img[np_img > 0] = 1

print(np_img)

Array = np_img

# Displaying the array
print('Array:\n', Array)
file = open("file1.txt", "w+")

# Saving the array in a text file
content = str(Array)
file.write(content)
file.close()
