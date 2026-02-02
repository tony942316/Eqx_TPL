vim.api.nvim_create_user_command("MakeClass", function(opts)
    local name = opts.fargs[1]

    local lines = {
        "class " .. name .. " final",
        "{",
        "public:",
        "    " .. name .. "() = default;",
        "    " .. name .. "(const " .. name .. "&) = default;",
        "    " .. name .. "(" .. name .. "&&) = default;",
        "    " .. name .. "& operator= (const " .. name .. "&) = default;",
        "    " .. name .. "& operator= (" .. name .. "&&) = default;",
        "    ~" .. name .. "() = default;",
        "",
        "private:",
        "};",
    }

    local text = table.concat(lines, "\n")

    -- Put into unnamed register (what `p` uses)
    -- vim.fn.setreg('"', text, "c")

    -- Optional: also put into system clipboard
    vim.fn.setreg("+", text, "c")
end, { nargs = 1 })
