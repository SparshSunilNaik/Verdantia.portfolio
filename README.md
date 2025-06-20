# Verdantia Portfolio

This repository combines a static portfolio website with C++ programs used for an academic course project on metro network management.

## Repository layout

- **index.html** and accompanying `*.css` files – the front page and section pages for the website.
- **CourseProj.cpp** – final C++ implementation containing metro network logic (routing, security, lost and found, etc.).
- **PseudoCodes.cpp** – a collection of commented algorithm snippets and experiments.
- **city.jpg**, **metro.jpg** and other images – visual assets referenced by the site.
- **.github/workflows/static.yml** – GitHub Pages workflow for deploying the static site.

## Viewing the website

Open `index.html` in a browser to explore the static site. If the repository is hosted on GitHub Pages, the site is automatically deployed using the workflow under `.github/workflows`.

## Building the C++ project

The main implementation resides in `CourseProj.cpp`. To compile and run it with a modern compiler:

```bash
g++ -std=c++17 -o course_project CourseProj.cpp
./course_project
```

The file `PseudoCodes.cpp` contains alternative algorithm examples which can be compiled in the same manner if needed.

## Project background

The C++ code models a small metro network and demonstrates algorithms such as Dijkstra's shortest path and a simple scheduling routine. It also includes a lost-and-found workflow and basic security checks. These features were developed as part of a course assignment and showcased through the accompanying website.


## Next steps

New contributors can explore the codebase with these suggestions:

- Open `index.html` to view the website locally.
- Study `CourseProj.cpp` to learn how the metro network logic works.
- Experiment with the algorithms inside `PseudoCodes.cpp`.
- Modify the CSS files or extend the C++ source to add new features.

