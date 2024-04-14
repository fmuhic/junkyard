-- :help options

local options = {
    -- creates a backup file
    backup = false,

    -- allows neovim to access the system clipboard
    clipboard = "",

    -- mostly just for cmp
    completeopt = { "menuone", "noselect" },

    -- so that `` is visible in markdown files
    conceallevel = 2,

    -- the encoding written to a file
    fileencoding = "utf-8",

    -- highlight all matches on previous search pattern
    hlsearch = true,

    -- set cursor to block
    guicursor = "",

    -- ignore case in search patterns
    ignorecase = true,

    -- pop up menu height
    pumheight = 10,

    -- smart case
    smartcase = true,

    -- make indenting smarter again
    smartindent = true,

    -- force all horizontal splits to go below current window
    splitbelow = true,

    -- force all vertical splits to go to the right of current window
    splitright = true,

    -- creates a swapfile
    swapfile = false,

    -- time to wait for a mapped sequence to complete (in milliseconds)
    timeoutlen = 1000,

    -- enable persistent undo
    undofile = true,

    -- faster completion (4000ms default)
    updatetime = 300,

    -- if a file is being edited by another program (or was written to file while editing with another program), it is not allowed to be edited
    writebackup = false,

    -- convert tabs to spaces
    expandtab = true,

    -- the number of spaces inserted for each indentation
    shiftwidth = 4,

    -- insert 4 spaces for a tab
    tabstop = 4,

    -- highlight the current line
    cursorline = false,

    -- set numbered lines
    number = true,

    -- set relative numbered lines
    relativenumber = true,

    -- set number column width to 2 {default 4}
    numberwidth = 2,

    -- always show the sign column, otherwise it would shift the text each time
    signcolumn = "yes",

    -- display lines as one long line
    wrap = false,

    -- Min scroll offset
    scrolloff = 8,
    sidescrolloff = 8,

    -- the font used in graphical neovim applications
    guifont = "monospace:h15",

    -- set term gui colors (most terminals support this)
    termguicolors = true,
}

for k, v in pairs(options) do
    vim.opt[k] = v
end

-- Treat dash separated words as one (one-word)
vim.cmd [[set iskeyword+=-]]
vim.cmd [[set guicursor=i:block]]
