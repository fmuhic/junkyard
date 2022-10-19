local util = {}

function util.keymap(modes, from, to, options)
    local map = vim.api.nvim_set_keymap
    if type(modes) == "string" then
        map(modes, from, to, options)
    else
        for _, mode in pairs(modes) do
            map(mode, from, to, options)
        end
    end
end

return util
