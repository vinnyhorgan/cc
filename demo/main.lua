value = 0
value2 = 0
checked = true

function load()
    gui.enableDocking();
end

function update()

end

function draw()
    gui.dockSpace();

    if gui.beginMainMenuBar() then
        if gui.beginMenu("File") then
            if gui.menuItem("Open") then
                print("Open")
            end

            gui.endMenu()
        end

        gui.endMainMenuBar();
    end

    gui.begin("Hello");

    value = gui.sliderInt("Value", value, 0, 100);
    value2 = gui.sliderFloat("Value2", value2, 0, 100);
    checked = gui.checkbox("Checked", checked);

    gui.text("Helloooooo");

    if (gui.button("Click me")) then
        print("Clicked!")
    end

    gui.endd();
end
