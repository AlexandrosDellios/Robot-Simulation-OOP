# 🐕 Robot cleanup simulation
![C++](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54)
![OOP](https://img.shields.io/badge/PyTorch-%23EE4C2C.svg?style=for-the-badge&logo=PyTorch&logoColor=white)

> **Bridging the Sim-to-Real gap** for legged robots using Curricular Domain Randomization and Bio-inspired Control.

---

## 📺 Demo
![Gait Demo](your-cool-gif-link-here.gif)
*Caption: Quadruped traversing a 20° slope with randomized friction.*

## 🧠 Technical Overview
This project implements a robust locomotion stack for a quadruped robot in **Pybullet**. The core challenge was balancing stability with energy efficiency.

### 🏗️ Control Architecture
I compared three distinct action spaces to evaluate learning efficiency:
1. **Hopf-oscillator CPG:** A bio-inspired rhythmic generator.
2. [cite_start]**Cartesian-space PD:** For precise foot-end effector control[cite: 18].
3. **Joint-space PD:** Standard actuator control.



### 🧪 Reinforcement Learning
[cite_start]Utilizing **PPO** and **SAC** (Stable Baselines3), the agent was trained using a multi-objective reward function[cite: 19]:

$$R = w_1 \cdot \text{tracking\_error} - w_2 \cdot \text{energy\_cost} - w_3 \cdot \text{impact\_forces}$$

## 🚀 Key Features
* [cite_start]**Sim-to-Real Bridge:** Used **Curricular Domain Randomization** (varying friction $\mu \in [0.2, 1.2]$ and sensor noise) to ensure policy robustness[cite: 20].
* [cite_start]**State Estimation:** Integrated an **EKF** to fuse IMU data with wheel-speed odometry[cite: 35].
* **Modular Codebase:** Clean C++/Python architecture with automated builds via **Makefile**.

## 💻 Installation & Usage
```bash
# Clone the repo
git clone [https://github.com/your-username/legged-robotics.git](https://github.com/your-username/legged-robotics.git)
cd legged-robotics

# Install dependencies
pip install -r requirements.txt

# Run the simulation
python main.py --mode test --policy ppo_cpg
