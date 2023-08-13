return {
  "nvim-neorg/neorg",
  build = ":Neorg sync-parsers",
  after = "nvim-treesitter",
  dependencies = { "nvim-lua/plenary.nvim" },
  config = function()
    require("neorg").setup {
      load = {
        ["core.defaults"] = {}, -- Loads default behaviour
        ["core.concealer"] = {}, -- Adds pretty icons to your documents
        ["core.keybinds"] = {
          config = {
            hook = function(keybinds)
              keybinds.remap_event("norg", "n", "md", "core.qol.todo_items.todo.task_done")
              keybinds.remap_event("norg", "n", "mu", "core.qol.todo_items.todo.task_undone")
              keybinds.remap_event("norg", "n", "mp", "core.qol.todo_items.todo.task_pending")
              keybinds.remap_event("norg", "n", "mn", "core.dirman.new.note")
            end,
          }
        },
        ["core.dirman"] = { -- Manages Neorg workspaces
          config = {
            workspaces = {
              notes = "~/notes/notes",
              work = "~/notes/work"
            },
          },
        },
      }
    }
  end,
}
