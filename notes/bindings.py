from textual.binding import Binding

BINDINGS = [
    # --- App & Navigation ---
    Binding("q", "quit", "Quit", priority=True),
    Binding("d", "toggle_dark", "Toggle Theme"),
    Binding("question_mark", "help", "Help", key_display="?"),
    # --- Note Management ---
    Binding("n", "new_note", "New Note"),
    Binding("ctrl+s", "save_note", "Save"),
    Binding("ctrl+d", "delete_note", "Delete"),
    Binding("r", "rename_note", "Rename"),
    # --- Search & Filter ---
    Binding("slash", "search", "Search", key_display="/"),
    # --- View & Focus Modes ---
    Binding("ctrl+b", "toggle_sidebar", "Sidebar"),
    Binding("p", "toggle_preview", "Preview"),
    Binding("escape", "clear_focus", "Back/Escape", show=False),
    # --- Navigation Between Notes ---
    Binding("j", "cursor_down", "Down", show=False),
    Binding("k", "cursor_up", "Up", show=False),
]
