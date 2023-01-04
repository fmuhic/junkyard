local utils = require "custom.utils"

local keymap = utils.keymap
local opts = { noremap = true, silent = true }
local opts_visible = { noremap = true, silent = false }
local term_opts = { silent = true }


-- Set leader key
keymap("", ",", "<Nop>", opts)
vim.g.mapleader = ","
vim.g.maplocalleader = ","


--------------------------------------
--------------- Normal ---------------
--------------------------------------

-- Remove mappings from space
keymap("n", "<space>", "<Nop>", opts)

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
keymap({"n", "v", "x"}, "<S-k>", "5<C-y>", opts)
keymap({"n", "v", "x"}, "<S-j>", "5<C-e>", opts)

-- Split window navigation
keymap("n", "<Space>h", "<C-w>h", opts)
keymap("n", "<Space>j", "<C-w>j", opts)
keymap("n", "<Space>k", "<C-w>k", opts)
keymap("n", "<Space>l", "<C-w>l", opts)

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
keymap("n", "<Space>m", ":bprevious<Cr>", opts)
keymap("n", "<Space>,", ":bnext<Cr>", opts)





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

-- Copy to clipboard
keymap("v", "<leader>y", "\"+y", opts)
keymap("v", "<leader>Y", "\"+yg_", opts)
keymap("v", "<leader>yy", "\"+yy", opts)

-- Paste from clipboard
keymap("v", "<leader>p", "\"+p", opts)
keymap("v", "<leader>P", "\"+P", opts)





--------------------------------------
------------ Visual Block ------------
--------------------------------------

-- Move text up and down
--keymap("x", "J", ":move '>+1<Cr>gv-gv", opts)
--keymap("x", "K", ":move '<-2<Cr>gv-gv", opts)
keymap("x", "<A-j>", ":move '>+1<Cr>gv-gv", opts)
keymap("x", "<A-k>", ":move '<-2<Cr>gv-gv", opts)





--------------------------------------
-------------- Terminal --------------
--------------------------------------

-- Better terminal navigation
keymap("t", "<C-h>h", "<C-\\><C-N><C-w>h", term_opts)
keymap("t", "<C-j>j", "<C-\\><C-N><C-w>j", term_opts)
keymap("t", "<C-k>k", "<C-\\><C-N><C-w>k", term_opts)
keymap("t", "<C-l>l", "<C-\\><C-N><C-w>l", term_opts)





--------------------------------------
--------------- Plugin ---------------
--------------------------------------

-- Telescope fuzzy bindings
local telescope = require('telescope.builtin')

vim.keymap.set('n', '<Space>b', telescope.lsp_references, opts)
vim.keymap.set('n', '<Space>n', telescope.lsp_definitions, opts)
vim.keymap.set("n", "<Space>o", telescope.live_grep, opts)
keymap("n", "<Space>p", "<Cmd>lua require'telescope.builtin'.find_files(require('telescope.themes').get_dropdown({ previewer = false }))<Cr>", opts)
keymap("n", "<Space>q", "<Cmd>lua require'telescope'.extensions.project.project{}<CR>", opts)
keymap("n", "<leader>d", "<cmd>lua vim.diagnostic.open_float({ border = 'rounded' })<Cr>", opts)
keymap("n", "<leader>D>", "<Cmd>lua require'telescope.builtin'.diagnostics(require('telescope.themes').get_dropdown())<Cr>", opts)

-- Nvimtree
keymap("n", ";", ":NvimTreeToggle<Cr>", opts)