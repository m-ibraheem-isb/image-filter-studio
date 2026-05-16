<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:0f0c29,50:302b63,100:24243e&height=200&section=header&text=Image%20Filter%20Studio&fontSize=40&fontColor=ffffff&animation=fadeIn" />
</p>

<p align="center">
  <b>Implemented by Muhammad Ibrahim</b><br>
  <i>FAST-NUCES Islamabad &nbsp;|&nbsp; Object Oriented Programming &nbsp;|&nbsp; Roll No: 25I-0045</i>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-17-blue?style=for-the-badge&logo=cplusplus" />
  <img src="https://img.shields.io/badge/Images-JPG%20%2F%20PNG-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Filters-10%20Implemented-purple?style=for-the-badge" />
  <img src="https://img.shields.io/badge/OOP-Full%20Showcase-success?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge" />
</p>

---

## Overview

**Image Filter Studio** is a console-based C++ application that loads real JPG and PNG images, applies a user-built pipeline of image filters, and writes the processed result back to disk — a real image you can open in any viewer.

Every OOP concept covered in the course appears somewhere in this project: raw pointers, polymorphism, encapsulation, operator overloading, virtual functions, friend classes, and multiple inheritance. Think of it as a complete OOP portfolio project built around real image processing.

> Developed as a Semester Project for **Object Oriented Programming** at FAST-NUCES Islamabad.

---

## Features

| Feature | Details |
|---------|---------|
| **Real Image I/O** | Load any JPG or PNG from disk; write processed output using `stb_image` |
| **10 Filters** | Pixel transforms, spatial filters, and geometric operations |
| **Filter Pipeline** | Chain multiple filters; each runs on the output of the previous |
| **ASCII Preview** | Terminal text-art preview generated after every filter step |
| **Two User Roles** | Admin manages catalog and accounts; Customer loads, filters, and saves |
| **File Persistence** | All users, sessions, and catalog state saved to `.txt` files |
| **Login & Registration** | CNIC validation, password rules, 3-attempt lockout, block system |

---

## The 10 Filters

| ID | Filter | Category | What It Does |
|----|--------|----------|--------------|
| 01 | Grayscale | Pixel Transform | Replaces R,G,B with (R+G+B)/3 |
| 02 | Invert / Negative | Pixel Transform | new = 255 − old for each channel |
| 03 | Brightness Adjust | Pixel Transform | Adds a fixed value to every channel; clamped to [0,255] |
| 04 | Contrast Stretch | Pixel Transform | Linearly scales each channel between min and max |
| 05 | Red Channel Only | Pixel Transform | Sets G=0, B=0; keeps R |
| 06 | Green Channel Only | Pixel Transform | Sets R=0, B=0; keeps G |
| 07 | Blue Channel Only | Pixel Transform | Sets R=0, G=0; keeps B |
| 08 | Box Blur (3×3) | Spatial Filter | Each pixel = average of itself and its 8 neighbours |
| 09 | Flip Horizontal | Geometric | Mirrors image left-to-right |
| 10 | Flip Vertical | Geometric | Mirrors image top-to-bottom |

---

## OOP Concepts Demonstrated

| Concept | Where It Appears |
|---------|-----------------|
| Abstract base class + pure virtual | `Filter` base class with `apply()` |
| Inheritance & Polymorphism | All 10 filter classes extend `Filter` |
| Runtime polymorphism | `FilterSession` holds `vector<Filter*>` |
| Dynamic memory (`new` / `delete`) | `Image` uses `Pixel**` with deep copy constructor |
| Friend class | `FilterSession` declared friend of `Image` |
| Operator overloading | `operator+` and `operator<<` on `Pixel` |
| Static utility function | `Pixel::clamp()` |
| Multiple inheritance | Demonstrated in at least one class |
| Virtual destructor | Present on `Filter` base class |
| User hierarchy | `Admin` and `Customer` both extend abstract `User` |
| Try / catch | Wrapped around all file I/O operations |
| Method chaining | `addFilter()` returns reference for chaining |

---

## Project Structure

```
Image-Filter-Studio/
├── src/
│   ├── main.cpp
│   ├── Pixel.h / Pixel.cpp
│   ├── Image.h / Image.cpp
│   ├── Filter.h
│   ├── Filters/              ← All 10 filter classes
│   ├── FilterSession.h / FilterSession.cpp
│   ├── User.h / Admin.h / Customer.h
│   └── FileManagers/         ← CustomerManager, CatalogManager, SessionManager
├── data/
│   ├── customers.txt
│   ├── catalog.txt
│   ├── sessions.txt
│   └── blocked_cnics.txt
├── include/
│   ├── stb_image.h
│   └── stb_image_write.h
└── README.md
```

---

## How to Run

```bash
# Clone the repository
git clone https://github.com/m-ibraheem-isb/Image-Filter-Studio.git
cd Image-Filter-Studio

# Compile (g++)
g++ -std=c++17 src/*.cpp -o ImageFilterStudio

# Run
./ImageFilterStudio
```

> Make sure `stb_image.h` and `stb_image_write.h` are present in your include path.  
> Download from: https://github.com/nothings/stb

---

## Sample ASCII Preview

```
=== Image Preview (20 x 10) ===
..........::::::::::::
..........::::::::::::
..........-::::=++++*
..........=::::+***##
..........*::::*###@@
..........*::::#@@@@@
..........*::::*###@@
..........=::::+***##
..........-::::=++++*
..........::::::::::::
Image size: 20 x 10 | Total pixels: 200
```

---

## File Formats

| File | What It Stores |
|------|---------------|
| `customers.txt` | CNIC \| Password \| FullName \| Gender \| Phone \| City \| IsBlocked |
| `catalog.txt` | FilterID \| FilterName \| Category \| IsEnabled |
| `sessions.txt` | CNIC \| Timestamp \| FiltersApplied \| OutputFile |
| `blocked_cnics.txt` | One banned CNIC per line |
| `<CNIC>_<timestamp>.png` | Output image from a completed session |

---

## Academic Integrity

- Built entirely in C++ with no third-party image processing libraries
- `stb_image` and `stb_image_write` used only for raw JPG/PNG file I/O
- All filter logic, OOP architecture, and file management is original work
- Fully meets all course requirements for the OOP Semester Project

---

## License

For educational use only. Please do not submit this work as your own.

---

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0:24243e,50:302b63,100:0f0c29&height=100&section=footer&animation=fadeIn" />
</p>

<p align="center">If this helped you, leave a ⭐ — it means a lot!</p>
