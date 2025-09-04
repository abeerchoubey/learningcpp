//MADE BY ABEER CHOUBEY
//REMEMBER TO DOWNLOAD NCURSES BEFORE RUNNING

#include <ncurses.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <filesystem>
#include <sstream>

class TUIApp {
private:
    int current_selection;
    int max_selection;
    std::vector<std::string> menu_items;
    bool running;
    int mouse_x, mouse_y;
    
    // File operations
    std::string current_file;
    std::vector<std::string> file_content;
    std::vector<std::string> file_list;
    bool in_file_mode;
    bool in_edit_mode;
    int edit_cursor_x, edit_cursor_y;
    int edit_scroll_y;
    
public:
    TUIApp() : current_selection(0), max_selection(0), running(true), mouse_x(0), mouse_y(0),
               current_file(""), in_file_mode(false), in_edit_mode(false), 
               edit_cursor_x(0), edit_cursor_y(0), edit_scroll_y(0) {
        // Initialize menu items
        menu_items = {
            "Create New File",
            "Open File", 
            "Edit File",
            "Save File",
            "List Files",
            "Exit"
        };
        max_selection = menu_items.size() - 1;
        refresh_file_list();
    }
    
    void init_ncurses() {
        // Initialize ncurses
        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);
        curs_set(0); // Hide cursor
        
        // Enable mouse support
        mousemask(ALL_MOUSE_EVENTS, NULL);
        
        // Enable colors if available
        if (has_colors()) {
            start_color();
            init_pair(1, COLOR_WHITE, COLOR_BLUE);   // Selected item
            init_pair(2, COLOR_BLACK, COLOR_WHITE);  // Normal item
            init_pair(3, COLOR_RED, COLOR_BLACK);    // Title
            init_pair(4, COLOR_GREEN, COLOR_BLACK);  // Instructions
        }
        
        // Get screen dimensions
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        // Clear screen
        clear();
        refresh();
    }
    
    void cleanup_ncurses() {
        endwin();
    }
    
    void draw_title() {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(2, (max_x - 20) / 2, "TUI Navigation Demo");
        attroff(COLOR_PAIR(3) | A_BOLD);
    }
    
    void draw_menu() {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        int start_y = max_y / 2 - menu_items.size() / 2;
        int start_x = max_x / 2 - 15;
        
        for (int i = 0; i < menu_items.size(); i++) {
            int y = start_y + i;
            
            if (i == current_selection) {
                attron(COLOR_PAIR(1) | A_BOLD);
                mvprintw(y, start_x, "> %s <", menu_items[i].c_str());
                attroff(COLOR_PAIR(1) | A_BOLD);
            } else {
                attron(COLOR_PAIR(2));
                mvprintw(y, start_x, "  %s  ", menu_items[i].c_str());
                attroff(COLOR_PAIR(2));
            }
        }
    }
    
    void draw_instructions() {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        attron(COLOR_PAIR(4));
        mvprintw(max_y - 5, 2, "Navigation:");
        mvprintw(max_y - 4, 2, "  Arrow Keys: Navigate menu");
        mvprintw(max_y - 3, 2, "  Enter: Select item");
        mvprintw(max_y - 2, 2, "  Mouse: Click to select");
        mvprintw(max_y - 1, 2, "  ESC/q: Quit");
        if (!current_file.empty()) {
            mvprintw(max_y, 2, "Current file: %s", current_file.c_str());
        }
        attroff(COLOR_PAIR(4));
    }
    
    void draw_mouse_info() {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        
        attron(COLOR_PAIR(4));
        mvprintw(4, 2, "Mouse Position: (%d, %d)", mouse_x, mouse_y);
        attroff(COLOR_PAIR(4));
    }
    
    void handle_keyboard(int ch) {
        switch (ch) {
            case KEY_UP:
                current_selection = (current_selection > 0) ? current_selection - 1 : max_selection;
                break;
            case KEY_DOWN:
                current_selection = (current_selection < max_selection) ? current_selection + 1 : 0;
                break;
            case '\n':
            case '\r':
                select_item();
                break;
            case 27: // ESC
            case 'q':
            case 'Q':
                running = false;
                break;
        }
    }
    
    void handle_mouse(MEVENT* event) {
        mouse_x = event->x;
        mouse_y = event->y;
        
        if (event->bstate & BUTTON1_CLICKED) {
            // Check if click is on a menu item
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);
            
            int start_y = max_y / 2 - menu_items.size() / 2;
            int start_x = max_x / 2 - 15;
            
            for (int i = 0; i < menu_items.size(); i++) {
                int item_y = start_y + i;
                if (event->y == item_y && event->x >= start_x && event->x < start_x + 30) {
                    current_selection = i;
                    select_item();
                    break;
                }
            }
        }
    }
    
    void select_item() {
        switch (current_selection) {
            case 0: // Create New File
                create_new_file();
                break;
            case 1: // Open File
                open_file_dialog();
                break;
            case 2: // Edit File
                edit_file_dialog();
                break;
            case 3: // Save File
                save_current_file();
                break;
            case 4: // List Files
                list_files();
                break;
            case 5: // Exit
                running = false;
                break;
        }
    }
    
    void refresh_file_list() {
        file_list.clear();
        try {
            for (const auto& entry : std::filesystem::directory_iterator(".")) {
                if (entry.is_regular_file()) {
                    file_list.push_back(entry.path().filename().string());
                }
            }
        } catch (const std::exception& e) {
            // Handle directory access errors
        }
    }
    
    void create_new_file() {
        clear();
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(5, 10, "Create New File");
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        attron(COLOR_PAIR(4));
        mvprintw(7, 10, "Enter filename: ");
        attroff(COLOR_PAIR(4));
        
        echo();
        char filename[256];
        getnstr(filename, 255);
        noecho();
        
        current_file = std::string(filename);
        file_content.clear();
        file_content.push_back(""); // Start with empty line
        
        attron(COLOR_PAIR(2));
        mvprintw(9, 10, "File '%s' created. Press any key to continue.", current_file.c_str());
        attroff(COLOR_PAIR(2));
        
        refresh();
        getch();
    }
    
    void open_file_dialog() {
        if (file_list.empty()) {
            show_message("No files found in current directory.");
            return;
        }
        
        in_file_mode = true;
        int file_selection = 0;
        
        while (in_file_mode) {
            clear();
            draw_title();
            
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(5, 10, "Select File to Open");
            attroff(COLOR_PAIR(3) | A_BOLD);
            
            int start_y = 8;
            for (int i = 0; i < file_list.size() && i < 10; i++) {
                int y = start_y + i;
                if (i == file_selection) {
                    attron(COLOR_PAIR(1) | A_BOLD);
                    mvprintw(y, 10, "> %s <", file_list[i].c_str());
                    attroff(COLOR_PAIR(1) | A_BOLD);
                } else {
                    attron(COLOR_PAIR(2));
                    mvprintw(y, 10, "  %s  ", file_list[i].c_str());
                    attroff(COLOR_PAIR(2));
                }
            }
            
            attron(COLOR_PAIR(4));
            mvprintw(start_y + 12, 10, "Arrow Keys: Navigate, Enter: Select, ESC: Cancel");
            attroff(COLOR_PAIR(4));
            
            refresh();
            
            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    file_selection = (file_selection > 0) ? file_selection - 1 : file_list.size() - 1;
                    break;
                case KEY_DOWN:
                    file_selection = (file_selection < file_list.size() - 1) ? file_selection + 1 : 0;
                    break;
                case '\n':
                case '\r':
                    open_file(file_list[file_selection]);
                    in_file_mode = false;
                    break;
                case 27: // ESC
                    in_file_mode = false;
                    break;
            }
        }
    }
    
    void open_file(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            show_message("Error: Could not open file '" + filename + "'");
            return;
        }
        
        current_file = filename;
        file_content.clear();
        std::string line;
        
        while (std::getline(file, line)) {
            file_content.push_back(line);
        }
        file.close();
        
        if (file_content.empty()) {
            file_content.push_back("");
        }
        
        show_message("File '" + filename + "' opened successfully.");
    }
    
    void edit_file_dialog() {
        if (current_file.empty()) {
            show_message("No file is currently open. Please open a file first.");
            return;
        }
        
        in_edit_mode = true;
        edit_cursor_x = 0;
        edit_cursor_y = 0;
        edit_scroll_y = 0;
        
        while (in_edit_mode) {
            clear();
            draw_title();
            
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(2, 2, "Editing: %s", current_file.c_str());
            attroff(COLOR_PAIR(3) | A_BOLD);
            
            // Display file content
            int max_y, max_x;
            getmaxyx(stdscr, max_y, max_x);
            int content_start_y = 4;
            int content_end_y = max_y - 3;
            
            for (int i = 0; i < file_content.size() && (i + content_start_y) < content_end_y; i++) {
                int display_y = content_start_y + i;
                if (display_y >= content_start_y && display_y < content_end_y) {
                    std::string line = file_content[i + edit_scroll_y];
                    if (line.length() > max_x - 4) {
                        line = line.substr(0, max_x - 4);
                    }
                    
                    if (i + edit_scroll_y == edit_cursor_y) {
                        attron(COLOR_PAIR(1));
                        mvprintw(display_y, 2, "%s", line.c_str());
                        attroff(COLOR_PAIR(1));
                        
                        // Show cursor
                        if (edit_cursor_x < line.length()) {
                            mvprintw(display_y, 2 + edit_cursor_x, "_");
                        }
                    } else {
                        attron(COLOR_PAIR(2));
                        mvprintw(display_y, 2, "%s", line.c_str());
                        attroff(COLOR_PAIR(2));
                    }
                }
            }
            
            attron(COLOR_PAIR(4));
            mvprintw(max_y - 2, 2, "Arrow Keys: Navigate, Enter: New Line, Backspace: Delete, Ctrl+S: Save, ESC: Exit Edit");
            attroff(COLOR_PAIR(4));
            
            refresh();
            
            int ch = getch();
            handle_edit_input(ch);
        }
    }
    
    void handle_edit_input(int ch) {
        switch (ch) {
            case KEY_UP:
                if (edit_cursor_y > 0) {
                    edit_cursor_y--;
                    if (edit_cursor_y < edit_scroll_y) {
                        edit_scroll_y = edit_cursor_y;
                    }
                    edit_cursor_x = std::min(edit_cursor_x, (int)file_content[edit_cursor_y].length());
                }
                break;
            case KEY_DOWN:
                if (edit_cursor_y < file_content.size() - 1) {
                    edit_cursor_y++;
                    int max_y, max_x;
                    getmaxyx(stdscr, max_y, max_x);
                    if (edit_cursor_y >= edit_scroll_y + max_y - 7) {
                        edit_scroll_y = edit_cursor_y - max_y + 8;
                    }
                    edit_cursor_x = std::min(edit_cursor_x, (int)file_content[edit_cursor_y].length());
                }
                break;
            case KEY_LEFT:
                if (edit_cursor_x > 0) {
                    edit_cursor_x--;
                }
                break;
            case KEY_RIGHT:
                if (edit_cursor_x < file_content[edit_cursor_y].length()) {
                    edit_cursor_x++;
                }
                break;
            case '\n':
            case '\r':
                // Insert new line
                {
                    std::string current_line = file_content[edit_cursor_y];
                    std::string new_line = current_line.substr(edit_cursor_x);
                    file_content[edit_cursor_y] = current_line.substr(0, edit_cursor_x);
                    file_content.insert(file_content.begin() + edit_cursor_y + 1, new_line);
                    edit_cursor_y++;
                    edit_cursor_x = 0;
                }
                break;
            case 127: // Backspace
            case KEY_BACKSPACE:
                if (edit_cursor_x > 0) {
                    file_content[edit_cursor_y].erase(edit_cursor_x - 1, 1);
                    edit_cursor_x--;
                } else if (edit_cursor_y > 0) {
                    // Merge with previous line
                    edit_cursor_x = file_content[edit_cursor_y - 1].length();
                    file_content[edit_cursor_y - 1] += file_content[edit_cursor_y];
                    file_content.erase(file_content.begin() + edit_cursor_y);
                    edit_cursor_y--;
                }
                break;
            case 19: // Ctrl+S
                save_current_file();
                break;
            case 27: // ESC
                in_edit_mode = false;
                break;
            default:
                if (ch >= 32 && ch <= 126) { // Printable characters
                    file_content[edit_cursor_y].insert(edit_cursor_x, 1, ch);
                    edit_cursor_x++;
                }
                break;
        }
    }
    
    void save_current_file() {
        if (current_file.empty()) {
            show_message("No file is currently open to save.");
            return;
        }
        
        std::ofstream file(current_file);
        if (!file.is_open()) {
            show_message("Error: Could not save file '" + current_file + "'");
            return;
        }
        
        for (const auto& line : file_content) {
            file << line << std::endl;
        }
        file.close();
        
        show_message("File '" + current_file + "' saved successfully.");
    }
    
    void list_files() {
        refresh_file_list();
        
        clear();
        draw_title();
        
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(5, 10, "Files in Current Directory");
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        if (file_list.empty()) {
            attron(COLOR_PAIR(2));
            mvprintw(7, 10, "No files found.");
            attroff(COLOR_PAIR(2));
        } else {
            for (int i = 0; i < file_list.size() && i < 15; i++) {
                attron(COLOR_PAIR(2));
                mvprintw(7 + i, 10, "%s", file_list[i].c_str());
                attroff(COLOR_PAIR(2));
            }
        }
        
        attron(COLOR_PAIR(4));
        mvprintw(25, 10, "Press any key to continue...");
        attroff(COLOR_PAIR(4));
        
        refresh();
        getch();
    }
    
    void show_message(const std::string& message) {
        clear();
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(10, 10, "%s", message.c_str());
        attroff(COLOR_PAIR(3) | A_BOLD);
        
        attron(COLOR_PAIR(4));
        mvprintw(12, 10, "Press any key to continue...");
        attroff(COLOR_PAIR(4));
        
        refresh();
        getch();
    }
    
    void run() {
        init_ncurses();
        
        while (running) {
            clear();
            
            draw_title();
            draw_menu();
            draw_instructions();
            draw_mouse_info();
            
            refresh();
            
            int ch = getch();
            
            if (ch == KEY_MOUSE) {
                MEVENT event;
                if (getmouse(&event) == OK) {
                    handle_mouse(&event);
                }
            } else {
                handle_keyboard(ch);
            }
        }
        
        cleanup_ncurses();
    }
};

int main() {
    TUIApp app;
    app.run();
    return 0;
}
