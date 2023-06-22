local ballPositionX = -100
local ballRadius = 20
local ballAlpha = 0

local state = 0
local timer = 0

function load()
    roboto = cc.graphics.newFont("assets/Roboto-Regular.ttf", 32);
    cc.graphics.setFont(roboto)
end

function update(dt)
    timer += dt

    if state == 0 then
        ballPositionX = cc.math.tween(timer, -100, cc.window.getWidth() / 2, 2, TweenType.ElasticOut)

        if timer > 2 then
            timer = 0
            state = 1
        end
    elseif state == 1 then
        ballRadius = cc.math.tween(timer, 20, 520, 3.3, TweenType.ElasticIn)

        if timer > 3.3 then
            timer = 0
            state = 2
        end
    elseif state == 2 then
        ballAlpha = cc.math.tween(timer, 0, 1, 3.3, TweenType.CubicOut)
        print(ballAlpha)

        if timer > 3.3 then
            timer = 0
            state = 3
        end
    elseif state == 3 then
        if cc.keyboard.isPressed(Key.Space) then
            timer = 0;
            ballPositionX = -100;
            ballRadius = 20;
            ballAlpha = 0;
            state = 0;
        end
    end
end

function draw()
    cc.graphics.clear(255, 255, 255)

    cc.graphics.print("Ball position: " .. ballPositionX, 10, 10)
    cc.graphics.print("Ball radius: " .. ballRadius, 10, 40)
    cc.graphics.print("Ball alpha: " .. ballAlpha, 10, 70)
    cc.graphics.print("Timer: " .. timer, 10, 100)

    r, g, b, a = cc.graphics.fade(255, 0, 0, 1 - ballAlpha)

    if state >= 2 then
        cc.graphics.setColor(0, 255, 0)
        cc.graphics.rectangle(DrawMode.Fill, 0, 0, cc.window.getWidth(), cc.window.getHeight())
        cc.graphics.setColor(0, 0, 0)
    end

    if state == 3 then
        cc.graphics.print("Press space to restart", 10, 10)
    end

    cc.graphics.setColor(r, g, b, a)
    cc.graphics.circle(DrawMode.Fill, ballPositionX, cc.window.getHeight() / 2, ballRadius)
    cc.graphics.setColor(0, 0, 0)
end
