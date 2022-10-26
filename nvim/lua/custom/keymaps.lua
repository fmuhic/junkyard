local utils = require "custom.utils"

local keymap = utils.keymap
local opts = { noremap = true, silent = true }
local opts_visible = { noremap = true, silent = false }
local term_opts = { silent = true }


-- Set space as leader key
keymap("", ",", "<Nop>", opts)
vim.g.mapleader = ","
vim.g.maplocalleader = ","


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
keymap("n", "<leader>n", ":noh<Cr>", opts)

-- Quick save
keymap("n", "<leader>w", ":w!<Cr>", opts_visible)

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
keymap("n", "<C-Up>", ":resize +2<Cr>", opts)
keymap("n", "<C-Down>", ":resize -2<Cr>", opts)
keymap("n", "<C-Left>", ":vertical resize -2<Cr>", opts)
keymap("n", "<C-Right>", ":vertical resize +2<Cr>", opts)

-- Insert empty line without changing mode
keymap("n", "<Enter>", "o<Esc>k", opts)
keymap("n", "<S-Enter>", "O<Esc>j", opts)

-- Navigate buffers
keymap("n", "<A-n>", ":bprevious<Cr>", opts)
keymap("n", "<A-m>", ":bnext<Cr>", opts)





--------------------------------------
--------------- Insert ---------------
--------------------------------------

-- Exit insert mode
keymap("i", "jk", "<Esc>", opts)
keymap("i", "Jk", "<Esc>", opts)
keymap("i", "JK", "<Esc>", opts)





--------------------------------------
--------------- Visual --------------- 
--------------------------------------

-- Exit visaul modes
keymap({"v", "x"}, "<leader>jk", "<Esc>", opts)
keymap({"v", "x"}, "<leader>Jk", "<Esc>", opts)
keymap({"v", "x"}, "<leader>JK", "<Esc>", opts)

-- Indent one space with <Space>
keymap({"v", "x"}, "<Space>", ":s/^/ /<Cr>:noh<Cr>gv", opts)

-- Indent one tab with tab
keymap("v", "<Tab>", ">gv", opts)
keymap("v", "<S-Tab>", "<gv", opts)

-- Stay in indent mode
keymap("v", "<", "<gv", opts)
keymap("v", ">", ">gv", opts)

-- Hold the yank
keymap("v", "p", '"_dP', opts)





--------------------------------------
------------ Visual Block ------------
--------------------------------------

-- Move text up and down
keymap("x", "J", ":move '>+1<Cr>gv-gv", opts)
keymap("x", "K", ":move '<-2<Cr>gv-gv", opts)
keymap("x", "<A-j>", ":move '>+1<Cr>gv-gv", opts)
keymap("x", "<A-k>", ":move '<-2<Cr>gv-gv", opts)





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
keymap("n", "<A-p>", "<Cmd>lua require'telescope.builtin'.find_files(require('telescope.themes').get_dropdown({ previewer = false }))<Cr>", opts)
keymap("n", "<C-d>", "<Cmd>lua require'telescope.builtin'.diagnostics(require('telescope.themes').get_dropdown())<Cr>", opts)
keymap("n", "<leader>d", "<cmd>lua vim.diagnostic.open_float({ border = 'rounded' })<Cr>", opts)

-- Nvimtree
keymap("n", ";", ":NvimTreeToggle<Cr>", opts)

-- Test
