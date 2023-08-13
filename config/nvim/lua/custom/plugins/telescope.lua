return {
  'nvim-telescope/telescope.nvim',
  dependencies = {
    'nvim-lua/plenary.nvim',
    'nvim-telescope/telescope-project.nvim'
  },
  config = function()
    local telescope = require("telescope")
    local actions = require("telescope.actions")

    telescope.setup {
      defaults = {
        prompt_prefix = " ",
        selection_caret = " ",
        path_display = { "smart" },
        mappings = {
          i = {
            ["<C-n>"] = actions.cycle_history_next,
            ["<C-p>"] = actions.cycle_history_prev,
            ["<C-j>"] = actions.move_selection_next,
            ["<C-k>"] = actions.move_selection_previous,
            ["<C-c>"] = actions.close,
            ["<Down>"] = actions.move_selection_next,
            ["<Up>"] = actions.move_selection_previous,
            ["<CR>"] = actions.select_default,
            ["<C-t>"] = actions.select_tab,
            ["<C-u>"] = actions.preview_scrolling_up,
            ["<C-d>"] = actions.preview_scrolling_down,
            ["<PageUp>"] = actions.results_scrolling_up,
            ["<PageDown>"] = actions.results_scrolling_down,
            ["<Tab>"] = actions.toggle_selection + actions.move_selection_worse,
            ["<S-Tab>"] = actions.toggle_selection + actions.move_selection_better,
            ["<C-q>"] = actions.send_to_qflist + actions.open_qflist,
            ["<M-q>"] = actions.send_selected_to_qflist + actions.open_qflist,
            ["<C-l>"] = actions.complete_tag,
            ["<C-_>"] = actions.which_key,
          },
          n = {
            ["<esc>"] = actions.close,
            ["<CR>"] = actions.select_default,
            ["<C-t>"] = actions.select_tab,
            ["<Tab>"] = actions.toggle_selection + actions.move_selection_worse,
            ["<S-Tab>"] = actions.toggle_selection + actions.move_selection_better,
            ["<C-q>"] = actions.send_to_qflist + actions.open_qflist,
            ["<M-q>"] = actions.send_selected_to_qflist + actions.open_qflist,
            ["j"] = actions.move_selection_next,
            ["k"] = actions.move_selection_previous,
            ["H"] = actions.move_to_top,
            ["M"] = actions.move_to_middle,
            ["L"] = actions.move_to_bottom,
            ["<Down>"] = actions.move_selection_next,
            ["<Up>"] = actions.move_selection_previous,
            ["gg"] = actions.move_to_top,
            ["G"] = actions.move_to_bottom,
            ["<C-u>"] = actions.preview_scrolling_up,
            ["<C-d>"] = actions.preview_scrolling_down,
            ["<PageUp>"] = actions.results_scrolling_up,
            ["<PageDown>"] = actions.results_scrolling_down,
            ["?"] = actions.which_key,
          },
        },
      },
      pickers = {},
      extensions = {
        media_files = {
          filetypes = {"png", "webp", "jpg", "jpeg"},
          find_cmd = "rg"
        },
        project = {
          base_dirs = {
            "~/code",
            "~/code/junkyard/",
          },
          hidden_files = true,
          theme = "dropdown",
          order_by = "asc",
          search_by = "title",
          sync_with_nvim_tree = true,
        }
      },
    }
  end,
  keys = {
    {
      "<Space>b",
      function()
        require("telescope.builtin").lsp_references()
      end,
      desc = "Find references",
    },
    {
      "<Space>n",
      function()
        require("telescope.builtin").lsp_definitions()
      end,
      desc = "Find definitions",
    },
    {
      "<Space>o",
      function()
        require("telescope.builtin").live_grep()
      end,
      desc = "Find words",
    },
    {
      "<Space>p",
      function()
        require("telescope.builtin")
          .find_files(require('telescope.themes')
          .get_dropdown({ previewer = false }))
      end,
      desc = "Find files",
    },
    {
      "<Space>p",
      function()
        require("telescope.builtin")
          .find_files(require('telescope.themes')
          .get_dropdown({ previewer = false }))
      end,
      desc = "Find files",
    },
    {
      "<Space>q",
      function()
        require("telescope").extensions.project.project{}
      end,
      desc = "Select project",
    },
    {
      "<Leader>d",
      function()
        vim.diagnostic.open_float({ border = 'rounded' })
      end,
      desc = "Select project",
    },
    {
      "<Leader>D",
      function()
        require("telescope.builtin")
          .diagnostics(require('telescope.themes')
          .get_dropdown())
      end,
      desc = "Select project",
    },
  }
}
