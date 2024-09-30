# Shader Meta Balls

Welcome to the Shader Meta Balls repository, where you can explore the dynamic interactions of meta balls simulated through shader programming. This project leverages GLSL shaders to render visually captivating interactions based on physics principles.

## Project Features

- **Realistic Physics Simulation**: Utilizes shaders to simulate the fluid-like interaction of meta balls.
- **Interactive Controls**: Supports zooming and other interactive features to explore the physics interactions in detail.
- **Shader Programming**: Employs GLSL (OpenGL Shading Language) to achieve realistic rendering and effects.

## Technical Details

The core of the simulation is built using C++ and integrates with SFML (Simple and Fast Multimedia Library) for window management and event handling. The GLSL shader code is used to calculate the visual effects and dynamics of meta balls in real time.

### Shader Code

The shader code (`Mihnea.frag`) handles the pixel-by-pixel rendering of meta balls, applying physics-based transformations to simulate motion and interaction. Key aspects of the shader include:
- **Distance Calculation**: Computes the influence of each meta ball on the surrounding space.
- **Color Mapping**: Dynamically adjusts colors based on the density and overlap of meta balls.

## Gallery

Below are images from the simulation showcasing various states and interactions of meta balls:

![Meta Ball Interaction](https://github.com/MihneaAndreescu/Shader-Meta-Balls/blob/main/0CDDF513-2FE0-4332-AF44-FB78357DDFBC.png)

![Meta Ball Dynamics](https://github.com/MihneaAndreescu/Shader-Meta-Balls/blob/main/700F86ED-1C60-4DB8-A477-DADD9732A7AF.png)

![Detailed Meta Ball Interaction](https://github.com/MihneaAndreescu/Shader-Meta-Balls/blob/main/AEEAF6D9-2E25-4163-A8E3-EF16DB4DE7C3.png)


## Controls

- **Zoom**: Use the mouse wheel to zoom in and out, allowing for detailed observation of the meta ball interactions.
- **Pan**: Click and drag to move around the simulation space.
