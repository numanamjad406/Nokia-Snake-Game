# Nokia-Snake-Game
🐍 Nokia Snake — Multiplayer Edition 🎮 A C++ console remake of the classic Snake game with 3 players battling live! Features real-time controls (Arrows/WASD/IJKL), dynamic growth, wrap-around walls, collision detection &amp; live scoring. ⚡🏆 My first-semester C++ project!
# 🐍 NOKIA SNAKE — MULTIPLAYER EDITION

### A Classic Reborn in the Console

**Built with C++ | Windows Console API | Real-Time Multiplayer**

🟢 3 Players &nbsp;•&nbsp; ⚡ Real-Time Input &nbsp;•&nbsp; 🍎 Dynamic Growth &nbsp;•&nbsp; 🏆 Live Scoring


---

> 🎓 **First Semester Project #2** — A hands-on journey through structs, pointers, dynamic memory, and real-time console game development in C++.

---

## 🌟 Overview

Remember the iconic Nokia Snake game? Now imagine **three snakes, three players, one battlefield** — all on a single console screen, competing live.

This project takes the nostalgic classic and supercharges it into a **3-player simultaneous showdown**, where players race to grow the longest, avoid crashing into themselves or rivals, and rack up the highest score.

---

## ✨ Features

| 🎯 Feature | 📝 Description |
|---|---|
| 👥 **3-Player Multiplayer** | Three independently controlled snakes on one screen |
| ⚡ **Real-Time Controls** | Smooth, non-blocking input using `_kbhit()` & `_getch()` |
| 🌱 **Dynamic Growth** | Snakes grow using dynamic memory (`new[]` / `delete[]`) |
| 🔁 **Wrap-Around Walls** | Snakes loop around edges instead of dying at walls |
| 💥 **Collision Detection** | Detects self-collision and collisions with other snakes |
| 🍎 **Smart Food Spawning** | Food never spawns on top of a snake |
| 🎨 **Colorful Console UI** | Each snake & UI element rendered in distinct colors |
| 🏆 **Live Score Tracking** | Real-time score updates for every player |
| 🪦 **Game Over Screen** | Shows who lost and the final scores of all players |

---

## 🕹️ Controls

| 🎮 Player | 🔼 Up | 🔽 Down | ◀️ Left | ▶️ Right |
|:---:|:---:|:---:|:---:|:---:|
| **Player 1** | ↑ | ↓ | ← | → |
| **Player 2** | W | S | A | D |
| **Player 3** | I | K | J | L |


> Press **ENTER** on the start screen to begin the game!

---

## 🛠️ Requirements

- 🖥️ **OS:** Windows (uses `<windows.h>` & `<conio.h>`)
- ⚙️ **Compiler:** g++ (MinGW) or MSVC (Visual Studio)

---

## ▶️ How to Run

### Option 1: g++ / MinGW
```bash
g++ nokia_snake.cpp -o snake.exe
snake.exe
```

### Option 2: Visual Studio
1. Create a new **Console App (C++)** project
2. Paste in `nokia_snake.cpp`
3. Build & Run (`Ctrl + F5`)

---

## 📂 Project Structure

```
nokia-snake-multiplayer/
│
├── nokia_snake.cpp     # Main source code
└── README.md           # You're reading it!
```

---

## 🧠 Concepts Practiced

- 🧩 Structures (`struct`)
- 🧷 Pointers & Dynamic Memory Allocation
- 📦 Arrays of Structs
- 🔄 Pass-by-Reference Functions
- 🖥️ Windows Console API Manipulation
- ⌨️ Real-Time Keyboard Input
- 🔁 Game Loop Architecture

---

## 🚀 Roadmap / Future Ideas

- [ ] Pause / Resume functionality
- [ ] Adjustable difficulty & speed levels
- [ ] Obstacles & walls (no wrap-around mode)
- [ ] Persistent high-score leaderboard
- [ ] Sound effects 🔊

---

## 📌 About This Project

Built purely for **learning and fun** as part of a first-semester C++ assignment — focused on applying core programming concepts in a real, interactive project rather than just theory.

---

## 📄 License

Open-source and free to use for learning purposes 💙

### 🐍 Happy Coding & Game On! 🎮


