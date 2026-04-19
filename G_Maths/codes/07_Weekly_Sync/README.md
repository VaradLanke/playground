# Phase 1 Completion Report: Foundations of 3D Mathematics

---

## 1. Curriculum Phase 1: Strategic Mission Overview

The primary objective of Phase 1 is to establish a rigorous baseline for mathematical notation and spatial intuition, transitioning from theoretical abstraction to the pragmatic requirements of a high-performance graphics engine.

By grounding our engineers in these fundamentals, we ensure that the subsequent implementation of cameras, physics systems, and rendering pipelines is built upon a stable, intuitive framework rather than rote memorization of formulas.

This phase prioritizes the **"Practical Track"**, emphasizing the translation of mathematical identities into optimized C++ code.

**Strategic Goal:**
- Move beyond the "Algebra Refresher" stage
- Achieve architectural readiness
- Enable instinctive application of algebra and trigonometry in:
  - Collision detection
  - Vertex transformation

---

## 2. Algebraic Foundation and Arithmetic Properties

### Exponent Properties

- Product Rule: a^n · a^m = a^(n+m)
- Power of a Power: (a^n)^m = a^(nm)
- Power of a Product: (ab)^n = a^n b^n
- Zero Exponent: a^0 = 1, where a ≠ 0
- Quotient Rule: a^n / a^m = a^(n-m)
- Negative Exponents: a^(-n) = 1 / a^n
- Rational Exponents: a^(n/m) = √[m](a^n) = (√[m](a))^n

---

### Properties of Radicals

- Root-to-Exponent Conversion: √[n](a) = a^(1/n)
- Product Property: √[n](ab) = √[n](a) √[n](b)
- Root of a Root: √[m](√[n](a)) = √[nm](a)
- Quotient Property: √[n](a/b) = √[n](a) / √[n](b)
- Even/Odd Roots: √[n](a^n) = |a| if n is even, else a

---

### Factoring Formulas and Solving

- Difference of Squares: x^2 - a^2 = (x + a)(x - a)
- Perfect Square Trinomials: x^2 + 2ax + a^2 = (x + a)^2
- Sum of Cubes: x^3 + a^3 = (x + a)(x^2 - ax + a^2)
- Difference of Cubes: x^3 - a^3 = (x - a)(x^2 + ax + a^2)
- Square Root Property: If x^2 = p, then x = ±√p

---

## 3. Quadratic Solutions for Ray Tracing Root-Finding

### Technical Spotlight: The Quadratic Formula

In the ray-tracing module, the quadratic formula enables O(1) intersection computation for spherical primitives.

### Formula

ax^2 + bx + c = 0, where a ≠ 0

x = (-b ± √(b^2 - 4ac)) / (2a)

### Discriminant

D = b^2 - 4ac

- D > 0 → Two real, unequal roots (entry & exit points)
- D = 0 → One repeated root (tangent)
- D < 0 → No real intersection

---

### Geometric Derivation (Completing the Square)

- Start with: x^2 + (b/a)x
- Represent:
  - Square → x^2
  - Rectangle → (b/a)x
- Split rectangle into two parts: width b/(2a)
- Add missing square area: (b/2a)^2
- Form perfect square: (x + b/2a)^2
- Solve → derive general quadratic formula

---

## 4. Complex Number Arithmetic for Future Rotations

Define imaginary unit: i = √(-1)

| Operation      | Formula                                      | Property                        |
|----------------|----------------------------------------------|---------------------------------|
| Addition       | (a + bi) + (c + di) = (a + c) + (b + d)i     | Commutative                     |
| Subtraction    | (a + bi) - (c + di) = (a - c) + (b - d)i     | Sign Distribution               |
| Multiplication | (a + bi)(c + di) = (ac - bd) + (ad + bc)i    | FOIL / Distributive             |
| Conjugate      | ā = a - bi                                   | Reflection on real axis         |
| Modulus        | \|a + bi\| = √(a² + b²)                        | Magnitude                       |

---

## 5. Trigonometric Foundations and Spatial Distance

### Core Concepts

1. Unit Circle
   - x = cosθ
   - y = sinθ

2. Rotation Transforms
   - Basis for rotation matrices

3. Field of View (FOV)

tan(θ/2) = opposite / adjacent

Where θ is the full field of view angle. Used for projection matrix scaling.

---

### Distance Formula

#### 2D Distance

d = √((x₂ - x₁)^2 + (y₂ - y₁)^2)

#### 3D Distance

d = √((x₂ - x₁)^2 + (y₂ - y₁)^2 + (z₂ - z₁)^2)

---

## 6. C++ Implementation Milestones: The Math Library

### Key Achievements

- Vector Primitives
  - Vector2
  - Vector3

- Operator Overloading
  - Addition
  - Subtraction
  - Scalar multiplication
  - Implemented using pass-by-reference

- Memory Alignment
  - Component layout (x, y, z) for all vector types
  - Cache-friendly design

---

### Notational Style Guide

For mathematical expressions in documentation:
- Scalars → italic lowercase (x, y, z)
- Vectors → bold uppercase (V, P)
- Quaternions → bold lowercase (q)
- Matrices → bold uppercase (M)
- Operations → standard symbols (·, ×, |·|)

---

## 7. Integration: The Rendering Pipeline Context

### Transformation Flow

1. Object Space  
2. World Space  
3. Camera Space  
4. Window Space  

---

### Critical Tests

#### Pixel Ownership Test
- Validates if (x, y) lies inside viewport bounds

#### Depth Test
- Uses z-value comparison
- Based on 3D distance logic
- Ensures:
  - Hidden surface removal
  - Closest fragment rendering

---

## Final Note

Phase 1 establishes the mathematical backbone of the rendering engine, ensuring that all higher-level systems operate on a foundation that is both:

- Mathematically sound
- Computationally efficient
