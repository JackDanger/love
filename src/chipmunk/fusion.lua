local t =
{
    methods =
    {
        PolygonShape =
        {
            getTransformedPoints = "_PolygonShape_getTransformedPoints"
        }, 
        
        -- Joints.
        PinJoint = 
        {
			getPoints = "_PinJoint_getPoints"
        },        
        PivotJoint = 
        {
			getPoint = "_PivotJoint_getPoint"
        },
    }
}
return t