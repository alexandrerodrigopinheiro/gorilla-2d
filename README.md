# Gorilla 2D

> 🦍 Robust 2D Game Engine in C++ for advanced gameplay  
> Built on SDL2 and OpenGL, with modular systems for complex game architecture.

---

## 🧭 Overview

**Gorilla 2D** is a modern and extensible 2D game engine written in C++. It is designed for developers building **medium to large-scale games** with advanced rendering, physics, entity systems, and tools.

Gorilla 2D provides a clean modular architecture built on top of **SDL2**, **OpenGL**, and **custom ECS** — ideal for platformers, strategy, arcade, and simulation games.

---

## ✨ Features

- SDL2 + OpenGL accelerated renderer
- Custom Entity Component System (ECS)
- Sprite batching & texture atlases
- Physics integration (Box2D or custom)
- Input abstraction layer
- Scene graph & object hierarchy
- Audio system (SDL_mixer)
- Scripting integration (Lua planned)
- Debug UI (ImGui)
- Asset pipeline (images, tilemaps, audio)

---

## ⚙️ Requirements

- C++17+
- CMake 3.15+
- SDL2, SDL_image, SDL_mixer, SDL_ttf
- OpenGL 3.3+
- ImGui (optional)
- Box2D (optional)
- Linux, Windows, macOS

---

## 🔧 Build Instructions

1. **Clone the repository**

```bash
git clone https://github.com/your-org/gorilla-2d.git
cd gorilla-2d
```

2. **Configure and build with CMake**

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

3. **Run the demo**

```bash
./gorilla2d-demo
```

---

## 🧪 Project Structure

```plaintext
src/
├── core/         → Main engine loop, time, config
├── graphics/     → Renderer, textures, batching
├── ecs/          → Entity Component System
├── input/        → Input manager
├── audio/        → Sound & music
├── physics/      → Physics world and colliders
├── scripting/    → Lua bridge (optional)
examples/         → Sample games
tools/            → Editors and asset tools
include/          → Public headers
```

---

## 🧾 License

This project is released under the **MIT License**.  
© Gaming Innovators — Build powerful 2D games with confidence.

---

## 🤝 Credits

- SDL2
- OpenGL
- Dear ImGui
- Box2D
- Contributors & Indie Devs
