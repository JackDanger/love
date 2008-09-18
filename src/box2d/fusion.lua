local t =
{
    methods =
    {
		Body =
		{
			-- actualMethodName = "exposedMethodName"
			getPosition = "getPosition",
			getVelocity = "getVelocity",
			getWorldCenter = "getWorldCenter",
			getLocalCenter = "getLocalCenter",
			getWorldPoint = "getWorldPoint",
			getWorldVector = "getWorldVector",
			getLocalPoint = "getLocalPoint",
			getLocalVector = "getLocalVector",
			getVelocityWorldPoint = "getVelocityWorldPoint",
			getVelocityLocalPoint = "getVelocityLocalPoint",
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
			getGravity = "getGravity",
		},
		
		CircleShape = 
		{
			setData = "setData", 
			getData = "getData",
			setCategory = "setCategory",
			getCategory = "getCategory",
			setMask = "setMask",
			getMask = "getMask",
			getBoundingBox = "getBoundingBox",
			testSegment = "testSegment",
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
			getBoundingBox = "getBoundingBox",
			testSegment = "testSegment",
		},
		

		RevoluteJoint = 
		{
			getAnchors = "getAnchors",
			getReactionForce = "getReactionForce",
			getLimits = "getLimits",
		},
		MouseJoint = 
		{
			getAnchors = "getAnchors",
			getReactionForce = "getReactionForce",
			getTarget = "getTarget",
		},
		DistanceJoint = 
		{
			getAnchors = "getAnchors",
			getReactionForce = "getReactionForce",
		},
		PrismaticJoint = 
		{
			getAnchors = "getAnchors",
			getReactionForce = "getReactionForce",
			getLimits = "getLimits",
		},
	},
	rawmethods =
	{
	},
	destroy = 
	{
		Body = true,
		PolygonShape = true,
		CircleShape = true,
		MouseJoint = true,
		DistanceJoint = true,
		RevoluteJoint = true,
		PrismaticJoint = true,
	},
}
return t