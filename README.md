# THE Rich Man Of WALL's STREET
### A Distributed Stock Market Simulation Engine (C++ | OOP) to Learn Stock market in an Efficient way

---

## What is THE Rich Man Of WALL's STREET ?

THE Rich Man Of WALL's STREET is not just a project — it is a **learning-driven stock market simulator** designed to help users understand how financial markets actually behave.

Built using C++ and Object-Oriented Programming principles, it recreates the core mechanics of a stock exchange:
- Stock creation (IPOs)
- Buy and sell interactions
- Demand–supply driven price movements
- Portfolio tracking
- Dividend distribution

The system currently runs as a **console-based distributed simulation**, where multiple instances interact through a shared data layer to mimic a multi-user trading environment. :contentReference[oaicite:0]{index=0}

---

## Why this project exists

Most people learn the stock market theoretically.  
Very few get to *experience* how it behaves.

THE Rich Man Of WALL's STREET is built to bridge that gap.

The goal is simple:
> Create a system where users can **learn the market by participating in it**.

This is designed as the foundation of something bigger —  
a platform where learning finance feels like interacting with a real system, not reading static content.

---

## System Design

The architecture is structured into clear layers:

- **Entity Layer** – Core objects such as User, Company, Stock, Portfolio, Transaction  
- **Middleware Layer** – Synchronization and concurrency control using file-based coordination  
- **Market Engine** – Handles trading logic, price updates, and system behavior  
- **View Layer** – Terminal-based interface with live data and ASCII visualization  

This modular design allows the system to scale and evolve without breaking its core structure.

---

## Current Capabilities

- Multi-instance simulation (pseudo-distributed environment)  
- Dynamic stock pricing based on user activity  
- Persistent state using file handling  
- Portfolio and transaction tracking  
- Console-based visualization of market trends  

---

## Where this is going

This is just the starting point.

THE Rich Man Of WALL's STREET is being developed toward a **full-scale interactive market simulation platform**, including:

- A professional graphical user interface  
- Real-time stock data integration for accurate market learning  
- Online multi-user system (game-like environment)  
- Advanced trading systems (order matching, market depth)  
- Intelligent agents and simulation enhancements  

The long-term vision is to make this feel less like a program and more like a **live financial ecosystem**.

---

## Contributing

This project is open to people who want to build something meaningful.

If you:
- care about system design  
- want to explore financial simulations  
- enjoy building scalable systems  
- or simply want to improve and experiment  

then you are welcome here.

Fork it. Improve it. Break it. Rebuild it better.

Every contribution — whether small or structural — pushes this closer to its vision.

---

## Getting Started

Clone the repository and run the project locally:

```bash
git clone <https://github.com/Sri-Adithyaa/oop_project>
cd The_rich_man_of_walls_street
g++ main_file.cpp -o The_rich_man_of_walls_street
./The_rich_man_of_walls_street