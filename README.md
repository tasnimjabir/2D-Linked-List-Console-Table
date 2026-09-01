# 2D Linked List Console Table

A console-based, dynamically resizable table built entirely with 2D (row + column) linked lists in C++. The table supports live keyboard navigation, in-place cell editing, and adding/deleting both rows and columns at runtime — all rendered as an ASCII table in the terminal.

**Made by:** Tasnim Jabir

---

## Demo

### Table view and navigation
![Table demo](demo1.jpg)

### Editing a cell
![Editing demo](demo2.jpg)

---

## Features

- **Dynamic table creation** — set a custom table name, column count, and row count at startup.
- **2D linked-list data structure** — each row is a `record` node (doubly linked vertically), and each row holds a doubly linked list of `cell` nodes horizontally. Column metadata (width/formatting) is tracked in a separate `columndata` linked list.
- **Auto-resizing columns** — column width automatically expands to fit the longest entry, and all existing rows are reformatted to match.
- **Keyboard-driven cell editor**
  - Arrow keys to move between cells (↑ ↓ ← →)
  - `Enter` to edit the currently selected cell
  - `Esc` to exit the editor and return to the main menu
- **Row and column management**
  - Add a row or column at any position
  - Delete a row or column at any position
  - Table auto-detects when it has been fully emptied and exits gracefully
- **Simple in-terminal menu** navigated with arrow keys and `Enter`

---

## How It Works

The table is built from three linked structures:

| Structure    | Purpose                                                              |
|--------------|-----------------------------------------------------------------------|
| `record`     | Represents one row; linked vertically via `prev`/`next`.             |
| `cell`       | Represents one cell in a row; linked horizontally via `prev`/`next`. |
| `columndata` | Tracks per-column width/formatting, linked horizontally.             |

Every `record` owns a horizontal chain of `cell` nodes (its columns), and every `record` is itself linked to the `record` above and below it — forming a full 2D grid out of linked lists rather than a traditional array/vector-based table.

---

## Controls

### Main Menu
| Key         | Action                     |
|-------------|-----------------------------|
| ↑ / ↓       | Move between menu options  |
| `Enter`     | Select highlighted option  |

### Cell Editor
| Key            | Action                          |
|----------------|----------------------------------|
| ↑ ↓ ← →        | Move to an adjacent cell        |
| `Enter`        | Edit the currently selected cell |
| `Esc`          | Return to the main menu         |

### Row / Column Menu
| Option | Action                          |
|--------|----------------------------------|
| `1`    | Add a row/column at a given position |
| `2`    | Delete a row/column at a given position |

---

## Building & Running

This project uses `<conio.h>`, so it is intended for **Windows** (or an environment with a `conio.h`-compatible library, e.g. `pdcurses` on Linux/macOS).

### Windows (MinGW / g++)
```bash
g++ dynamictable.cpp -o dynamictable.exe
dynamictable.exe
```

### Windows (MSVC)
```bash
cl dynamictable.cpp
dynamictable.exe
```

On startup you'll be prompted for:
1. **Table Name**
2. **Column Number**
3. **Row Number**

The table will then render in the console, ready for editing.

---

## Notes

- Column width auto-expands based on the longest string entered in that column, and existing rows are reflowed to match.
- Deleting the last remaining row or column will end the program with a "Table is fully deleted!" message.
- Input validation on menu prompts is minimal — invalid choices are caught and reported, but out-of-range positions should be entered carefully.

---

## License

Feel free to use, modify, and learn from this project.
