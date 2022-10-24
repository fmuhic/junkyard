local utils = require "custom.utils"

local keymap = utils.keymap
local opts = { noremap = true, silent = true }
local opts_visible = { noremap = true, silent = false }
local term_opts = { silent = true }


-- Set space as leader key
keymap("", "<Space>", "<Nop>", opts)
vim.g.mapleader = " "
vim.g.maplocalleader = " "


--------------------------------------
--------------- Normal ---------------
--------------------------------------

-- Move backward a word
keymap({"n", "v", "x"}, "q", "b", opts)
keymap({"n", "v", "x"}, "Q", "B", opts)


-- Move to first character in line
keymap({"n", "v", "x"}, "H", "0", opts)

-- Move to last character in line
keymap({"n", "v", "x"}, "L", "$", opts)

-- Recording remap
keymap("n", "<leader>q", "q", opts)

-- Clear highlight after search
keymap("n", "<leader>n", ":noh<CR>", opts)

-- Quick save
keymap("n", "<leader>w", ":w!<CR>", opts_visible)

-- Scroll navigation
keymap("n", "<S-k>", "5<C-y>", opts)
keymap("n", "<S-j>", "5<C-e>", opts)

-- Split window navigation
keymap("n", "<C-h>", "<C-w>h", opts)
keymap("n", "<C-j>", "<C-w>j", opts)
keymap("n", "<C-k>", "<C-w>k", opts)
keymap("n", "<C-l>", "<C-w>l", opts)

keymap("n", "<leader>e", ":Lex 30<cr>", opts)

-- Resize with arrows
keymap("n", "<C-Up>", ":resize +2<CR>", opts)
keymap("n", "<C-Down>", ":resize -2<CR>", opts)
keymap("n", "<C-Left>", ":vertical resize -2<CR>", opts)
keymap("n", "<C-Right>", ":vertical resize +2<CR>", opts)

-- Insert empty line without changing mode
keymap("n", "<Enter>", "o<Esc>k", opts)
keymap("n", "<S-Enter>", "O<Esc>j", opts)

-- Navigate buffers
--keymap("n", "<C-e>", ":bnext<CR>", opts)
--keymap("n", "<C-q>", ":bprevious<CR>", opts)





--------------------------------------
--------------- Insert ---------------
--------------------------------------

-- Exit insert mode
keymap("i", "jk", "<ESC>", opts)
keymap("i", "Jk", "<ESC>", opts)
keymap("i", "JK", "<ESC>", opts)





--------------------------------------
--------------- Visual --------------- 
--------------------------------------

-- Exit visaul modes
keymap({"v", "x"}, "<leader>jk", "<ESC>", opts)
keymap({"v", "x"}, "<leader>Jk", "<ESC>", opts)
keymap({"v", "x"}, "<leader>JK", "<ESC>", opts)

-- Indent with tab
keymap("v", "<TAB>", ">gv", opts)
keymap("v", "<S-TAB>", "<gv", opts)

-- Stay in indent mode
keymap("v", "<", "<gv", opts)
keymap("v", ">", ">gv", opts)

-- Hold the yank
keymap("v", "p", '"_dP', opts)





--------------------------------------
------------ Visual Block ------------
--------------------------------------

-- Move text up and down
keymap("x", "J", ":move '>+1<CR>gv-gv", opts)
keymap("x", "K", ":move '<-2<CR>gv-gv", opts)
keymap("x", "<A-j>", ":move '>+1<CR>gv-gv", opts)
keymap("x", "<A-k>", ":move '<-2<CR>gv-gv", opts)





--------------------------------------
-------------- Terminal --------------
--------------------------------------

-- Better terminal navigation
keymap("t", "<C-h>", "<C-\\><C-N><C-w>h", term_opts)
keymap("t", "<C-j>", "<C-\\><C-N><C-w>j", term_opts)
keymap("t", "<C-k>", "<C-\\><C-N><C-w>k", term_opts)
keymap("t", "<C-l>", "<C-\\><C-N><C-w>l", term_opts)





--------------------------------------
--------------- Plugin ---------------
--------------------------------------

-- Telescope fuzzy bindings
local telescope = require('telescope.builtin')

vim.keymap.set('n', '<A-j>', telescope.lsp_definitions, opts)
vim.keymap.set('n', '<A-k>', telescope.lsp_references, opts)
vim.keymap.set("n", "<A-o>", telescope.live_grep, opts)
keymap("n", "<A-p>", "<cmd>lua require'telescope.builtin'.find_files(require('telescope.themes').get_dropdown({ previewer = false }))<cr>", opts)
keymap("n", "<C-d>", "<cmd>lua require'telescope.builtin'.diagnostics(require('telescope.themes').get_dropdown())<CR>", opts)
keymap("n", "<leader>d", "<cmd>lua vim.diagnostic.open_float({ border = 'rounded' })<CR>", opts)

-- Nvimtree
keymap("n", ";", ":NvimTreeToggle<CR>", opts)
