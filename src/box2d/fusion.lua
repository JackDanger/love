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
			setCategory = "setCategory",
			getCategory = "getCategory",
			setMask = "setMask",
			getMask = "getMask",
		},
		CircleShape = 
		{
			setData = "setData", 
			getData = "getData",
			setCategory = "setCategory",
			getCategory = "getCategory",
			setMask = "setMask",
			getMask = "getMask",
		},
		PolygonShape = 
		{
			setData = "setData", 
			getData = "getData",
			getPoints = "getPoints",
			setCategory = "setCategory",
			getCategory = "getCategory",
			setMask = "setMask",
			getMask = "getMask",
		},
	}
}
return t