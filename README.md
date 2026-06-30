# CLOSED SOURCE - EXAMPLE of Haris Engine with GPU Acceleration

Feature: GPU Hardware Acceleration.
Target: Performance optimization and high-speed processing.


💡 Note: The quality and frame rate of this demo have been reduced to optimize file size for the repository.
![App Demo](./document/preview/__HarisEngine_GPU_Processing.gif)

```mermaid
graph TD
    subgraph App [Modern Application Layer]
        A[Hardware <br> Window ]
        B[Hardware I/O<br> Keyboard / Mouse ]
        C[Event/Task Engine<br> Thread Pool / Callback Subriber]
        GPU_App[Vision / AI Core<br>Parallel Compute]
    end
    
    subgraph Wrapper [" "]
        SAL_Core[Your Framework<br> GLFW / glm / imgui / ...]
        SAL_GPU[Unified Memory & GPU Stream Manager]
        Wrapper_note[System Abstraction Layer / Wrappers / Libs]
    end

    style Wrapper_note fill:none,stroke:none,font-weight:none
    
    subgraph Hardware [Linux Kernel & Hardware Primitives]
        D[Kernel Drivers / VFS]
        E[GPU / NPU Accelerator<br> Vulkan / OpenCL / ... ]
    end

    A <--> SAL_Core
    B --> SAL_Core
    C --> SAL_Core
    GPU_App --> SAL_GPU

    SAL_Core <--> D
    SAL_GPU --> E
    E <--> D
```

## Build and Run example with libraries in HarisEngine package.

```sh
cd example/
./cmake_build_and_run.sh
```
