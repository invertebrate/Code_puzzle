settings = {
window_size_x = 1000,
window_size_y = 1700,
step_time = 1.0,
fps_cap = 60
}

function testf(input1)
   return (input1 * 5)
end

settings["window_size_y"] = testf(200)


--play with macros and try to find something that resembles a pseudo language
