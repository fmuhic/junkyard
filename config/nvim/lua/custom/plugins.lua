local fn = vim.fn

-- Automatically install packer
local install_path = fn.stdpath "data" .. "/site/pack/packer/start/packer.nvim"
if fn.empty(fn.glob(install_path)) > 0 then
  PACKER_BOOTSTRAP = fn.system {
    "git",
    "clone",
    "--depth",
    "1",
    "https://github.com/wbthomason/packer.nvim",
    install_path,
  }
  print "Installing packer close and reopen Neovim..."
  vim.cmd [[packadd packer.nvim]]
end

-- Autocommand that reloads neovim whenever you save the plugins.lua file
vim.cmd [[
  augroup packer_user_config
    autocmd!
    autocmd BufWritePost plugins.lua source <afile> | PackerSync
  augroup end
]]

-- Use a protected call so we don't error out on first use
local status_ok, packer = pcall(require, "packer")
if not status_ok then
  return
end

-- Have packer use a popup window
packer.init {
  display = {
    open_fn = function()
      return require("packer.util").float { border = "rounded" }
    end,
  },
}

-- Install your plugins here
return packer.startup(function(use)
  -- My plugins here
  use "wbthomason/packer.nvim" -- Have packer manage itself
  use "nvim-lua/popup.nvim" -- An implementation of the Popup API from vim in Neovim
  use "nvim-lua/plenary.nvim" -- Useful lua functions used ny lots of plugins
  use "windwp/nvim-autopairs" -- Autopairs, integrates with both cmp and treesitter

  -- File tree
  use 'kyazdani42/nvim-web-devicons'
  use 'kyazdani42/nvim-tree.lua'

  -- Colorschemes
  use 'folke/tokyonight.nvim'

  -- Dashboard
  use {
    'glepnir/dashboard-nvim',
    event = 'VimEnter',
    config = require('custom.dashboard_config').setup,
    requires = {'nvim-tree/nvim-web-devicons'}
  }

  -- Status line
  use {
    'nvim-lualine/lualine.nvim',
    requires = { 'kyazdani42/nvim-web-devicons', opt = true }
  }

  -- Comment
  use "numToStr/Comment.nvim" -- Easily comment stuff
  use 'JoosepAlviste/nvim-ts-context-commentstring'

  -- Markdown
  use({
    "iamcco/markdown-preview.nvim",
    run = function()
        vim.fn["mkdp#util#install"]()
    end,
  })
  use({
    "iamcco/markdown-preview.nvim",
    run = "cd app && npm install",
    setup = function()
        vim.g.mkdp_filetypes = { "markdown" }
    end,
    ft = { "markdown" },
  })

  -- Todo
  use {
    "nvim-neorg/neorg",
        config = function()
            require('neorg').setup {
                load = {
                    ["core.defaults"] = {},
                    ["core.concealer"] = {},
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
                    ["core.dirman"] = {
                        config = {
                            workspaces = {
                                notes = "~/notes/notes",
                                work = "~/notes/work",
                            },
                        },
                    },
                },
            }
        end,
        run = ":Neorg sync-parsers",
        requires = "nvim-lua/plenary.nvim",
    }

  -- Completion plugins
  use "hrsh7th/nvim-cmp" -- The completion plugin
  use "hrsh7th/cmp-buffer" -- buffer completions
  use "hrsh7th/cmp-path" -- path completions
  use "hrsh7th/cmp-cmdline" -- cmdline completions
  use "saadparwaiz1/cmp_luasnip" -- snippet completions
  use "hrsh7th/cmp-nvim-lsp" -- lsp completion
  use "hrsh7th/cmp-nvim-lua" -- neovim lua API completion

  -- Snippets
  use "L3MON4D3/LuaSnip" --snippet engine
  use "rafamadriz/friendly-snippets" -- a bunch of snippets to use

  -- LSP
  use {
    "williamboman/mason.nvim",
    "williamboman/mason-lspconfig.nvim",
    "neovim/nvim-lspconfig",
    "simrat39/rust-tools.nvim"
  }

  -- Telescope and extensions
  use "nvim-telescope/telescope.nvim"
  use "nvim-telescope/telescope-project.nvim"

  -- Treesitter
  use {
    "nvim-treesitter/nvim-treesitter",
    run = ":TSUpdate",
  }

  -- Git
  use "lewis6991/gitsigns.nvim"

  -- Automatically set up your configuration after cloning packer.nvim
  -- Put this at the end after all plugins
  if PACKER_BOOTSTRAP then
    require("packer").sync()
  end
end)
