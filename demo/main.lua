import("demo/mod.lua")

local berlu
local roboto
local canvas

function load()
    berlu = graphics.newImage("assets/b.png");
    roboto = graphics.newFont("assets/Roboto-Regular.ttf", 32);
    canvas = graphics.newCanvas(200, 200)

    graphics.setFont(roboto)
end

function update()

end

function draw()
    graphics.setCanvas(canvas)

    graphics.clear(255, 255, 255)

    graphics.setColor(255, 0, 0)

    graphics.rectangle(DrawMode.Fill, 10, 10, 50, 100)

    graphics.setColor(255, 255, 255)

    graphics.setCanvas()

    graphics.draw(berlu, 0, 0)
    graphics.print("VIVA LA FIGA", 0, 0)

    graphics.draw(canvas, 100, 100)
end
