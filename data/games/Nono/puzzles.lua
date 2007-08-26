-- a collection of puzzle presets
-- put in a separate file so it is easy to add/edit puzzles
-- the puzzles stored here will end up a little askew, so keep that in mind at all times ^_^

presets = {
	{
		name = "stairs";
		gridsize = 5;
		offset = 5;
		board ={{1,1,1,1,1},
			    {0,1,1,1,1},
			    {0,0,1,1,1},
			    {0,0,0,1,1},
			    {0,0,0,0,1}};
	},
	{
		name = "paper";
		gridsize = 5;
		offset = 5;
		board ={{0,1,1,1,1},
			    {1,0,0,0,1},
			    {1,0,0,0,1},
			    {1,0,0,0,1},
			    {1,1,1,1,1}};
	},
	{
		name = "star";
		gridsize = 5;
		offset = 5;
		board ={{1,1,0,1,1},
			    {1,0,0,0,1},
			    {0,0,1,0,0},
			    {1,0,0,0,1},
			    {1,1,0,1,1}};
	},
	{
		name = "smile";
		gridsize = 5;
		offset = 5;
		board ={{0,0,0,1,1},
			    {1,1,0,0,1},
			    {0,0,0,0,1},
			    {1,1,0,0,1},
			    {0,0,0,1,1}};
	},
	{
		name = "giraffe";
		gridsize = 5;
		offset = 5;
		board ={{0,0,0,0,0},
			    {0,0,1,1,1},
			    {0,0,0,1,0},
			    {1,1,1,1,1},
			    {0,1,0,0,0}};
	},
	{
		name = "emm";
		gridsize = 5;
		offset = 5;
		board ={{1,1,1,1,1},
			    {0,1,0,0,0},
			    {0,0,1,0,0},
			    {0,1,0,0,0},
			    {1,1,1,1,1}};
	},
	{
		name = "camel";
		gridsize = 7;
		offset = 7;
		board ={{0,1,0,0,0,0,0},
			    {1,1,1,1,1,1,1},
			    {0,0,1,1,1,0,0},
			    {0,1,1,1,1,0,0},
			    {0,1,1,1,1,0,0},
			    {0,0,1,1,1,1,1},
			    {0,0,0,0,0,0,0}};
	},
	{
		name = "basic man";
		gridsize = 7;
		offset = 7;
		board ={{0,0,0,0,0,0,0},
			    {0,1,1,1,0,0,0},
			    {0,1,0,0,1,1,1},
			    {1,1,1,1,1,0,0},
			    {0,1,0,0,1,1,1},
			    {0,1,1,1,0,0,0},
			    {0,0,0,0,0,0,0}};
	},
	{
		name = "grave";
		gridsize = 7;
		offset = 7;
		board ={{0,0,1,1,1,1,1},
			    {0,1,0,0,0,0,0},
			    {1,0,0,1,0,0,0},
			    {1,0,1,1,1,1,0},
			    {1,0,0,1,0,0,0},
			    {0,1,0,0,0,0,0},
			    {0,0,1,1,1,1,1}};
	},
	{
		name = "nyu";
		gridsize = 7;
		offset = 7;
		board ={{0,1,0,0,1,1,0},
			    {1,0,0,1,0,0,1},
			    {0,1,0,0,0,0,1},
			    {0,0,0,0,0,1,0},
			    {0,1,0,0,0,0,1},
			    {1,0,0,1,0,0,1},
			    {0,1,0,0,1,1,0}};
	}
}