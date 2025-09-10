## TextCraft – A Mini Text Editor in C++

### Overview
TextCraft is a beginner-friendly, console-based text editor written in modern C++ (C++11+). It demonstrates object-oriented design, basic file I/O, text manipulation, and a simple undo/redo mechanism implemented with stacks. The project is intentionally small, easy to read, and uses only the C++ standard library, so it is cross-platform (Windows, macOS, Linux).

### Features
- **Create new file**: Start a new editing session for a given file path.
- **Load existing file**: Open and read a text file into the editor.
- **Display content**: Print the current text to the console.
- **Append text**: Add more text to the end of the document.
- **Search & Replace**: Replace all occurrences of a word or phrase.
- **Save**: Write the current content back to disk.
- **Undo/Redo (Bonus)**: Navigate recent changes using stacks.

### Folder Structure
```
TextCraft/
│── README.md
│── sample.txt
│
├── src/
│   ├── main.cpp
│   └── TextEditor.cpp
│
├── include/
│   └── TextEditor.h
│
├── build/
│
└── tests/
    └── test_editor.cpp
```

### Build and Run
The project uses only standard C++ and requires a compiler that supports C++11 or newer (e.g., `g++`, `clang++`, MSVC).

Create the `build` directory (if it doesn't exist), compile, and run:

#### Windows (PowerShell or Command Prompt)
```bash
mkdir build 2> NUL
g++ src/main.cpp src/TextEditor.cpp -I include -std=c++11 -o build/textcraft
build\textcraft.exe
```

#### macOS / Linux
```bash
mkdir -p build
g++ src/main.cpp src/TextEditor.cpp -I include -std=c++11 -o build/textcraft
./build/textcraft
```

To run the tests (simple assertions, no framework needed):
```bash
g++ tests/test_editor.cpp src/TextEditor.cpp -I include -std=c++11 -o build/tests && ./build/tests
```
On Windows:
```bash
g++ tests/test_editor.cpp src/TextEditor.cpp -I include -std=c++11 -o build/tests.exe
build\tests.exe
```

### How to Use
1. Launch the program.
2. Use the menu to create a new file or load `sample.txt`.
3. Append text by entering lines and finish with a line that contains only `::end`.
4. Use Search & Replace to modify words/phrases.
5. Save your changes.
6. Try Undo/Redo to move between recent states.

### Learning Outcomes
- **OOP design** with a dedicated `TextEditor` class split into header and implementation.
- **File I/O** using `std::ifstream` and `std::ofstream`.
- **String manipulation** and replace logic without third-party libraries.
- **State management** using stacks for Undo/Redo.
- **Cross-platform development** with portable C++ code.

### Notes
- The `build/` directory is intended for compiled outputs and typically ignored by version control.
- The editor prints "[Empty file]" if no content is loaded yet.
