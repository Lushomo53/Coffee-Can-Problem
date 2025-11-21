
# Coffee Bean Problem – C Simulation

A **C program** that demonstrates the **Coffee Bean Problem**, illustrating how a process evolves and terminates according to simple rules—a conceptual demonstration of **halting and invariants**.

The program simulates a can of coffee beans (black or white) and repeatedly applies rules until only one bean remains.

---

## Problem Description

* The **can** contains beans that are either **black (B)** or **white (W)**.
* **Rules for picking beans**:

  1. Pick **two beans at random** from the can.
  2. If both beans are the **same color**:

     * Remove both beans.
     * Add **one black bean** back into the can.
  3. If the beans are **different colors**:

     * Remove the black bean.
     * Return the white bean to the can.
* **Invariants**:

  * The total number of beans **reduces by one** at each step.
  * The **parity of white beans** remains constant (even or odd).
* The simulation continues until **only one bean remains**, which is then displayed.

---

## Files

* `coffee_can.c` – Contains all structs, linked list operations, and logic for simulating the coffee bean problem.

---

## Key Structures

* **`Bean`** – Represents a coffee bean with a color (`BLACK` or `WHITE`).
* **`Node`** – Node for a singly linked list containing a bean.
* **`LinkedList`** – Custom linked list to store beans in the can.

---

## How It Works

1. **Initialize the can**:

   * Randomly generates 10 beans (black or white).
2. **Simulate picking beans**:

   * Randomly select two beans from the list.
   * Apply the rules for same or different colors.
   * Repeat until only one bean remains.
3. **Output**:

   * Initial count of white and black beans.
   * The **color of the last remaining bean**.

---

## Usage

1. **Clone the repository** (or copy the code):

```bash
git clone https://github.com/Lushomo53/Coffee-Can-Problem.git
```

2. **Compile the program**:

```bash
gcc coffee_can.c -o coffee_can
```

3. **Run the simulation**:

```bash
./coffee_can
```

4. **Sample output**:

```
Beans of colors white or black are being added to the can at random....
There are 4 white beans and 6 black beans
The last bean is Black
```

---

## Notes

* **Memory Management**:

  * All beans and list nodes are dynamically allocated and freed at the end of the program.
* **Randomness**:

  * Uses `rand()` seeded with `time(NULL)` for pseudo-random bean selection.
* **Demonstrates**:

  * Linked list operations (`add`, `get`, `remove`).
  * Invariants and termination in a stochastic process.

---

## Author

**Lushomo Lungo** – Implemented as a C learning exercise demonstrating linked lists and simulation of a simple halting problem.

