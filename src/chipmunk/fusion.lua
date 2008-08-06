local t =
{
    methods =
    {
    	-- Shapes
	Shape =
	{
	    -- actualMethodName = "exposedMethodName"
	    setData = "setData",
	    getData = "getData",
	    getPoints = "getPoints",
	},
	CircleShape = 
	{
	    setData = "setData",
	    getData = "getData",
	    getPoints = "getPoints",
	},
	PolygonShape =
	{
	    setData = "setData",
	    getData = "getData",
	    getPoints = "getPoints",
	},
	SegmentShape = 
	{
	    setData = "setData",
	    getData = "getData",
	    getPoints = "getPoints",
	},
	
	--[[
	-- Joints.
	PinJoint = 
	{
		getPoints = "_PinJoint_getPoints",
	},        
	PivotJoint = 
	{
		getPoint = "_PivotJoint_getPoint",
	},
	SlideJoint = 
	{
		getPoints = "_SlideJoint_getPoints",
		getLimits = "_SlideJoint_getLimits",
	},
	GrooveJoint = 
	{
		getPoints = "_GrooveJoint_getPoints",
	},
	--]]
    },
}
return t