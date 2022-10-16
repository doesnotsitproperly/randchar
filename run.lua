function arg_compare(a, b)
    return a == "-" .. b or a == "--" .. b
end

function run_command(command)
    print(command)
    os.execute(command)
end

local cc = "gcc"

local next_arg_is_cc = false
for i = 1, #arg do
    if next_arg_is_cc then
        cc = arg[i]
        next_arg_is_cc = false
    elseif arg_compare(arg[i], "cc") then
        next_arg_is_cc = true
    end
end

run_command(cc .. " randchar.c -o randchar")
run_command("." .. package.config:sub(1,1) .. "randchar")
