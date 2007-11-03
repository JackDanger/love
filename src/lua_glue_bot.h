void luaPushPointer(lua_State * L, void * ptr, int type, int own)
{
	SWIG_NewPointerObj(L, ptr, swig_types[type], 0);
}
