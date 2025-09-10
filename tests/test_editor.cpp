#include "../include/TextEditor.h"

#include <cassert>
#include <iostream>

static void test_search_and_replace_basic() {
    TextEditor editor;
    editor.newFile("test.txt");
    editor.appendText("hello world\nhello world\n");

    std::size_t replaced = editor.searchAndReplace("world", "TextCraft");
    assert(replaced == 2);
    assert(editor.getContent().find("TextCraft") != std::string::npos);
}

static void test_search_and_replace_no_match() {
    TextEditor editor;
    editor.newFile("test.txt");
    editor.appendText("abc def ghi\n");

    std::size_t replaced = editor.searchAndReplace("xyz", "123");
    assert(replaced == 0);
    assert(editor.getContent() == "abc def ghi\n");
}

static void test_undo_redo_after_replace() {
    TextEditor editor;
    editor.newFile("test.txt");
    editor.appendText("cat dog cat\n");
    std::size_t replaced = editor.searchAndReplace("cat", "fox");
    assert(replaced == 2);
    bool undone = editor.undo();
    assert(undone);
    assert(editor.getContent().find("cat") != std::string::npos);
    bool redone = editor.redo();
    assert(redone);
    assert(editor.getContent().find("fox") != std::string::npos);
}

int main() {
    test_search_and_replace_basic();
    test_search_and_replace_no_match();
    test_undo_redo_after_replace();
    std::cout << "All tests passed.\n";
    return 0;
}


