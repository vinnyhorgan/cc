function load()
    guiEnableDocking();
end

function update()

end

function draw()
    guiDockSpace();

    guiBegin("Hello");

    guiText("Helloooooo");

    if (guiButton("Click me")) then
        print("Clicked!")
    end

    guiEnd();
end
