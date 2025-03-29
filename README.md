# Qt Fuzzy Finder

## Overview

Qt Fuzzy Finder is a GUI-based application that allows users to search for text within `.txt` and `.pdf` files using a fuzzy searching approach. The application scans a selected directory, lists the files, and enables users to search for specific terms using an approximate matching algorithm based on the Levenshtein Distance.

## Features

- **Directory Selection:** Users can select a directory to scan for `.txt` and `.pdf` files.
- **File Listing with Checkboxes:** Users can choose which files to include in the search.
- **Fuzzy Search:** Uses Levenshtein Distance to find approximate matches.
- **Multithreading:** Ensures the UI remains responsive during search operations.
- **Persistent Directory Storage:** Remembers the last opened directory using `QSettings`.
- **Context Menu:** Provides options to select/deselect all files in the list.

## Installation

### Prerequisites

- Qt 5 or Qt 6 installed
- C++ compiler (such as MinGW or MSVC)
- CMake (if using an external build system)

### Steps

1. Clone the repository:
   ```sh
   git clone https://github.com/abhishekMuge/QtFuzzyFinder.git
   cd QtFuzzyFinder
   ```
2. Open the project in Qt Creator or build manually:
   ```sh
   qmake && make  # For qmake users
   cmake . && make  # For CMake users
   ```
3. Run the application:
   ```sh
   ./QtFuzzyFinder  # On Linux/Mac
   QtFuzzyFinder.exe  # On Windows
   ```

## Usage

1. Click **Select Directory** to choose a folder containing `.txt` and `.pdf` files.
2. The application will list all detected files with checkboxes to enable/disable them for search.
3. Enter a search query and press **Enter**.
4. The application will perform a fuzzy search and display matching files.

## Contributing

1. Fork the repository.
2. Create a new branch:
   ```sh
   git checkout -b feature-branch
   ```
3. Make changes and commit:
   ```sh
   git commit -m "Added new feature"
   ```
4. Push the branch and create a Pull Request.

## License

This project is licensed under the MIT License.

## Author

[Abhishek Muge](https://github.com/abhishekMuge)

