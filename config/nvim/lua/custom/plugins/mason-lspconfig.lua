return {
  "williamboman/mason-lspconfig.nvim",
  dependencies = {
    "williamboman/mason.nvim",
  },
  opts = {
    ensure_installed = {
      "clangd",
      "lua_ls",
      "pyright",
      "rust_analyzer"
    }
  }
}
