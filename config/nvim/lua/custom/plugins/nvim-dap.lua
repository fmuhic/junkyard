return {
  "mfussenegger/nvim-dap",
  config = function ()
    local dap = require("dap")

    dap.adapters.codelldb = {
      type = 'server',
      port = "${port}",
      executable = {
        command = os.getenv("HOME") .. '/.local/share/nvim/mason/bin/codelldb',
        args = {"--port", "${port}"},
        -- On windows you may have to uncomment this:
        -- detached = false,
      }
    }

    dap.configurations.cpp = {
      {
        name = "Launch file",
        type = "codelldb",
        request = "launch",
        program = function()
          return vim.fn.input('Path to executable: ', vim.fn.getcwd() .. '/', 'file')
        end,
        cwd = '${workspaceFolder}',
        stopOnEntry = false,
      }
    }

    dap.configurations.c = dap.configurations.cpp

    local keymap = require("custom.utils").keymap
    keymap({"n", "i"}, "<F6>", ":DapToggleBreakpoint<CR>", { noremap = true, silent = true })
    keymap({"n", "i"}, "<F7>", ":DapStepInto<CR>", { noremap = true, silent = true })
    keymap({"n", "i"}, "<F8>", ":DapStepOver<CR>", { noremap = true, silent = true })
    keymap({"n", "i"}, "<F9>", ":DapContinue<CR>", { noremap = true, silent = true })
    keymap({"n", "i"}, "<F12>", ":DapTerminate<CR>", { noremap = true, silent = true })
  end
}
