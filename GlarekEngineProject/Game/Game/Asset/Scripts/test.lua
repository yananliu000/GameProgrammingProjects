-- Test function calls from our engine!

--log('helllooooooooo')

--call lua function from c
--can only get this function after do file
function SayHello(name)
    log('Hello'..name..'!')
end

xform = engine.world[3].components
--.TransformComponent
--xform.Move(xform.this, 0.1, 0);
