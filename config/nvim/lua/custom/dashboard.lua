local dashboard = require('dashboard')

local home = os.getenv('HOME')

dashboard.preview_command = 'cat | lolcat -F 0.3'
dashboard.preview_file_path = home .. '/.config/nvim/static/neovim.cat'
dashboard.preview_file_height = 11
dashboard.preview_file_width = 70
dashboard.custom_center = {
    {
        icon = '  ',
        desc = 'Open Projects                           ',
        action ='Telescope project',
        shortcut = 'Space q'
    },
    {
        icon = '  ',
        desc = 'Find File                               ',
        action = 'Telescope find_files find_command=rg,--hidden,--files',
        shortcut = 'Space p'
    },
    {
        icon = '  ',
        desc = 'Find Word                               ',
        action = 'Telescope live_grep',
        shortcut = 'Space o'
    },
    {
        icon = '  ',
        desc = 'Open Personal Dotfiles                  ',
        action = 'cd ' .. home ..'/.config/nvim | e init.lua',
        shortcut = 'None   '
    },
}
