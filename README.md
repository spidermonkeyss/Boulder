# Boulder
<h2>2D engine</h2>

<div>I'm trying out a different architecture.</div>
<div>Scene has the list of scene objects</div>
<div>Renderer has a list of renderer objects</div>
<div>Render objects have the reference ids to the buffers, shader, and texture of the objects</div>
<div>Scene objects are like game objects in Unity. If the objects should be rendered, it has a pointer to a render object, otherwise the pointer is null.</div>
<div></div>

<div></div>


