#include "TextEditor.h"

#include <iostream>
#include <string>

static void printMenu() {
    std::cout << "\n=== TextCraft – Mini Text Editor ===\n";
    std::cout << "1. Create new file\n";
    std::cout << "2. Load existing file\n";
    std::cout << "3. Display content\n";
    std::cout << "4. Append text\n";
    std::cout << "5. Search & Replace\n";
    std::cout << "6. Save\n";
    std::cout << "7. Undo\n";
    std::cout << "8. Redo\n";
    std::cout << "9. Show file path\n";
    std::cout << "0. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    TextEditor editor;
    bool running = true;

    while (running) {
        printMenu();
        int choice = -1;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        std::cin.ignore(1024, '\n'); // discard rest of line

        switch (choice) {
            case 1: {
                std::string path;
                std::cout << "Enter new file path (e.g., sample.txt): ";
                std::getline(std::cin, path);
                if (path.empty()) {
                    std::cout << "Path cannot be empty.\n";
                    break;
                }
                editor.newFile(path);
                std::cout << "New file created in editor (not saved yet).\n";
                break;
            }
            case 2: {
                std::string path, err;
                std::cout << "Enter existing file path: ";
                std::getline(std::cin, path);
                if (editor.loadFromFile(path, err)) {
                    std::cout << "File loaded successfully.\n";
                } else {
                    std::cout << "Error: " << err << "\n";
                }
                break;
            }
            case 3: {
                editor.display();
                break;
            }
            case 4: {
                std::cout << "Enter text to append (end with a single line containing only '::end'):\n";
                std::string line;
                std::string block;
                while (true) {
                    if (!std::getline(std::cin, line)) break;
                    if (line == "::end") break;
                    block += line;
                    block += '\n';
                }
                editor.appendText(block);
                std::cout << "Text appended.\n";
                break;
            }
            case 5: {
                std::string fromWord, toWord;
                std::cout << "Find: ";
                std::getline(std::cin, fromWord);
                std::cout << "Replace with: ";
                std::getline(std::cin, toWord);
                std::size_t replaced = editor.searchAndReplace(fromWord, toWord);
                std::cout << "Replaced " << replaced << " occurrence(s).\n";
                break;
            }
            case 6: {
                std::string err;
                if (editor.saveToFile(err)) {
                    std::cout << "Saved to: " << editor.getFilePath() << "\n";
                } else {
                    std::cout << "Error: " << err << "\n";
                }
                break;
            }
            case 7: {
                if (editor.undo()) {
                    std::cout << "Undo successful.\n";
                } else {
                    std::cout << "Nothing to undo.\n";
                }
                break;
            }
            case 8: {
                if (editor.redo()) {
                    std::cout << "Redo successful.\n";
                } else {
                    std::cout << "Nothing to redo.\n";
                }
                break;
            }
            case 9: {
                std::cout << "Current file: " << (editor.getFilePath().empty() ? "<unsaved>" : editor.getFilePath()) << "\n";
                break;
            }
            case 0: {
                running = false;
                break;
            }
            default:
                std::cout << "Unknown option. Try again.\n";
                break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}


