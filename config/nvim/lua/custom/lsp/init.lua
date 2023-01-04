require("mason").setup()
require("mason-lspconfig").setup()

local config = require("custom.lsp.config")
config.initialize()

require("lspconfig")["sumneko_lua"].setup(
    vim.tbl_deep_extend(
        "force",
        require("custom.lsp.server_config.sumneko_lua"),
        config.options
    )
)

require("lspconfig")["jsonls"].setup(
    vim.tbl_deep_extend(
        "force",
        require("custom.lsp.server_config.jsonls"),
        config.options
    )
)

require("lspconfig")["pyright"].setup(
    config.options
)


-- Rust setup
local rt = require("rust-tools")

rt.setup({
  server = {
    on_attach = function(_, bufnr)
      -- Hover actions
      vim.keymap.set("n", "<C-space>", rt.hover_actions.hover_actions, { buffer = bufnr })
      -- Code action groups
      vim.keymap.set("n", "<Leader>a", rt.code_action_group.code_action_group, { buffer = bufnr })
    end,
  },
})

-- Disabled for now, there is a bug
rt.inlay_hints.disable()
