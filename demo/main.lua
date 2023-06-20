import("demo/mod.lua")

local berlu
local roboto
local canvas

function load()
    berlu = cc.graphics.newImage("assets/b.png");
    roboto = cc.graphics.newFont("assets/Roboto-Regular.ttf", 32);
    canvas = cc.graphics.newCanvas(200, 200)

    cc.graphics.setFont(roboto)
end

function update(dt)
    if cc.keyboard.isDown(Key.Space) then
        print("YES")
        res = cc.networking.httpGet("https://www.google.com")

        print(res)
    end
end

function draw()
    cc.graphics.setCanvas(canvas)

    cc.graphics.clear(255, 255, 255)

    cc.graphics.setColor(255, 0, 0)

    cc.graphics.rectangle(DrawMode.Fill, 10, 10, 50, 100)

    cc.graphics.setColor(255, 255, 255)

    cc.graphics.setCanvas()

    cc.graphics.draw(berlu, 0, 0)
    cc.graphics.print("VIVA LA FIGA", 0, 0)

    cc.graphics.draw(canvas, 100, 100)
end
