local t =
{
    methods =
    {
		Body =
		{
			-- actualMethodName = "exposedMethodName"
			getPosition = "getPosition",
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
		
		Shape = 
		{
			setData = "setData", 
			getData = "getData",
		},
		CircleShape = 
		{
			setData = "setData", 
			getData = "getData",
		},
		PolygonShape = 
		{
			setData = "setData", 
			getData = "getData",
			getPoints = "getPoints",
		},		
	}
}
return t