<h2> About project</h2>
face detetection using LBPH face recognizer of OpenCV and Qt
This is a opencv and qt based project to detect and identify faces over a live video stream.
<h2> Background on face recognition</h2>
To detect a face from stream of frames and train a model to recognize the face to a trained label from a live stream, following steps are needed to be processed.

1. Face Detection
2. Data Gathering: Extract unique characteristics of a person face that it can use to differentiate him from another person, like eyes, mouth, nose, etc.
3. Data Comparison: Despite variations in light or expression, it will compare those unique features to all the features of all the people you know.
4. Face Recognition


<h4>Theory of OpenCV face recognizers</h4>
There are three easy steps to computer coding facial recognition, which are similar to the steps that our brains use for recognizing faces. These steps are:

Data Gathering: Gather face data (face images in this case) of the persons you want to identify.
Train the Recognizer: Feed that face data and respective names of each face to the recognizer so that it can learn.
Recognition: Feed new faces of that people and see if the face recognizer you just trained recognizes them.

OpenCV has three built-in face recognizers and thanks to its clean coding, you can use any of them just by changing a single line of code. Here are the names of those face recognizers and their OpenCV calls:

1. EigenFaces – EigenFaceRecognizer::create()
2. FisherFaces – FisherFaceRecognizer::create()
3. Local Binary Patterns Histograms (LBPH) – LBPHFaceRecognizer::create()

I have used LBPH Face Recognizer in my project. Below is a brief discussion on LBPH.

Eigenfaces and Fisherfaces are both affected by light and, in real life, we can't guarantee perfect light conditions. LBPH face recognizer is an improvement to overcome this drawback. The idea with LBPH is not to look at the image as a whole, but instead, try to find its local structure by comparing each pixel to the neighboring pixels. 

The LBPH Face Recognizer Process
Take a 3×3 window and move it across one image. At each move (each local part of the picture), compare the pixel at the center, with its surrounding pixels. Denote the neighbors with intensity value less than or equal to the center pixel by 1 and the rest by 0.

After you read these 0/1 values under the 3×3 window in a clockwise order, you will have a binary pattern like 11100011 that is local to a particular area of the picture. When you finish doing this on the whole image, you will have a list of local binary patterns.

![alt text](https://github.com/noumanyosuf/face-detetection-using-opencv/blob/master/54_blog_image_10.jpg)

Now, after you get a list of local binary patterns, you convert each one into a decimal number using binary to decimal conversion (as shown in above image) and then you make a histogram of all of those decimal values.

In the end, you will have one histogram for each face in the training data set. That means that if there were 100 images in the training data set then LBPH will extract 100 histograms after training and store them for later recognition. Remember, the algorithm also keeps track of which histogram belongs to which person.

Later during recognition, the process is as follows:

Feed a new image to the recognizer for face recognition.
The recognizer generates a histogram for that new picture.
It then compares that histogram with the histograms it already has.
Finally, it finds the best match and returns the person label associated with that best match.

Please read https://iq.opengenus.org/lbph-algorithm-for-face-recognition/ to understand about LBPH algorithm in detail.

<h2> About implementation </h2>
Below is brief description on the list of classes in the projects:</br>
1. FaceDetector: detectes faces in a Mat frame, train a FaceRecognizer and predicts trained faces to return the registered label.</br>
2. VideoStreamer:[model] uses opencv to open webcamera to start and stop video stream and emit each fetched frames.</br>
3. RegisterWidget:[view] register window to take snap of face to be recognized again a provided label.</br>
4. MenuWidget:[view] window to start stream, stop stream and to navigate to register window.</br>
5. MainWidget:[view model] main window to hold stream video and, RegisterWidget and MenuWidget as stack widgets. This widget also facilitates the event/signal forwarding between diffrent widgets.</br>
globalconstants.h: hold all the constants of the projects.</br>

Note:
To be able to use LBPHFaceRecognizer in opencv, build opencv with extra module of FaceRecognizer.

