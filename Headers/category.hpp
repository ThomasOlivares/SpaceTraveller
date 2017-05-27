#ifndef CATEGORY_HPP
#define CATEGORY_HPP


// Entity/scene node category, used to dispatch commands
namespace Category
{
	enum Type
	{
		None				= 0,
		SceneAirLayer		= 1 << 0,
		FleetHandler		= 1 << 1,
		Background			= 1 << 2,
		View				= 1 << 3, 
		Cursor				= 1 << 4,
		Planet				= 1 << 5,
		Ship				= 1 << 6,
		Fleet				= 1 << 7,
		Symbol 				= 1 << 8,
	};
}

#endif // CATEGORY_HPP
