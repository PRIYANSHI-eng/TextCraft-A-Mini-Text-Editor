#include "TextEditor.h"

#include <iostream>
#include <fstream>
#include <sstream>

TextEditor::TextEditor() : filePath_(), content_() {}

bool TextEditor::newFile(const std::string &filePath) {
    filePath_ = filePath;
    content_.clear();
    while (!undoStack_.empty()) undoStack_.pop();
    while (!redoStack_.empty()) redoStack_.pop();
    return true;
}

bool TextEditor::loadFromFile(const std::string &filePath, std::string &errorMessage) {
    std::ifstream in(filePath.c_str());
    if (!in) {
        errorMessage = "Unable to open file: " + filePath;
        return false;
    }

    std::ostringstream buffer;
    buffer << in.rdbuf();
    if (in.bad()) {
        errorMessage = "Error reading file: " + filePath;
        return false;
    }

    filePath_ = filePath;
    content_ = buffer.str();

    while (!undoStack_.empty()) undoStack_.pop();
    while (!redoStack_.empty()) redoStack_.pop();

    return true;
}

bool TextEditor::saveToFile(std::string &errorMessage) const {
    if (filePath_.empty()) {
        errorMessage = "No file path set. Create or load a file first.";
        return false;
    }

    std::ofstream out(filePath_.c_str());
    if (!out) {
        errorMessage = "Unable to open file for writing: " + filePath_;
        return false;
    }
    out << content_;
    if (!out.good()) {
        errorMessage = "Error writing to file: " + filePath_;
        return false;
    }
    return true;
}

void TextEditor::display() const {
    if (content_.empty()) {
        std::cout << "[Empty file]\n";
    } else {
        std::cout << content_;
        if (content_.size() == 0 || content_.back() != '\n') {
            std::cout << '\n';
        }
    }
}

void TextEditor::appendText(const std::string &textToAppend) {
    saveStateForUndo();
    content_ += textToAppend;
    clearRedoHistory();
}

std::size_t TextEditor::searchAndReplace(const std::string &fromWord, const std::string &toWord) {
    if (fromWord.empty()) return 0;

    saveStateForUndo();

    std::size_t count = 0;
    std::string result;
    result.reserve(content_.size());

    std::size_t pos = 0;
    while (true) {
        std::size_t found = content_.find(fromWord, pos);
        if (found == std::string::npos) {
            result.append(content_.substr(pos));
            break;
        }
        result.append(content_, pos, found - pos);
        result.append(toWord);
        pos = found + fromWord.size();
        ++count;
    }

    content_.swap(result);
    clearRedoHistory();
    return count;
}

bool TextEditor::undo() {
    if (undoStack_.empty()) return false;
    redoStack_.push(content_);
    content_ = undoStack_.top();
    undoStack_.pop();
    return true;
}

bool TextEditor::redo() {
    if (redoStack_.empty()) return false;
    undoStack_.push(content_);
    content_ = redoStack_.top();
    redoStack_.pop();
    return true;
}

bool TextEditor::hasUndo() const { return !undoStack_.empty(); }
bool TextEditor::hasRedo() const { return !redoStack_.empty(); }

const std::string &TextEditor::getFilePath() const { return filePath_; }
const std::string &TextEditor::getContent() const { return content_; }

void TextEditor::saveStateForUndo() {
    undoStack_.push(content_);
}

void TextEditor::clearRedoHistory() {
    while (!redoStack_.empty()) redoStack_.pop();
}


