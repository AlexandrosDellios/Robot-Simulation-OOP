# 🤖 Robot cleanup simulation
![C++](https://img.shields.io/badge/C++-3670A0?style=for-the-badge&logo=cplusplus&logoColor=ffdd54)
![OOP](https://img.shields.io/badge/OOP-%23EE4C2C.svg?style=for-the-badge&logo=cmake&logoColor=white)

> **Simulation of a cleanup mission with multiple robot types. Simulation uses Gtkmm for the GUI and OOP for the logic.

---


## 🏗️ Robot Class Hierarchy
The three robot types (Neutralizer, Repairer, and Spatial) are implemented as subclasses of the Robot base class. This base class utilizes the Circle data structure from the Shape module, specifically implementing its constructor and "getter" methods. Each subclass defines its own specific constructor to initialize additional unique attributes.

The Spatial class, which tracks the update count and the various robot types, includes an organized data structure (data) as an attribute. Finally, we opted for function overloading rather than polymorphism for the robot rendering logic (draw_Robot).



## 💾 Data Structuring of Model Entities
The Simulation class manages the primary data structures, containing vectors for the neutralizer robots, repairer robots, particles, and the spatial robot. This class also handles state persistence by storing the filename currently in use. The Particle class utilizes the Square structure from the Shape module, featuring a constructor for initialization and a getter for spatial data access.

We implemented a global simulation instance within the Simulation module, allowing various functions to access the state without passing instances as arguments. This design choice facilitates a clean separation between the core logic and the GUI module responsible for the user interface.



## 🚀 Description of Geometric Types (Shape Module)
* S2d: Represents Cartesian coordinates using x and y attributes.
* Square (Carre): Defines a square via a center point (type S2d) and its side length.
* Circle (Cercle): Defines a circular boundary using center coordinates and a radius.
