function arg_compare(a, b)
    return a == "-" .. b or a == "--" .. b
end

function run_command(command)
    print(command)
    os.execute(command)
end

local cc = "gcc"
local compiler_args = ""
local randchar_args = ""

local next_arg_is_cc = false
local next_arg_is_compiler_args = false
local next_arg_is_randchar_args = false
for i = 1, #arg do
    if next_arg_is_cc then
        cc = arg[i]
        next_arg_is_cc = false
    elseif next_arg_is_compiler_args then
        compiler_args = arg[i]
        next_arg_is_compiler_args = false
    elseif next_arg_is_randchar_args then
        randchar_args = arg[i]
        next_arg_is_randchar_args = false
    elseif arg_compare(arg[i], "cc") then
        next_arg_is_cc = true
    elseif arg_compare(arg[i], "compiler-args") then
        next_arg_is_compiler_args = true
    elseif arg_compare(arg[i], "randchar-args") then
        next_arg_is_randchar_args = true
    end
end

local command = cc .. " randchar.c -o randchar"
if compiler_args ~= "" then
    command = command .. " " .. compiler_args
end
run_command(command)

command = "." .. package.config:sub(1,1) .. "randchar"
if randchar_args ~= "" then
    command = command .. " " .. randchar_args
end
run_command(command)
