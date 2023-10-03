return {
  "nvim-tree/nvim-tree.lua",
  opts = {
    disable_netrw = true,
    hijack_netrw = true,
    open_on_tab = false,
    hijack_cursor = false,
    update_cwd = true,
    hijack_directories = {
      enable = true,
      auto_open = true,
    },
    diagnostics = {
      enable = true,
      icons = {
        hint = "",
        info = "",
        warning = "",
        error = "",
      },
    },
    update_focused_file = {
      enable = true,
      update_cwd = true,
      ignore_list = {},
    },
    git = {
      enable = false,
      ignore = true,
      timeout = 500,
    },
    view = {
      width = 30,
      side = "left",
      number = false,
      relativenumber = false,
    },
    actions = {
      open_file = {
        quit_on_open = true,
        resize_window = true,
        window_picker = {
          enable = false
        }
      }
    },
    renderer = {
      highlight_git = true,
      root_folder_modifier = ":t",
      icons = {
        show = {
          file = true,
          folder = true,
          folder_arrow = true,
          git = true,
        },
        glyphs = {
          default = "",
          symlink = "",
          git = {
            unstaged = "",
            staged = "S",
            unmerged = "",
            renamed = "➜",
            deleted = "",
            untracked = "U",
            ignored = "◌",
          },
          folder = {
            default = "",
            open = "",
            empty = "",
            empty_open = "",
            symlink = "",
          },
        }
      }
    }
  },
  keys = {
    { ";", "<cmd>NvimTreeToggle<CR>", desc = "Toggle file browser" }
  }
}
