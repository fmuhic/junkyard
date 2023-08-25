return {
  "williamboman/mason.nvim",
  opts = {
    ui = {
      icons = {
          package_installed = "✓",
          package_pending = "➜",
          package_uninstalled = "✗"
      }
    }
  },
    ensure_installed = {
      "clangd",
      "lua_ls",
      "pyright",
      "rust_analyzer"
    }
}
