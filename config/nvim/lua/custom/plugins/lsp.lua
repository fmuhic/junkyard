return {
  "neovim/nvim-lspconfig",
  dependencies = {
    "williamboman/mason.nvim",
    "williamboman/mason-lspconfig.nvim",
    "simrat39/rust-tools.nvim"
  },
  config = function()
    local config = require("custom.plugins.lsp_servers.config")
    config.initialize()

    require("lspconfig")["lua_ls"].setup(
      vim.tbl_deep_extend(
        "force",
        require("custom.plugins.lsp_servers.lua_ls"),
        config.options
      )
    )

    require("lspconfig")["jsonls"].setup(
      vim.tbl_deep_extend(
        "force",
        require("custom.plugins.lsp_servers.jsonls"),
        config.options
      )
    )

    require("lspconfig")["pyright"].setup(
      config.options
    )

    require("lspconfig")["clangd"].setup(
      config.options
    )

    -- Rust setup
    local rt = require("rust-tools")

    rt.setup({
      server = {
        on_attach = function(_, bufnr)
          vim.keymap.set("n", "<C-space>", rt.hover_actions.hover_actions, { buffer = bufnr })
          vim.keymap.set("n", "<Leader>a", rt.code_action_group.code_action_group, { buffer = bufnr })
        end,
      },
    })

    -- Disabled for now, there is a bug
    rt.inlay_hints.disable()
  end
}
