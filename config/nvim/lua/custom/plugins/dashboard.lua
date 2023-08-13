return {
  'glepnir/dashboard-nvim',
  event = 'VimEnter',
  dependencies = {
    'nvim-tree/nvim-web-devicons'
  },
  config = function()
    local home = os.getenv('HOME')
    require('dashboard').setup {
      theme = 'doom',
      preview = {
        command = 'cat | lolcat -F 0.3',
        file_path = home .. '/.config/nvim/static/neovim.cat',
        file_height = 11,
        file_width = 70,
      },
      config = {
        header = {},
        center = {
          {
            icon = '  ',
            desc = 'Update               ',
            action = 'Lazy update',
            key = 'u',
            keymap = 'SPC u',
          },
          {
            icon = '  ',
            desc = 'Projects               ',
            action = 'Telescope project',
            key = 'q',
            keymap = 'SPC q',
          },
          {
            icon = '  ',
            desc = 'Files               ',
            action = 'Telescope find_files find_command=rg,--hidden,--files',
            key = 'p',
            keymap = 'SPC p',
          },
          {
            icon = '  ',
            desc = 'Words               ',
            action = 'Telescope live_grep',
            key = 'w',
            keymap = 'SPC w',
          },
          {
            icon = '  ',
            desc = 'Dotfiles               ',
            action = 'cd ' .. home ..'/.config/nvim | e init.lua',
            key = 'd',
            keymap = 'SPC d',
          },
        },
        footer = {},
      }
    }
  end
}
