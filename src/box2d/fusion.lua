local t =
{
    methods =
    {
		Body =
		{
			-- actualMethodName = "exposedMethodName"
			getPosition = "getPosition",
		},
		PolygonShape = 
		{
			getPoints = "getPoints"
		}, 
		Contact = 
		{
			getPosition = "getPosition", 
			getVelocity = "getVelocity",
			getNormal = "getNormal",
		},
		World = 
		{
			setCallback = "setCallback",
			getCallback = "getCallback",
		},
		
	}
}
return t