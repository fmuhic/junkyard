return {
    "iamcco/markdown-preview.nvim",
    ft = "markdown",
    lazy = true,
    build = "cd app && npm install",
    config = function()
      vim.fn["mkdp#util#install"]()
    end
}

