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

vim.api.nvim_create_user_command("MakeMember", function(opts)
    if #opts.fargs ~= 2 then
        vim.notify("MakeMember expects exactly 2 arguments", vim.log.levels.ERROR)
        return
    end

    local type = opts.fargs[1]
    local name = opts.fargs[2]

    local lines = {
        "[[nodiscard]] constexpr " .. type .. "& edit_" .. name .. "() noexcept",
        "{",
        "    return this->m_" .. name .. ";",
        "}",
        "",
        "[[nodiscard]] constexpr const " .. type .. "& get_" .. name .. "() const noexcept",
        "{",
        "    return this->m_" .. name .. ";",
        "}",
        "",
        type .. " m_" .. name .. ";",
    }

    local text = table.concat(lines, "\n")

    -- Put into unnamed register (what `p` uses)
    -- vim.fn.setreg('"', text, "c")

    -- Optional: also put into system clipboard
    vim.fn.setreg("+", text, "c")
end, { nargs = "*" })
