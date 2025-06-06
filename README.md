🧪 C++ Physics Simulator
A C++ physics simulator featuring a real-time GUI built with raygui. The simulator supports dynamic, kinematic, and static bodies, spring systems, and configurable physics parameters via an intuitive interface.

🚀 Features
🔷 Core Simulation
Physical Body Types:

Static – Fixed in space; not affected by forces or collisions.

Kinematic – Moves with predefined velocity; ignores external forces.

Dynamic – Fully simulated with force, gravity, and collision response.

Per-Object Configurations:

Mass

Size

Damping

Gravity Scale

Restitution (Bounciness)

Spring System:

Connect objects via springs.

Spring parameters:

Stiffness (spring constant)

Damping

🎛 GUI Controls (via raygui)
Object Management:

Add new objects of each type.

Modify individual object parameters.

Spring Management:

Create spring connections between selected objects.

Simulation Settings:

Adjust global parameters:

Global Gravity

Gravitational Force

Spring Stiffness Multiplier

Simulation Control:

Start / Stop simulation

Reset simulation (clears all state)

🧠 Physics Behavior
Accurate force-based motion and interactions.

Spring dynamics are computed using physics-based constraints.

Simulation state is maintained when paused, and fully reset when needed.

🛠 Build Instructions
Prerequisites
C++17 or later

raylib

raygui

Build (example using g++ on Linux)
bash
Copy
Edit
g++ -o physics_sim main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
Make sure raylib and raygui are installed and linked correctly.

📁 Project Structure
css
Copy
Edit
.
├── src/
│   ├── main.cpp
│   ├── physics_engine.cpp
│   └── gui_manager.cpp
├── assets/
├── include/
│   ├── raygui.h
│   └── physics_engine.h
└── README.md
📌 Future Plans / TODO
Collision resolution improvements

Save/load scenes

Visual debugging (e.g., force vectors, collision normals)

📄 License
This project is open-source under the MIT License.
