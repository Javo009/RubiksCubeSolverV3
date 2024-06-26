import cv2
import numpy as np

# Define color ranges in HSV
color_ranges = {
    'white': ((0, 0, 168), (172, 111, 255)),
    'yellow': ((20, 100, 100), (30, 255, 255)),
    'red1': ((0, 100, 100), (10, 255, 255)),
    'red2': ((160, 100, 100), (180, 255, 255)),
    'green': ((40, 70, 70), (80, 255, 255)),
    'blue': ((90, 70, 70), (128, 255, 255)),
    'orange': ((10, 100, 100), (20, 255, 255))
}

# Initialize the video capture
cap = cv2.VideoCapture(0)

# Function to get the color name from HSV value
def get_color_name(hsv_value):
    hsv_pixel = np.array([[hsv_value]], dtype=np.uint8)
    for color, (lower, upper) in color_ranges.items():
        lower = np.array(lower, dtype=np.uint8)
        upper = np.array(upper, dtype=np.uint8)
        if color == 'red1' or color == 'red2':
            if cv2.inRange(hsv_pixel, lower, upper) > 0:
                return 'red'
        else:
            if cv2.inRange(hsv_pixel, lower, upper) > 0:
                return color
    return 'undefined'

# Process each frame
while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Convert frame to HSV
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Detect contours and process each facelet
    contours, _ = cv2.findContours(cv2.inRange(hsv_frame, (0, 50, 50), (180, 255, 255)), cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    for contour in contours:
        # Approximate the contour to a polygon
        epsilon = 0.02 * cv2.arcLength(contour, True)
        approx = cv2.approxPolyDP(contour, epsilon, True)

        # Check if the approximated polygon is a square (4 sides)
        if len(approx) == 4 and cv2.contourArea(approx) > 1000:
            x, y, w, h = cv2.boundingRect(approx)
            aspect_ratio = w / float(h)
            if 0.9 <= aspect_ratio <= 1.1:
                # Get the color of the center of the square
                center_x, center_y = x + w // 2, y + h // 2
                hsv_value = hsv_frame[center_y, center_x]
                color_name = get_color_name(hsv_value)

                # Draw the detected square and color name
                cv2.drawContours(frame, [approx], -1, (0, 255, 0), 2)
                cv2.putText(frame, color_name, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

    # Display the frame
    cv2.imshow('Rubik\'s Cube Color Detection', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the capture and destroy all windows
cap.release()
cv2.destroyAllWindows()
