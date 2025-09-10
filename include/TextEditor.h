// TextCraft – A Mini Text Editor in C++
// Declaration of the TextEditor class (header)
// Uses only the C++ standard library. Cross-platform.

#pragma once

#include <string>
#include <stack>

class TextEditor {
public:
    TextEditor();

    // File operations
    bool newFile(const std::string &filePath);
    bool loadFromFile(const std::string &filePath, std::string &errorMessage);
    bool saveToFile(std::string &errorMessage) const;

    // Display current content to stdout
    void display() const;

    // Editing operations
    void appendText(const std::string &textToAppend);
    // Replaces all occurrences of 'fromWord' with 'toWord'. Returns count replaced
    std::size_t searchAndReplace(const std::string &fromWord, const std::string &toWord);

    // Undo/Redo
    bool undo();
    bool redo();
    bool hasUndo() const;
    bool hasRedo() const;

    // Utilities
    const std::string &getFilePath() const;
    const std::string &getContent() const; // Exposed for testing purposes

private:
    std::string filePath_;
    std::string content_;

    // History stacks store previous and future states of content
    std::stack<std::string> undoStack_;
    std::stack<std::string> redoStack_;

    // Push current state to undo stack before any mutating change
    void saveStateForUndo();
    // Clear redo history when a new change is made
    void clearRedoHistory();
};


