local t =
{
    methods =
    {
	-- Shapes
	CircleShape = 
	{
		setData = "_CircleShape_setData",
		getData = "_CircleShape_getData",
		getPoint = "_CircleShape_getPoint,"
	},
    PolygonShape =
    {
        getTransformedPoints = "_PolygonShape_getTransformedPoints",
		setData = "_PolygonShape_setData",
		getData = "_PolygonShape_getData",         
    },
	SegmentShape = 
	{
		setData = "_SegmentShape_setData",
		getData = "_SegmentShape_getData",
		getPoints = "_SegmentShape_getPoints",
	},
	
        
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
    }
}
return t