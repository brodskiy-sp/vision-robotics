# Vision Robotics

**Embedded Computer Vision · C++ · OpenCV · Robotics**

Vision Robotics is a hands-on engineering project focused on embedded computer vision, real-time image processing, object tracking, and human–robot interaction.

The project starts with a compact embedded Linux platform and a camera, gradually building toward vision-based interaction systems and autonomous robotics.

## Project Goals

The long-term goals are to:

- Detect and track objects in real time.
- Explore hand and finger tracking.
- Develop gesture-based human–computer interaction.
- Control a Windows cursor using hand movements.
- Explore computer vision applications in autonomous ground robots.
- Investigate coordination between autonomous robots for industrial assistance.

## Hardware

| Component | Specification |
|---|---|
| Embedded board | Luckfox Pico Plus |
| SoC | Rockchip RV1103 |
| CPU | ARM Cortex-A7 |
| NPU | 0.5 TOPS |
| RAM | 64 MB DDR2 |
| Camera | SC3336 CAM V2 |
| Camera resolution | 3 MP |

## Software & Development Environment

| Technology | Purpose |
|---|---|
| C++ | Core application development |
| OpenCV | Image processing and computer vision |
| FFmpeg | Video decoding |
| CMake | Build configuration |
| Linux / Buildroot | Embedded operating system |
| RTSP | Video streaming |
| Windows 11 | Host development environment |
| MSYS2 / UCRT64 | C++ development toolchain |

## Current Implementation

The initial development stage focuses on establishing a reliable video pipeline between the embedded camera platform and a Windows PC.

### Implemented

- Established an RTSP connection to the Luckfox camera stream.
- Received and decoded video frames using OpenCV and FFmpeg.
- Retrieved frames with `cv::VideoCapture`.
- Saved captured frames as PNG images.
- Implemented continuous frame acquisition.
- Added keyboard-controlled program termination.
- Measured frame acquisition performance using `std::chrono`.
- Implemented BGR-to-grayscale conversion.
- Tested Gaussian blur with different kernel sizes.
- Implemented BGR-to-HSV conversion.
- Applied color thresholding with `cv::inRange()`.
- Generated binary segmentation masks.
- Extracted selected image regions using `cv::bitwise_and()`.

### Initial Experimental Results

The RTSP stream was successfully received and processed on the Windows host.

Typical measured acquisition rates during initial experiments were approximately 20–25 FPS. Actual performance varies with network conditions, decoding, and processing workload.

An initial color segmentation experiment successfully isolated a green object from its background.

These experiments establish the foundation for subsequent object detection and tracking.

## System Architecture
   ```mermaid
flowchart TD

    A["SC3336 Camera"] --> B["Luckfox Pico Plus"]

    B --> C["Rockchip RV1103 - Embedded Linux"]

    C --> D["RTSP Video Stream"]

    D --> E["Windows PC"]

    E --> F["FFmpeg + OpenCV"]

    F --> G["Decoded Frames"]

    G --> H["Image Processing"]

    H --> I["HSV Segmentation"]

    I --> J["Binary Mask"]

    J --> K["Object Detection and Tracking"]

    K -.-> L["Gesture Recognition"]

    L -.-> M["Human-Robot Interaction"]
```


## Development Roadmap

### Phase 1 — Video Pipeline
- [x] Connect to the camera stream.
- [x] Receive and decode RTSP frames.
- [x] Save captured images.
- [x] Measure frame acquisition performance.

### Phase 2 — Image Processing
- [x] BGR and grayscale image conversion.
- [x] Gaussian blur experiments.
- [x] HSV color conversion.
- [x] Color thresholding and binary masks.
- [x] Color-based object isolation.
- [x] Contour detection.
- [x] Object center calculation.
- [ ] Real-time object tracking.

### Phase 3 — Hand Tracking
- [ ] Hand detection.
- [ ] Finger and fingertip localization.
- [ ] Hand movement tracking.
- [ ] Gesture recognition.

### Phase 4 — Human–Robot Interaction
- [ ] Gesture-based Windows cursor control.
- [ ] Low-latency interaction pipeline.
- [ ] Communication with robotic platforms.

### Phase 5 — Autonomous Robotics
- [ ] Ground robot navigation.
- [ ] Multi-robot coordination.
- [ ] Exploration of industrial assistance applications.

## Engineering Approach

This project follows an experimental, incremental development process:

1. Understand the hardware and software pipeline.
2. Measure performance before optimizing.
3. Implement and test individual computer vision operations.
4. Evaluate accuracy, latency, and computational cost.
5. Gradually integrate components into a complete system.

The focus is not only on making the system work, but also on understanding how and why it works.

## Project Status

**Early development — embedded video acquisition and fundamental computer vision experiments.**

This repository documents the ongoing development process, experiments, implementation details, and future milestones.

---

*Built step by step with C++, OpenCV, embedded Linux, and robotics.*
