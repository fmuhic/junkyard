vim.api.nvim_create_autocmd("InsertEnter", {
  callback = function ()
    vim.opt.cursorline = true
  end,
})

vim.api.nvim_create_autocmd("InsertLeave", {
  callback = function ()
    vim.opt.cursorline = false
  end,
})
